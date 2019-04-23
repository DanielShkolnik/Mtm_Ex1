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

Node NodeCreate(MapKeyElement key,
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

Node NodeGetNext(Node node) {
    if (node==NULL) return NULL;
    return node->next;
}

NodeResult NodeSetKey(Node node, MapKeyElement key) {
    if (node==NULL || key==NULL) return NODE_NULL_ARGUMENT;
    node->key=key;
    return NODE_SUCCESS;
}

NodeResult NodeSetData(Node node, MapDataElement data) {
    if (node==NULL || data==NULL) return NODE_NULL_ARGUMENT;
    node->data=data;
    return NODE_SUCCESS;
}

MapKeyElement NodeGetKey(Node node) {
    if (node==NULL) return NULL;
    return node->key;
}

MapDataElement NodeGetData(Node node) {
    if (node==NULL) return NULL;
    return node->data;
}

NodeResult NodeAdd(Node node, MapKeyElement key,
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
    node->next = NodeCreate( key, data, copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, compareKeyElements);
    (node->next)->next = tmp;
    if (node->next == NULL) {
        return NODE_OUT_OF_MEMORY;
    }
    return NODE_SUCCESS;
}

NodeResult NodeRemove(Node node ,MapKeyElement key) {
    if (node==NULL || key==NULL) return NODE_NULL_ARGUMENT;
    Node prevNode = node;
    Node currentNode = node->next;
    while (currentNode!=NULL){
        if(currentNode->compareKeys(currentNode->key,key)==0){
            prevNode->next = currentNode->next;
            freeNode(currentNode);
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    return NODE_SUCCESS;
}

static NodeResult freeNode (Node node){
    node->freeData(node->data);
    node->freeKey(node->key);
    free(node);
    return NODE_SUCCESS;
}

NodeResult NodeDestroy(Node head){
    if(head==NULL) return NODE_NULL_ARGUMENT;
    while (head!=NULL){
        Node tmp = head;
        head = head->next;
        freeNode(tmp);
    }
    return NODE_SUCCESS;
}

Node NodeCopy(Node node){
    if(node==NULL) return NULL;
    Node new = NodeCreate(node->key,node->data,node->copyData,node->copyKey,node->freeData,node->freeKey,node->compareKeys);
    Node head = new;
    node = node->next;
    while (node!=NULL){
        new->next = NodeCreate(node->key,node->data,node->copyData,node->copyKey,node->freeData,node->freeKey,node->compareKeys);
        if(new->next==NULL){
            NodeDestroy(head);
            return NULL;
        }
        new = new->next;
        node = node->next;
    }
    return head;
}
Node NodeGetNode(Node node, MapKeyElement key){
    while (node!=NULL){
        if(node->compareKeys(node->key,key)==0){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

#include "node.h"
