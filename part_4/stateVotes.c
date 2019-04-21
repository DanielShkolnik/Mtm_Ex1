#include "stateVotes.h"

struct StateVote_t{
    int stateId;
    int votes;
};

StateVote stateVoteCreate(int stateId){
    StateVote ptr = malloc(sizeof(*ptr));
    if(ptr == NULL){
        return NULL;
    }
    ptr->stateId = stateId;
    return ptr;
}

StateVote stateVoteCopy(StateVote stateVote){
    return stateVoteCreate(stateVote->stateId);
}

void stateVoteDestroy(StateVote stateVote){
    free(stateVote);
}

int stateVoteCompare(StateVote stateVote1,StateVote stateVote2){
    return stateVote1->stateId - stateVote2->stateId;
}