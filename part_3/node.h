#ifndef PART_3_NODE_H
#define PART_3_NODE_H

#include "map.h"

typedef struct Node_t *Node;

typedef enum {
    NODE_SUCCESS=0,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT,
} NodeResult;
//test
Node NodeGetNext(Node node);
MapKeyElement NodeGetKey(Node node);
MapDataElement NodeGetData(Node node);
NodeResult NodeSetKey(Node node, MapKeyElement key);
NodeResult NodeSetData(Node node, MapDataElement data);
NodeResult NodeAdd(Node node, MapKeyElement key,
                   MapDataElement data,
                   copyMapDataElements copyDataElement,
                   copyMapKeyElements copyKeyElement,
                   freeMapDataElements freeDataElement,
                   freeMapKeyElements freeKeyElement,
                   compareMapKeyElements compareKeyElements);
NodeResult NodeRemove(Node node ,MapKeyElement key);
Node NodeCreate(MapKeyElement key,
                MapDataElement data,
                copyMapDataElements copyDataElement,
                copyMapKeyElements copyKeyElement,
                freeMapDataElements freeDataElement,
                freeMapKeyElements freeKeyElement,
                compareMapKeyElements compareKeyElements);
NodeResult NodeDestroy(Node head);
typedef MapDataElement(*copyNodeDataElements)(MapDataElement); // need implement in node.c
typedef MapKeyElement(*copyNodeKeyElements)(MapKeyElement); // need implement in node.c
typedef void(*freeNodeDataElements)(MapDataElement); // need implement in node.c
typedef void(*freeNodeKeyElements)(MapKeyElement); // need implement in node.c
typedef int(*compareNodeKeyElements)(MapKeyElement, MapKeyElement); // need implement in node.c
#endif //PART_3_NODE_H
