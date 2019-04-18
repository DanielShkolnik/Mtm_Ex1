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

Node NodeGetNext(Node node) {
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
    return node->key;
}

MapDataElement NodeGetdata(Node node) {
    return node->data;
}

NodeResult NodeAdd(Node node, MapKeyElement key,
                   MapDataElement data,
                   copyMapDataElements copyDataElement,
                   copyMapKeyElements copyKeyElement,
                   freeMapDataElements freeDataElement,
                   freeMapKeyElements freeKeyElement,
                   compareMapKeyElements compareKeyElements) {
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = NodeCreate( key, data, copyDataElement, copyKeyElement, freeDataElement, freeKeyElement, compareKeyElements);
    if (node->next == NULL) {
        return NODE_OUT_OF_MEMORY;
    }
    return NODE_SUCCESS;
}

NodeResult NodeRemove(Node node ,MapKeyElement key) {
    while (node->next!=NULL) {
        if ((node->next)->key==key) {
            node->next=(node->next)->next;
            freeNode(node->next);
        }
    }
}

static NodeResult freeNode (Node node){
    node->freeData(node->data);
    node->freeKey(node->key);
    free(node);
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

#include "node.h"
