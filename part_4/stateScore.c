#include "stateScore.h"

struct StateScore_t{
    int id;
    int statesVotes;
    int judgesVotes;
};


StateScore stateScoreCreate(int id, int stateVotes, int judgesVotes){
    StateScore ptr=malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->id=id;
    ptr->statesVotes=stateVotes;
    ptr->judgesVotes=judgesVotes;
}

StateScoreResult stateScoreDestroy(StateScore stateScore){
    if (stateScore==NULL) return STATESCORE_NULL_ARGUMENT;
    free(stateScore);
    return STATESCORE_SUCCESS;
}

int stateScoreCompare(StateScore stateScore1, StateScore stateScore2) {
    assert(stateScore1!=NULL && stateScore2!=NULL);
    return stateScore1->id-stateScore2->id;
}

StateScore stateScoreCopy(StateScore stateScore){
    if (stateScore==NULL) return NULL;
     return stateScoreCreate(stateScore->id, stateScore->statesVotes, stateScore->judgesVotes);
}

