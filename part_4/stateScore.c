#include "stateScore.h"
#define PERCENTAGE 100

struct StateScore_t{
    int id;
    char* name;
    double totalScore;
};


StateScore stateScoreCreate(int id, char* name, double stateVotesAverage, double judgesVotesAverage, int audiencePercent){
    StateScore ptr=malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->id=id;
    ptr->name = malloc(sizeof(char)*strlen(name)+1);
    if (ptr->name==NULL) return NULL;
    strcpy(ptr->name,name);
    ptr->totalScore=(stateVotesAverage*audiencePercent)/PERCENTAGE+(judgesVotesAverage*(PERCENTAGE-audiencePercent))/PERCENTAGE;
    return ptr;
}

StateScoreResult stateScoreDestroy(StateScore stateScore){
    if (stateScore==NULL) return STATESCORE_NULL_ARGUMENT;
    free(stateScore->name);
    free(stateScore);
    return STATESCORE_SUCCESS;
}

int stateScoreCompare(StateScore stateScore1, StateScore stateScore2) {
    double compareResult=-(stateScore1->totalScore-stateScore2->totalScore);
    if (compareResult==0) {
        return stateScore1->id-stateScore2->id;
    }
    return (int)compareResult;
}

StateScore stateScoreCopy(StateScore stateScore){
    if (stateScore==NULL) return NULL;
    StateScore ptr=malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->id=stateScore->id;
    ptr->name = malloc(sizeof(char)*strlen(stateScore->name)+1);
    if (ptr->name==NULL) return NULL;
    strcpy(ptr->name,stateScore->name);
    ptr->totalScore=stateScore->totalScore;
    return ptr;
}

char* stateScoreGetName(StateScore stateScore) {
    assert(stateScore!=NULL);
    return stateScore->name;
}