#include "stateScore.h"

struct StateScore_t{
    int id;
    int stateVotes;
    int judgesVotes;
};


StateScore createStateScore(int id, int stateVotes, int judgesVotes){
    StateScore ptr=malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr->id=id;
    ptr->stateVotes=stateVotes;
    ptr->judgesVotes=judgesVotes;
}

StateScoreResult destroyStateScore(StateScore stateScore){
    if (stateScore==NULL) return STATESCORE_NULL_ARGUMENT;
    free(stateScore);
    return STATESCORE_SUCCESS;
}

int compareStateScoreId(StateScore stateScore1, StateScore stateScore2) {
    return stateScore1->id-stateScore2->id;
}

StateScore copyStateScore(StateScore stateScore){
     return createStateScore(stateScore->id, stateScore->stateVotes, stateScore->judgesVotes);
}

