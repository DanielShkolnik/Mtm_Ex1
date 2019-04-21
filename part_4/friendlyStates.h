#ifndef PART_4_FRIENDLYSTATES_H
#define PART_4_FRIENDLYSTATES_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct FriendlyStates_t *FriendlyStates;

typedef enum {
    FRIENDLYSTATES_SUCCESS,
    FRIENDLYSTATES_OUT_OF_MEMORY,
    FRIENDLYSTATES_NULL_ARGUMENT,
    FRIENDLYSTATES_ITEM_ALREADY_EXISTS,
    FRIENDLYSTATES_ITEM_DOES_NOT_EXIST
} FriendlyStatesResult;





#endif //PART_4_FRIENDLYSTATES_H
