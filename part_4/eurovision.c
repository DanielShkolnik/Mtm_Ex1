#include "eurovision.h"
#include "state.h"
#include "judge.h"

struct eurovision_t {
    Set states;
    Set judges;
};
static SetElement copyState (SetElement state){
    if(!state) return NULL;
    return stateCopy((State)state);
}

static void freeState(SetElement state){
    stateDestroy((State)state);
}

static int compareState(SetElement state1, SetElement state2){
    return stateCompare((State)state1,(State)state2);
}

static SetElement copyJudge (SetElement judge){
    if(!judge) return NULL;
    return judgeCopy((Judge)judge);
}

static void freeJudge(SetElement judge){
    judgeDestroy((Judge)judge);
}

static int compareJudge(SetElement judge1, SetElement judge2){
    return judgeCompare((Judge)judge1,(Judge)judge2);
}

Eurovision eurovisionCreate(){
    Eurovision ptr = malloc(sizeof(*ptr));
    if(!ptr) return NULL;
    ptr->states = setCreate(copyState,freeState,compareState);
    ptr->judges = setCreate(copyJudge,freeJudge,compareJudge);
}

EurovisionResult eurovisionAddState(Eurovision eurovision, int stateId,
                                    const char *stateName,
                                    const char *songName){
    if(!eurovision || !stateName || !songName){
        return EUROVISION_NULL_ARGUMENT;
    }
    State tmp = stateCreate(stateId,stateName,songName);
    SetResult result = setAdd(eurovision->states,tmp);
    if(result == SET_ITEM_ALREADY_EXISTS) return EUROVISION_STATE_ALREADY_EXIST;
    if(result == SET_OUT_OF_MEMORY) return EUROVISION_OUT_OF_MEMORY;
    return EUROVISION_SUCCESS;
}


