#include "eurovision.h"
#include "state.h"
#include "judge.h"
#include "stateScore.h"
#define JUDGE_NUMBER_OF_VOTES 10
#define STATE_NUMBER_OF_VOTES 10
#define REMOVE_STATE "remove"
#define ASCII_SMALL_A_VALUE 97
#define ASCII_SMALL_Z_VALUE 122
#define ASCII_SPACE_VALUE 32
#define DUSPWA 12
#define SECOND_PLACE 10

static EurovisionResult AddOrRemoveVote(Eurovision eurovision, int stateGiver,
                                        int stateTaker,VoteAddOrRemove choice);
static int getScoreByPlace(int place);
static Judge getJudge(Set judges ,int judgeId);
static void getJudgesWhoVotedForState(Eurovision eurovision,State state,Judge* judges);
static void initializeJudgeArray(Judge* array, int length);

static bool checkValidStateId(Set states ,const int* array);
static bool checkString(const char* str);
static bool checkJudgeArray(const int* array);

static SetElement copyState (SetElement state);
static void freeState(SetElement state);
static int compareState(SetElement state1, SetElement state2);

static SetElement copyJudge (SetElement judge);
static void freeJudge(SetElement judge);
static int compareJudge(SetElement judge1, SetElement judge2);

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
// the two functions below seem similar but the only difference is in the macro SER_FOREACH.
// we didnt want to put this whole function in macro and we cant change SET_FOREACH.
static double getAverageOfStateScores(Set states,int stateId){
    int sum = 0;
    int numberOfStates = setGetSize(states);
    SET_FOREACH(State,stateIterator,states){
        int* votes = stateGetVotes(stateIterator);
        for(int i=0;i<STATE_NUMBER_OF_VOTES;i++){
            if(votes[i]==stateId){
                sum += getScoreByPlace(i);
            }
        }
    }
    return (double)sum/numberOfStates;
}


static double getAverageOfJudgeScore(Set judges, int stateId){
    int sum = 0;
    int numberOfJudges = setGetSize(judges);
    SET_FOREACH(Judge,judgeIterator,judges){
        int* votes = judgeGetVotes(judgeIterator);
        for(int i=0;i<JUDGE_NUMBER_OF_VOTES;i++){
            if(votes[i]==stateId){
                sum += getScoreByPlace(i);
            }
        }
    }
    return (double)sum/numberOfJudges;
}

static int getScoreByPlace(int place){
    if(place==0) return DUSPWA;
    if(place==1) return SECOND_PLACE;
    return SECOND_PLACE - place;
}
static SetElement copyStateScore(SetElement stateScore) {
    if(stateScore==NULL) return NULL;
    return stateScoreCopy((StateScore)stateScore);
}

static void freeStateScore(SetElement stateScore) {
    stateScoreDestroy((StateScore)stateScore);
}

static int compareStateScores(SetElement stateScore1, SetElement stateScore2) {
    assert(stateScore1!=NULL || stateScore2!=NULL);
    return stateScoreCompare((StateScore)stateScore1, (StateScore)stateScore2);
}

static ListElement copyFinalistNames(ListElement name) {
    assert(name!=NULL);
    char* newName= malloc(sizeof(char)*strlen((char*)name)+1);
    strcpy(newName,(char*)name);
    return newName;
}

static void freeFinalistNames(ListElement stateScore) {
    free((StateScore)stateScore);
}


List eurovisionRunContest(Eurovision eurovision, int audiencePercent) {
    int numOfStates=setGetSize(eurovision->states);
    int* stateIds=malloc(sizeof(int)*numOfStates);
    char** stateNames=malloc(sizeof(char*)*numOfStates);
    if (stateIds==NULL || stateNames==NULL) return NULL;
    int i=0;
    SET_FOREACH(State ,stateIterator,eurovision->states) {
        stateIds[i]=stateGetId(stateIterator);
        stateNames[i]=malloc(sizeof(char)*strlen(stateGetName(stateIterator))+1);
        strcpy(stateNames[i],stateGetName(stateIterator));
        i++;
    }
    Set finalScores=setCreate(copyStateScore,freeStateScore,compareStateScores);
    double averageOfStateScores=0,averageOfJudgeScores=0;
    for (i=0; i<numOfStates; i++) {
        averageOfStateScores=getAverageOfStateScores(eurovision->states,stateIds[i]);
        averageOfJudgeScores=getAverageOfJudgeScore(eurovision->judges,stateIds[i]);
        StateScore tmp=stateScoreCreate(stateIds[i],stateNames[i],averageOfStateScores,averageOfJudgeScores,audiencePercent);
        setAdd(finalScores,tmp);
        stateScoreDestroy(tmp);
    }
    List finalistNames=listCreate(copyFinalistNames,freeFinalistNames);
    SET_FOREACH(StateScore ,stateScoreIterator,finalScores) {
        listInsertLast(finalistNames,stateScoreGetName(stateScoreIterator));
    }


    free(stateIds);
    for(int j=0;j<numOfStates;j++){
        free(stateNames[j]);
    }
    free(stateNames);
    setDestroy(finalScores);
    return finalistNames;
}
