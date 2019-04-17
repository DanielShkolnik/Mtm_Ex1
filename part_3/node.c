#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

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

MapKeyElement NodeGetKey(Node node) {
    return node->key;
}

MapDataElement NodeGetdata(Node node) {
    return node->data;
}

NodeResult NodeAdd(Node node, MapKeyElement key, MapDataElement data) {
    while (node->next != Null) {
        node = node->next;
    }
    node->next = NodeCreate(key, data);
    if (node->next == NULL) {
        return NODE_OUT_OF_MEMORY;
    }
    return NODE_SUCCESS;
}

#include "node.h"
