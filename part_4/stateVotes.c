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
    ptr->votes = 0;
    return ptr;
}

StateVote stateVoteCopy(StateVote stateVote){
    if(!stateVote) return NULL;
    return stateVoteCreate(stateVote->stateId);
}

void stateVoteDestroy(StateVote stateVote){
    free(stateVote);
}

int stateVoteCompare(StateVote stateVote1,StateVote stateVote2){
    return stateVote1->stateId - stateVote2->stateId;
}

StatVoteResult stateVoteAddVote(StateVote vote){
    if(!vote) return STATEVOTE_NULL_ARGUMENT;
    vote->votes += 1;
    return STATEVOTE_SUCCESS;
}

StatVoteResult stateVoteRemoveVote(StateVote vote){
    if(!vote) return STATEVOTE_NULL_ARGUMENT;
    if(vote->votes <= 0){
        vote->votes = 0;
    }
    else{
        vote->votes -= 1;
    }
    return STATEVOTE_SUCCESS;
}

int stateVoteGetId(StateVote vote){
    return vote->stateId;
}

int stateVoteGetVote(StateVote vote){
    return vote->stateId;
}