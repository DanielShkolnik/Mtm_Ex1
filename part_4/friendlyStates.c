#include "friendlyStates.h"

struct FriendlyStates_t{
    char* nameState1;
    char* nameState2;
};

FriendlyStates friendlyStatesCreate(const char* nameState1, const char* nameState2){
    FriendlyStates ptr = malloc(sizeof(*ptr));
    if(ptr == NULL){
        return NULL;
    }
    if (strcmp(nameState1,nameState2)<0) {
        ptr->nameState1 = malloc(sizeof(char)*strlen(nameState1)+1);
        ptr->nameState2 = malloc(sizeof(char)*strlen(nameState2)+1);
        strcpy(ptr->nameState1,nameState1);
        strcpy(ptr->nameState2,nameState2);
    }
    else {
        ptr->nameState1 = malloc(sizeof(char)*strlen(nameState2)+1);
        ptr->nameState2 = malloc(sizeof(char)*strlen(nameState1)+1);
        strcpy(ptr->nameState1,nameState2);
        strcpy(ptr->nameState2,nameState1);
    }
    if (ptr->nameState1==NULL || ptr->nameState2==NULL) return NULL;
}


FriendlyStatesResult friendlyStatesDestroy(FriendlyStates friendlyStates){
    if (friendlyStates==NULL) return FRIENDLYSTATES_NULL_ARGUMENT;
    free(friendlyStates->nameState1);
    free(friendlyStates->nameState2);
    free(friendlyStates);
}

int friendlyStatesCompare(FriendlyStates friendlyStates1, FriendlyStates friendlyStates2) {
   return strcmp(friendlyStates1->nameState1,friendlyStates2->nameState1);
}

FriendlyStates friendlyStatesCopy(FriendlyStates friendlyStates) {
    if (friendlyStates==NULL) return NULL;
    return friendlyStatesCreate(friendlyStates->nameState1,friendlyStates->nameState2);
}


