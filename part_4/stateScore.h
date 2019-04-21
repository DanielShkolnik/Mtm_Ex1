#ifndef PART_4_STATESCORE_H
#define PART_4_STATESCORE_H

#endif //PART_4_STATESCORE_H
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct StateScore_t *StateScore;

typedef enum {
    STATESCORE_SUCCESS,
    STATESCORE_OUT_OF_MEMORY,
    STATESCORE_NULL_ARGUMENT,
    STATESCORE_ITEM_ALREADY_EXISTS,
    STATESCORE_ITEM_DOES_NOT_EXIST
} StateScoreResult;