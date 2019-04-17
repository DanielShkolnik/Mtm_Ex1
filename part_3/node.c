#include "map.h"
#include "node.h"

struct Node_t{
    MapKeyElement key;
    MapDataElement value;
    struct Node_t* next;
};

Node NodeGetNext(Node node){
    return node->next;
}
#include "node.h"
