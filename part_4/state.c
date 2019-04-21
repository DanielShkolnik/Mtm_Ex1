#include "state.h"
#include "stateVotes.h"
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
    strcpy(ptr->name,name);
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