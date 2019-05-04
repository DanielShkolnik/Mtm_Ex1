#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

static NodeResult freeNode (Node node);

struct Node_t{
    MapKeyElement key;
    MapDataElement data;
    struct Node_t *next;
    copyNodeDataElements copyData;
    copyNodeKeyElements copyKey;
    freeNodeDataElements freeData;
    freeNodeKeyElements freeKey;
    compareNodeKeyElements compareKeys;
};

Node nodeCreate(MapKeyElement key,
                MapDataElement data,
                copyMapDataElements copyDataElement,
                copyMapKeyElements copyKeyElement,
                freeMapDataElements freeDataElement,
                freeMapKeyElements freeKeyElement,
                compareMapKeyElements compareKeyElements){
    Node ptr = malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->key = copyKeyElement(key);
    ptr->data= copyDataElement(data);
    ptr->copyKey = copyKeyElement;
    ptr->copyData = copyDataElement;
    ptr->freeData = freeDataElement;
    ptr->freeKey = freeKeyElement;
    ptr->compareKeys = compareKeyElements;
    ptr->next = NULL;
    return ptr;
}

Node nodeGetNext(Node node) {
    if (node==NULL) return NULL;
    return node->next;
}

NodeResult nodeSetKey(Node node, MapKeyElement key) {
    if (node==NULL || key==NULL) return NODE_NULL_ARGUMENT;
    node->key=key;
    return NODE_SUCCESS;
}

NodeResult nodeSetData(Node node, MapDataElement data) {
    if (node==NULL || data==NULL) return NODE_NULL_ARGUMENT;
    node->freeData(node->data);
    node->data = node->copyData(data);
    return NODE_SUCCESS;
}

MapKeyElement nodeGetKey(Node node) {
    if (node==NULL) return NULL;
    return node->key;
}

MapDataElement nodeGetData(Node node) {
    if (node==NULL) return NULL;
    return node->data;
}

NodeResult nodeAdd(Node node, MapKeyElement key,
                   MapDataElement data,
                   copyMapDataElements copyDataElement,
                   copyMapKeyElements copyKeyElement,
                   freeMapDataElements freeDataElement,
                   freeMapKeyElements freeKeyElement,
                   compareMapKeyElements compareKeyElements) {
    if (node==NULL || data==NULL || key==NULL) return NODE_NULL_ARGUMENT;
    while (node->next != NULL) {
        if((node->next)->compareKeys((node->next)->key,key)>0){
            break;
        }
        node = node->next;
    }
    Node tmp = node->next;
    node->next = nodeCreate( key, data, copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, compareKeyElements);
    (node->next)->next = tmp;
    if (node->next == NULL) {
        return NODE_OUT_OF_MEMORY;
    }
    return NODE_SUCCESS;
}

NodeResult nodeRemove(Node node ,MapKeyElement key) {
    if (node==NULL || key==NULL) return NODE_NULL_ARGUMENT;
    Node prevNode = node;
    Node currentNode = node->next;
    while (currentNode!=NULL){
        if(currentNode->compareKeys(currentNode->key,key)==0){
            prevNode->next = currentNode->next;
            freeNode(currentNode);
            return NODE_SUCCESS;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    return NODE_SUCCESS;
}

/**
 * freeNodeHead frees the first node key, data and the node pointer by the dedicated functions
 * for freeing these elements.
 * @param node = pointer of the node to free.
 * @return NODE_SUCCESS in case of successful free
 */
static NodeResult freeNodeHead (Node node) {
    free(node->key);
    free(node->data);
    free(node);
    return NODE_SUCCESS;
}

/**
 * freeNode frees the other nodes (except the first) key, data and the node pointer by the dedicated functions
 * for freeing these elements.
 * @param node = pointer of the node to free.
 * @return NODE_SUCCESS in case of successful free
 * @return
 */
static NodeResult freeNode (Node node){
    node->freeData(node->data);
    node->freeKey(node->key);
    free(node);
    return NODE_SUCCESS;
}

NodeResult nodeDestroy(Node head){
    if(head==NULL) return NODE_NULL_ARGUMENT;
    Node nodeCurrent=head->next;
    freeNodeHead(head);
    while (nodeCurrent!=NULL){
        Node tmp = nodeCurrent;
        nodeCurrent = nodeCurrent->next;
        freeNode(tmp);
    }
    return NODE_SUCCESS;
}

Node nodeCopy(Node node){
    if(node==NULL) return NULL;
    Node new = nodeCreate(node->key,node->data,node->copyData,node->copyKey,node->freeData,node->freeKey,node->compareKeys);
    Node head = new;
    node = node->next;
    while (node!=NULL){
        new->next = nodeCreate(node->key,node->data,node->copyData,node->copyKey,node->freeData,node->freeKey,node->compareKeys);
        if(new->next==NULL){
            nodeDestroy(head);
            return NULL;
        }
        new = new->next;
        node = node->next;
    }
    return head;
}
Node nodeGetNode(Node node, MapKeyElement key){
    while (node!=NULL){
        if(node->compareKeys(node->key,key)==0){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

#include "node.h"
