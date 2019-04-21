#include "stateScore.h"

struct StateScore_t{
    int id;
    int stateVotes;
    int judgesVotes;
};


StateScore stateScoreCreate(int id, int stateVotes, int judgesVotes){
    StateScore ptr=malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->id=id;
    ptr->stateVotes=stateVotes;
    ptr->judgesVotes=judgesVotes;
}

StateScoreResult stateScoreDestroy(StateScore stateScore){
    if (stateScore==NULL) return STATESCORE_NULL_ARGUMENT;
    free(stateScore);
    return STATESCORE_SUCCESS;
}

int stateScoreCompare(StateScore stateScore1, StateScore stateScore2) {
    return stateScore1->id-stateScore2->id;
}

StateScore stateScoreCopy(StateScore stateScore){
    if (stateScore==NULL) return NULL;
     return stateScoreCreate(stateScore->id, stateScore->stateVotes, stateScore->judgesVotes);
}

