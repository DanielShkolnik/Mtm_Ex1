#include "eurovision.h"
#include "state.h"
#include "judge.h"
#define JUDGE_NUMBER_OF_VOTES 10
#define REMOVE_STATE "remove"
#define ASCII_SMALL_A_VALUE 97
#define ASCII_SMALL_Z_VALUE 122
#define ASCII_SPACE_VALUE 32
static EurovisionResult AddOrRemoveVote(Eurovision eurovision, int stateGiver,
                                        int stateTaker,VoteAddOrRemove choice);
struct eurovision_t {
    Set states;
    Set judges;
};

static Judge getJudge(Set judges ,int judgeId) {
    SET_FOREACH(Judge,iterator,judges) {
        if (judgeCompareById(judgeGetId(iterator),judgeId)==0) return iterator;
    }
    return NULL;
}

static bool checkValidStateId(Set states ,const int* array) {
    for (int i=0; i<JUDGE_NUMBER_OF_VOTES; i++) {
        State tmp = stateCreate(array[i],REMOVE_STATE,REMOVE_STATE);
        if (!setIsIn(states,tmp)) {
            stateDestroy(tmp);
            return false;
        }
        stateDestroy(tmp);
    }
    return true;
}

static bool checkString(const char* str){
    for (int i=0; str[i]!=0 ; i++) {
        if ((str[i]<ASCII_SMALL_A_VALUE || str[i]>ASCII_SMALL_Z_VALUE) || str[i]!=ASCII_SPACE_VALUE) return false;
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
    if (judgeId<0 || !checkJudgeArray(judgeResults)) return EUROVISION_INVALID_ID;
    if (!checkValidStateId(eurovision->states,judgeResults)) return EUROVISION_STATE_NOT_EXIST;
    if (!checkString(judgeName)) return EUROVISION_INVALID_NAME;
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
    if(!checkString(stateName) || !checkString(songName)) return EUROVISION_INVALID_NAME;
    State tmp = stateCreate(stateId,stateName,songName);
    if(!tmp) return EUROVISION_OUT_OF_MEMORY;
    SetResult result = setAdd(eurovision->states,tmp);
    if(result == SET_ITEM_ALREADY_EXISTS) return EUROVISION_STATE_ALREADY_EXIST;
    if(result == SET_OUT_OF_MEMORY) return EUROVISION_OUT_OF_MEMORY;
    stateDestroy(tmp);
    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionRemoveJudge(Eurovision eurovision, int judgeId) {
    if (eurovision==NULL) return EUROVISION_NULL_ARGUMENT;
    if (judgeId<0) return EUROVISION_INVALID_ID;
    Judge judgeToRemove=getJudge(eurovision->judges,judgeId);
    if (judgeToRemove==NULL) return EUROVISION_JUDGE_NOT_EXIST;
    setRemove(eurovision->judges,judgeToRemove);
    return EUROVISION_SUCCESS;
}


static void getJudgesWhoVotedForState(Eurovision eurovision,State state,Judge* judges){
    int j = 0;
    SET_FOREACH(Judge,judge,eurovision->judges){
        int *votes = judgeGetVotes(judge);
        for(int i=0;i<JUDGE_NUMBER_OF_VOTES;i++){
            if(stateGetId(state)==votes[i]){
                judges[j] = judge;
                j++;
            }
        }
    }
}
static void initializeJudgeArray(Judge* array, int length){
    for(int i=0;i<length;i++){
        array[i]=NULL;
    }
}

EurovisionResult eurovisionRemoveState(Eurovision eurovision, int stateId){
    if(!eurovision) return EUROVISION_NULL_ARGUMENT;
    if(stateId<0) return EUROVISION_INVALID_ID;
    State tmp = stateCreate(stateId,REMOVE_STATE,REMOVE_STATE);
    SetResult result = setRemove(eurovision->states,tmp);
    if(result==SET_ITEM_DOES_NOT_EXIST) return EUROVISION_STATE_NOT_EXIST;
    int size = setGetSize(eurovision->judges);
    Judge* removeJudges = malloc(sizeof(Judge)*size);
    initializeJudgeArray(removeJudges,size);
    getJudgesWhoVotedForState(eurovision,tmp,removeJudges);
    for(int i=0;i<size;i++){
        if(removeJudges[i]==NULL){
            break;
        }
        setRemove(eurovision->judges,removeJudges[i]);
    }
    SET_FOREACH(State,state,eurovision->states){
        stateRemoveVotedState(state,tmp);
    }
    stateDestroy(tmp);
    free(removeJudges);
    return EUROVISION_SUCCESS;
}

EurovisionResult eurovisionAddVote(Eurovision eurovision, int stateGiver,
                                   int stateTaker){
    return AddOrRemoveVote(eurovision,stateGiver,stateTaker,VOTE_ADD);
}

EurovisionResult eurovisionRemoveVote(Eurovision eurovision, int stateGiver,
                                      int stateTaker){
    return AddOrRemoveVote(eurovision,stateGiver,stateTaker,VOTE_REMOVE);
}

static EurovisionResult AddOrRemoveVote(Eurovision eurovision, int stateGiver,
                                        int stateTaker,VoteAddOrRemove choice){
    if(!eurovision) return EUROVISION_NULL_ARGUMENT;
    if(stateGiver < 0 || stateTaker < 0) return EUROVISION_INVALID_ID;
    if(stateGiver==stateTaker) return EUROVISION_SAME_STATE;
    SET_FOREACH(State,state,eurovision->states){
        if(stateGetId(state)==stateGiver){
            stateAddOrRemoveVote(state,stateTaker,choice);
            break;
        }
    }
    return EUROVISION_SUCCESS;
}

