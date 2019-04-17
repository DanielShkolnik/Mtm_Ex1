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
NodeResult NodeAdd(Node node);
NodeResult NodeRemove(MapKeyElement key);
Node NodeCreate(MapKeyElement key, MapDataElement data);
NodeResult NodeDestroy(Node node);
#endif //PART_3_NODE_H
