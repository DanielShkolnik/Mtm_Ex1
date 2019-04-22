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

FriendlyStates friendlyStatesCreate(const char* nameState1, const char* nameState2);
FriendlyStatesResult friendlyStatesDestroy(FriendlyStates friendlyStates);
int friendlyStatesCompare(FriendlyStates friendlyStates1, FriendlyStates friendlyStates2);
FriendlyStates friendlyStatesCopy(FriendlyStates friendlyStates);
char* friendlyStatesGetName1(FriendlyStates friendlyStates);
char* friendlyStatesGetName2(FriendlyStates friendlyStates);


#endif //PART_4_FRIENDLYSTATES_H
