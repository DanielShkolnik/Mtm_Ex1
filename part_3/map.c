#include "map.h"
#include "node.h"
#include "map.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

struct Map_t {
    Node listHead;
    MapKeyElement iterator;
    copyMapDataElements copyData;
    copyMapKeyElements copyKey;
    freeMapDataElements freeData;
    freeMapKeyElements freeKey;
    compareMapKeyElements compareKeys;

};

