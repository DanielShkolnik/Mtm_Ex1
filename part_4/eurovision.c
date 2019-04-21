#include "eurovision.h"
#include "state.h"
#include "judge.h"
#define JUDGE_NUMBER_OF_VOTES 10
#define REMOVE_STATE "remove"

struct eurovision_t {
    Set states;
    Set judges;
};

static bool checkString(const char* str){
    for (int i=0; str[i]!=0 ; i++) {
        if ((str[i]<97 || str[i]>122) || str[i]!=32) return false;
    }
    return true;
}

static bool checkJudgeArray(const int* array) {
    for (int i=0; i<JUDGE_NUMBER_OF_VOTES; i++) {
        if (array[i]<0) return false;
    }
    return true;
}

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

void eurovisionDestroy(Eurovision eurovision) {
    setDestroy(eurovision->states);
    setDestroy(eurovision->judges);
    free(eurovision);
}

EurovisionResult eurovisionAddJudge(Eurovision eurovision, int judgeId,
                                    const char *judgeName,
                                    int *judgeResults) {
    if (eurovision==NULL || judgeName==NULL || judgeResults==NULL) return EUROVISION_NULL_ARGUMENT;
    Judge newJudge = judgeCreate(judgeId,judgeName,judgeResults);
    if (newJudge==NULL) return EUROVISION_OUT_OF_MEMORY;
    SetResult setAddResult=setAdd(eurovision->judges,newJudge);
    if (setAddResult==SET_OUT_OF_MEMORY) return EUROVISION_OUT_OF_MEMORY;
    if (setAddResult==SET_ITEM_ALREADY_EXISTS) return EUROVISION_JUDGE_ALREADY_EXIST;
    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionAddState(Eurovision eurovision, int stateId,
                                    const char *stateName,
                                    const char *songName){
    if(!eurovision || !stateName || !songName){
        return EUROVISION_NULL_ARGUMENT;
    }
    if(stateId < 0) return EUROVISION_INVALID_ID;
    if(!checkString(stateName)) return EUROVISION_INVALID_NAME;
    if(!checkString(songName)) return EUROVISION_INVALID_NAME;
    State tmp = stateCreate(stateId,stateName,songName);
    if(!tmp) return EUROVISION_OUT_OF_MEMORY;
    SetResult result = setAdd(eurovision->states,tmp);
    if(result == SET_ITEM_ALREADY_EXISTS) return EUROVISION_STATE_ALREADY_EXIST;
    if(result == SET_OUT_OF_MEMORY) return EUROVISION_OUT_OF_MEMORY;
    stateDestroy(tmp);
    return EUROVISION_SUCCESS;
}
static void getJudgeIdsWhoVotedForState(Eurovision eurovision,State state,int* judgesId){
    SET_FOREACH(Judge,judge,eurovision->judges){
        for(int i=0;i<10;i++){

        }
    }
}
EurovisionResult eurovisionRemoveState(Eurovision eurovision, int stateId){
    if(!eurovision) return EUROVISION_NULL_ARGUMENT;
    if(stateId<0) return EUROVISION_INVALID_ID;
    State tmp = stateCreate(stateId,REMOVE_STATE,REMOVE_STATE);
    SetResult result = setRemove(eurovision->states,tmp);
    if(result==SET_ITEM_DOES_NOT_EXIST) return EUROVISION_STATE_NOT_EXIST;

}