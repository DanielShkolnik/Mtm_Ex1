#include "state.h"
#include "stateVotes.h"
#define JUDGE_NUMBER_OF_VOTES 10
struct State_t{
    int id;
    char* name;
    char* song;
    Set votes;
};


static SetElement copyStateVote (SetElement stateVote){
    if(!stateVote) return NULL;
    return stateVoteCopy((StateVote)stateVote);
}

static void freeStateVote(SetElement stateVote){
    stateVoteDestroy((StateVote)stateVote);
}

static int compareStateVote(SetElement stateVote1, SetElement stateVote2){
    return stateVoteCompare((StateVote)stateVote1,(StateVote)stateVote2);
}

State stateCreate(int id, const char* name, const char* song){
    State ptr = malloc(sizeof(*ptr));
    if(ptr == NULL){
        return NULL;
    }
    ptr->id = id;
    ptr->name = malloc(sizeof(char)*strlen(name)+1);
    if(!ptr->name) return NULL;
    strcpy(ptr->name,name);
    ptr->song = malloc(sizeof(char)*strlen(song)+1);
    if(!ptr->song) return NULL;
    strcpy(ptr->song,song);
    ptr->votes = setCreate(copyStateVote,freeStateVote,compareStateVote);
}
State stateCopy(State state){
    if(!state) return NULL;
    return stateCreate(state->id,state->name,state->song);
}

void stateDestroy(State state){
    if(!state) return;
    free(state->song);
    free(state->name);
    setDestroy(state->votes);
    free(state);
}
int stateCompare(State state1,State state2){
    return state1->id - state2->id;
}

int stateGetId(State state){
    return state->id;
}

StateResult stateRemoveVotedState(State state, State remove){
    StateVote tmp = stateVoteCreate(remove->id);
    SetResult result = setRemove(state->votes,tmp);
    if(result == SET_ITEM_DOES_NOT_EXIST) return STATE_ITEM_DOES_NOT_EXIST;
    stateVoteDestroy(tmp);
    return STATE_SUCCESS;
}

StateResult stateAddOrRemoveVote(State state, int voteStateId,VoteAddOrRemove choice){
    if(!state || voteStateId < 0) return STATE_NULL_ARGUMENT;
    SET_FOREACH(StateVote,vote,state->votes){
        if(stateVoteGetId(vote)==voteStateId){
            if(choice == VOTE_ADD){
                stateVoteAddVote(vote);
            }
            else{
                stateVoteRemoveVote(vote);
            }
            return STATE_SUCCESS;
        }
    }
    if(choice==VOTE_ADD){
        StateVote tmp = stateVoteCreate(voteStateId);
        setAdd(state->votes,tmp);
        stateVoteAddVote(tmp);
        stateVoteDestroy(tmp);
    }
    return STATE_SUCCESS;
}

int* stateGetVotes(State state){
    int* votes = malloc(sizeof(int)*JUDGE_NUMBER_OF_VOTES);
    Set tmp = setCopy(state->votes);
    if(!votes || !tmp) return NULL;
    int max = 0;
    StateVote maxStateVote = NULL;
    for(int i=0;i<JUDGE_NUMBER_OF_VOTES;i++){
        SET_FOREACH(StateVote,voteIterator,tmp){
            if(stateVoteGetVote(voteIterator) > max){
                max=stateVoteGetVote(voteIterator);
                maxStateVote = voteIterator;
            }
        }
        votes[i]=stateVoteGetId(maxStateVote);
        setRemove(tmp,maxStateVote);
        max=0;
    }
    free(votes);
    setDestroy(tmp);
    stateVoteDestroy(maxStateVote);
    return votes;
}

char* stateGetName(State state) {
    assert(state!=NULL);
    return state->name;
}

