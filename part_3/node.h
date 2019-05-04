#ifndef PART_3_NODE_H
#define PART_3_NODE_H

#include "map.h"

/** Type for defining the Node struct */
typedef struct Node_t *Node;

/** Type used for returning error codes from Node functions */
typedef enum {
    NODE_SUCCESS=0,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT,
} NodeResult;
//test
Node nodeGetNext(Node node);
MapKeyElement nodeGetKey(Node node);
MapDataElement nodeGetData(Node node);
NodeResult nodeSetKey(Node node, MapKeyElement key);
NodeResult nodeSetData(Node node, MapDataElement data);
NodeResult nodeAdd(Node node, MapKeyElement key,
                   MapDataElement data,
                   copyMapDataElements copyDataElement,
                   copyMapKeyElements copyKeyElement,
                   freeMapDataElements freeDataElement,
                   freeMapKeyElements freeKeyElement,
                   compareMapKeyElements compareKeyElements);
NodeResult nodeRemove(Node node ,MapKeyElement key);
Node nodeCreate(MapKeyElement key,
                MapDataElement data,
                copyMapDataElements copyDataElement,
                copyMapKeyElements copyKeyElement,
                freeMapDataElements freeDataElement,
                freeMapKeyElements freeKeyElement,
                compareMapKeyElements compareKeyElements);
NodeResult nodeDestroy(Node head);
Node nodeCopy(Node node);
Node nodeGetNode(Node node, MapKeyElement);
typedef MapDataElement(*copyNodeDataElements)(MapDataElement);
typedef MapKeyElement(*copyNodeKeyElements)(MapKeyElement);
typedef void(*freeNodeDataElements)(MapDataElement);
typedef void(*freeNodeKeyElements)(MapKeyElement);
typedef int(*compareNodeKeyElements)(MapKeyElement, MapKeyElement);
#endif //PART_3_NODE_H
