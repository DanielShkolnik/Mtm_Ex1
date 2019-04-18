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
Node NodeCopy(Node node);
Node NodeGetNode(Node node, MapKeyElement);
typedef MapDataElement(*copyNodeDataElements)(MapDataElement);
typedef MapKeyElement(*copyNodeKeyElements)(MapKeyElement);
typedef void(*freeNodeDataElements)(MapDataElement);
typedef void(*freeNodeKeyElements)(MapKeyElement);
typedef int(*compareNodeKeyElements)(MapKeyElement, MapKeyElement);
#endif //PART_3_NODE_H
