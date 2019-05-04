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
/**
 * Gets next node
 * @param node
 * @return next node
 */
Node nodeGetNext(Node node);
/**
 * Gets the node key
 * @param node
 * @return the nodes key
 */
MapKeyElement nodeGetKey(Node node);
/**
 * Gets the node data
 * @param node
 * @return returns the node data
 */
MapDataElement nodeGetData(Node node);
/**
 * sets the node key
 * @param node
 * @param key
 * @return return succes if no errors
 */
NodeResult nodeSetKey(Node node, MapKeyElement key);
/**
 * Sets the data of the node
 * @param node
 * @param data
 * @return Success if no errors occurred
 */
NodeResult nodeSetData(Node node, MapDataElement data);
/**
 * Creates a new copy of a given node and add it.
 */
NodeResult nodeAdd(Node node, MapKeyElement key,
                   MapDataElement data,
                   copyMapDataElements copyDataElement,
                   copyMapKeyElements copyKeyElement,
                   freeMapDataElements freeDataElement,
                   freeMapKeyElements freeKeyElement,
                   compareMapKeyElements compareKeyElements);
/**
 * removes a node by its key.
 */
NodeResult nodeRemove(Node node ,MapKeyElement key);
/**
 * Creates a new node. with a copy, free and compare functions for generic data types.
 */
Node nodeCreate(MapKeyElement key,
                MapDataElement data,
                copyMapDataElements copyDataElement,
                copyMapKeyElements copyKeyElement,
                freeMapDataElements freeDataElement,
                freeMapKeyElements freeKeyElement,
                compareMapKeyElements compareKeyElements);
/**
 * Destroys a node and all its alocated memory using the given free function
 */
NodeResult nodeDestroy(Node head);
/**
 * Copies a node and all its "nexts".
 */
Node nodeCopy(Node node);
/**
 * Gets a node by its key.
 */
Node nodeGetNode(Node node, MapKeyElement);
typedef MapDataElement(*copyNodeDataElements)(MapDataElement);
typedef MapKeyElement(*copyNodeKeyElements)(MapKeyElement);
typedef void(*freeNodeDataElements)(MapDataElement);
typedef void(*freeNodeKeyElements)(MapKeyElement);
typedef int(*compareNodeKeyElements)(MapKeyElement, MapKeyElement);
#endif //PART_3_NODE_H
