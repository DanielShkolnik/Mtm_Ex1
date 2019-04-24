#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

static Node creatHead(copyMapDataElements copyDataElement,
                      copyMapKeyElements copyKeyElement,
                      freeMapDataElements freeDataElement,
                      freeMapKeyElements freeKeyElement,
                      compareMapKeyElements compareKeyElements);

struct Map_t {
    Node listHead;
    MapKeyElement iterator;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements compareKeys;
};

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
    if(!copyDataElement || !copyKeyElement || !freeDataElement || !freeKeyElement || !compareKeyElements){
        return NULL;
    }
    Map ptr = malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }


    ptr->listHead = creatHead(copyDataElement,copyKeyElement,freeDataElement,freeKeyElement,compareKeyElements);
    ptr->iterator = NULL;
    ptr->copyData = copyDataElement;
    ptr->copyKey = copyKeyElement;
    ptr->freeData = freeDataElement;
    ptr->freeKey = freeKeyElement;
    ptr->compareKeys = compareKeyElements;
    return ptr;
}

static Node creatHead(copyMapDataElements copyDataElement,
                      copyMapKeyElements copyKeyElement,
                      freeMapDataElements freeDataElement,
                      freeMapKeyElements freeKeyElement,
                      compareMapKeyElements compareKeyElements){
    if(!copyDataElement || !copyKeyElement || !freeDataElement || !freeKeyElement || !compareKeyElements){
        return NULL;
    }
    int* headKey = malloc(sizeof(int));
    if(headKey==NULL) return NULL;
    int* headData = malloc(sizeof(int));
    if(headData==NULL) return NULL;
    *headData = -1;
    *headKey = -1;
    Node node = NodeCreate(headKey,headData,copyDataElement,copyKeyElement,
                            freeDataElement,freeKeyElement,compareKeyElements);
    free(headKey);
    free(headData);
    if(node == NULL){
        return NULL;
    }
    return node;
}

void mapDestroy(Map map){
    if (map==NULL) return;
    NodeDestroy(map->listHead);
    free(map);
}

int mapGetSize(Map map) {
    if (map==NULL) return -1;
    Node currentNode=NodeGetNext(map->listHead);
    int counter=0;
    while (currentNode!=NULL) {
      counter++;
      currentNode=NodeGetNext(currentNode);
    }
    return counter;
}

Map mapCopy(Map map){
    if (map==NULL) return  NULL;
    Map newMap;
    newMap=mapCreate(map->copyData,map->copyKey,map->freeData,map->freeKey,map->compareKeys);
    NodeDestroy(newMap->listHead);
    newMap->listHead=NodeCopy(map->listHead);
    return newMap;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if (map==NULL || keyElement==NULL || dataElement==NULL) return MAP_NULL_ARGUMENT;
    map->iterator = NULL;
    Node current = NodeGetNext(map->listHead);
    while(NodeGetNext(current) !=NULL){
        if(map->compareKeys(NodeGetKey(current),keyElement)== 0){
            NodeSetData(current,dataElement);
            return MAP_SUCCESS;
        }
        current = NodeGetNext(current);
    }
    if(current!=NULL && map->compareKeys(NodeGetKey(current),keyElement)== 0){
        NodeSetData(current,dataElement);
        return MAP_SUCCESS;
    }
    else {
        NodeResult result = NodeAdd(map->listHead,keyElement,dataElement,map->copyData,map->copyKey,map->freeData,map->freeKey,map->compareKeys);
        if(result == NODE_OUT_OF_MEMORY) return MAP_OUT_OF_MEMORY;
        return MAP_SUCCESS;
    }
}

MapKeyElement mapGetFirst(Map map){
    if(!map) return NULL;
    Node first = NodeGetNext(map->listHead);
    if(first==NULL){
        return NULL;
    }
    map->iterator = NodeGetKey(first);
    return NodeGetKey(first);
}

MapKeyElement mapGetNext(Map map){
    if(!map) return NULL;
    if(map->iterator==NULL){
        return NULL;
    }
    Node tmp = NodeGetNode(NodeGetNext(map->listHead),map->iterator);
    map->iterator = NodeGetKey(NodeGetNext(tmp));
    return NodeGetKey(NodeGetNext(tmp));
}

bool mapContains(Map map, MapKeyElement element) {
    if (map==NULL || element==NULL) return false;
    if (mapGet(map,element)==NULL) return false;
    return true;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement) {
    if (map==NULL || keyElement==NULL) return NULL;
    Node currentNode=NodeGetNext(map->listHead);
    while (currentNode!=NULL) {
        if ((map->compareKeys(NodeGetKey(currentNode),keyElement))==0) {
            return NodeGetData(currentNode);
        }
        currentNode=NodeGetNext(currentNode);
    }
    return NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if (map==NULL || keyElement==NULL) return MAP_NULL_ARGUMENT;
    if ((mapContains(map, keyElement))==false) return MAP_ITEM_DOES_NOT_EXIST;
    NodeRemove(map->listHead,keyElement);
    return MAP_SUCCESS;
}

MapResult mapClear(Map map) {
    if (map==NULL) return MAP_NULL_ARGUMENT;
    NodeDestroy(map->listHead);
    return MAP_SUCCESS;
}

