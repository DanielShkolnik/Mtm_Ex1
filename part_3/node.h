#ifndef PART_3_NODE_H
#define PART_3_NODE_H

typedef struct Node_t *Node;

typedef enum {
    NODE_SUCCESS=0,
    NODE_OUT_OF_MEMORY,
    NODE_NULL_ARGUMENT,
} NodeResult;

Node NodeGetNext(Node node);
MapKeyElement NodeGetKey(Node node);
MapDataElement NodeGetValue(Node node);
Node NodeSetNext(Node node);
MapKeyElement NodeSetKey(Node node);
MapDataElement NodeSetValue(Node node);
NodeResult NodeAdd(Node node, MapKeyElement key, MapDataElement data);
NodeResult NodeRemove(MapKeyElement key);
Node NodeCreate(MapKeyElement key,
                MapDataElement data,
                copyMapDataElements copyDataElement,
                copyMapKeyElements copyKeyElement,
                freeMapDataElements freeDataElement,
                freeMapKeyElements freeKeyElement,
                compareMapKeyElements compareKeyElements);
NodeResult NodeDestroy(Node node);
typedef MapDataElement(*copyNodeDataElements)(MapDataElement);
typedef MapKeyElement(*copyNodeKeyElements)(MapKeyElement);
typedef void(*freeNodeDataElements)(MapDataElement);
typedef void(*freeNodeKeyElements)(MapKeyElement);
typedef int(*compareNodeKeyElements)(MapKeyElement, MapKeyElement);
#endif //PART_3_NODE_H
