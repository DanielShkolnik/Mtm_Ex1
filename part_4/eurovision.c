#include "eurovision.h"
#include "state.h"
#include "judge.h"
#include "stateScore.h"
#include "friendlyStates.h"
#define JUDGE_NUMBER_OF_VOTES 10
#define STATE_NUMBER_OF_VOTES 10
#define REMOVE_STATE "remove"
#define ASCII_SMALL_A_VALUE 97
#define ASCII_SMALL_Z_VALUE 122
#define ASCII_SPACE_VALUE 32
#define DUSPWA 12
#define SECOND_PLACE 10
#define PERCENTAGE 100

static EurovisionResult AddOrRemoveVote(Eurovision eurovision, int stateGiver,
                                        int stateTaker,VoteAddOrRemove choice);
static int getScoreByPlace(int place);
static Judge getJudge(Set judges ,int judgeId);
static void getJudgesWhoVotedForState(Eurovision eurovision,State state,Judge* judges);
static void initializeJudgeArray(Judge* array, int length);
static State getStateById(Set states, int stateId);
static double getAverageOfStateScores(Set states,int stateId);
static double getAverageOfJudgeScore(Set judges, int stateId);
static char* generateFriendlyStatesString(FriendlyStates friendlyStates);

static bool checkValidStateId(Set states ,const int* array);
static bool checkString(const char* str);
static bool checkJudgeArray(const int* array);

static SetElement copyState (SetElement state);
static void freeState(SetElement state);
static int compareState(SetElement state1, SetElement state2);

static SetElement copyJudge (SetElement judge);
static void freeJudge(SetElement judge);
static int compareJudge(SetElement judge1, SetElement judge2);

static SetElement copyStateScore(SetElement stateScore);
static void freeStateScore(SetElement stateScore);
static int compareStateScores(SetElement stateScore1, SetElement stateScore2);

static ListElement copyFinalistNames(ListElement name);
static void freeFinalistNames(ListElement stateScore);

static SetElement copyFriendlyStates(SetElement friendlyStates);
static void freeFriendlyStates(SetElement friendlyStates);
static int compareFriendlyStates(SetElement friendlyStates1, SetElement friendlyStates2);

static ListElement copyFriendlyStatesList(ListElement friendlyStatesStr);
static void freeFriendlyStatesList(ListElement friendlyStatesStr);

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
        if ((str[i]>=ASCII_SMALL_A_VALUE && str[i]<=ASCII_SMALL_Z_VALUE) || str[i]==ASCII_SPACE_VALUE){
            continue;
        }else{
            return false;
        }
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
    if (ptr->states==NULL || ptr->judges==NULL) {
        eurovisionDestroy(ptr);
        return NULL;
    }
    return ptr;
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
    if (!checkString(judgeName)) return EUROVISION_INVALID_NAME;
    if (!checkValidStateId(eurovision->states,judgeResults)) return EUROVISION_STATE_NOT_EXIST;
    Judge newJudge = judgeCreate(judgeId,judgeName,judgeResults);
    if (newJudge==NULL) return EUROVISION_OUT_OF_MEMORY;
    SetResult setAddResult=setAdd(eurovision->judges,newJudge);
    judgeDestroy(newJudge);
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
    if(!tmp){
        stateDestroy(tmp);
        return EUROVISION_OUT_OF_MEMORY;
    }
    SetResult result = setAdd(eurovision->states,tmp);
    stateDestroy(tmp);
    if(result == SET_ITEM_ALREADY_EXISTS) return EUROVISION_STATE_ALREADY_EXIST;
    if(result == SET_OUT_OF_MEMORY) return EUROVISION_OUT_OF_MEMORY;
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
    if(result==SET_ITEM_DOES_NOT_EXIST){
        stateDestroy(tmp);
        return EUROVISION_STATE_NOT_EXIST;
    }
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
    State tmp1 = stateCreate(stateGiver,REMOVE_STATE,REMOVE_STATE);
    State tmp2 = stateCreate(stateTaker,REMOVE_STATE,REMOVE_STATE);
    if(!setIsIn(eurovision->states,tmp1) || !setIsIn(eurovision->states,tmp2)){
        stateDestroy(tmp1);
        stateDestroy(tmp2);
        return EUROVISION_STATE_NOT_EXIST;
    }
    if(stateGiver==stateTaker) return EUROVISION_SAME_STATE;
    SET_FOREACH(State,state,eurovision->states){
        if(stateGetId(state)==stateGiver){
            stateAddOrRemoveVote(state,stateTaker,choice);
            break;
        }
    }
    stateDestroy(tmp1);
    stateDestroy(tmp2);
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
            if(votes[i]==stateId && votes[i]>=0){
                sum += getScoreByPlace(i);
            }
        }
        free(votes);
    }
    return (double)sum/(numberOfStates-1);//If average NEED EDIT
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
    return (double)sum/numberOfJudges;//If average NEED EDIT
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
    if(!newName) return  NULL;
    strcpy(newName,(char*)name);
    return newName;
}

static void freeFinalistNames(ListElement stateScore) {
    free((char*)stateScore);
}


List eurovisionRunContest(Eurovision eurovision, int audiencePercent) {
    if (audiencePercent<0 || audiencePercent>PERCENTAGE || eurovision==NULL) return NULL;
    int numOfStates=setGetSize(eurovision->states);
    int* stateIds=malloc(sizeof(int)*numOfStates);
    char** stateNames=malloc(sizeof(char*)*numOfStates);
    if (stateIds==NULL || stateNames==NULL) return NULL;
    int i=0;
    // Gets an array of state ids and state names (all states in eurovision)
    SET_FOREACH(State ,stateIterator,eurovision->states) {
        stateIds[i]=stateGetId(stateIterator);
        stateNames[i]=malloc(sizeof(char)*strlen(stateGetName(stateIterator))+1);
        if (stateNames[i]==NULL) return NULL;
        strcpy(stateNames[i],stateGetName(stateIterator));
        i++;
    }
    // Create a sorted set of all the states. The set is sorted by the final score
    Set finalScores=setCreate(copyStateScore,freeStateScore,compareStateScores);
    if (finalScores==NULL) return NULL;
    double averageOfStateScores=0,averageOfJudgeScores=0;
    for (i=0; i<numOfStates; i++) {
        averageOfStateScores=getAverageOfStateScores(eurovision->states,stateIds[i]);
        averageOfJudgeScores=getAverageOfJudgeScore(eurovision->judges,stateIds[i]);
        StateScore tmp=stateScoreCreate(stateIds[i],stateNames[i],averageOfStateScores,averageOfJudgeScores,audiencePercent);
        if (tmp==NULL) return NULL;
        setAdd(finalScores,tmp);
        stateScoreDestroy(tmp);
    }

    // This is a list of the states ordered by their score
    List finalistNames=listCreate(copyFinalistNames,freeFinalistNames);

    if (finalistNames==NULL) return NULL;
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


List eurovisionRunAudienceFavorite(Eurovision eurovision){
    return eurovisionRunContest(eurovision,PERCENTAGE);
}

static State getStateById(Set states, int stateId) {
    if (states==NULL || stateId<0) return NULL;
    SET_FOREACH(State ,stateIterator,states){
        if (stateGetId(stateIterator)==stateId) return stateIterator;
    }
    return NULL;
}






static SetElement copyFriendlyStates(SetElement friendlyStates) {
    if(friendlyStates==NULL) return NULL;
    return friendlyStatesCopy((FriendlyStates)friendlyStates);
}

static void freeFriendlyStates(SetElement friendlyStates) {
    friendlyStatesDestroy((FriendlyStates)friendlyStates);
}

static int compareFriendlyStates(SetElement friendlyStates1, SetElement friendlyStates2) {
    assert(friendlyStates1!=NULL || friendlyStates2!=NULL);
    return friendlyStatesCompare((FriendlyStates)friendlyStates1, (FriendlyStates)friendlyStates2);
}



static char* generateFriendlyStatesString(FriendlyStates friendlyStates) {
    assert(friendlyStates!=NULL);
    char* newName1= malloc(sizeof(char)*strlen(friendlyStatesGetName1(friendlyStates))+1);
    char* newName2= malloc(sizeof(char)*strlen(friendlyStatesGetName2(friendlyStates))+1);
    if(!newName1 || !newName2) return NULL;
    strcpy(newName1,friendlyStatesGetName1(friendlyStates));
    strcpy(newName2,friendlyStatesGetName2(friendlyStates));
    char* newStr=" - ";
    char* finalName=malloc(sizeof(char)*(strlen(newName1)+strlen(newName2)+strlen(newStr))+1);
    if(!finalName) return NULL;
    strcpy(finalName,newName1);
    strncat(finalName,newStr,strlen(newStr));
    strncat(finalName,newName2,strlen(newName2));
    free(newName1);
    free(newName2);
    return finalName;
}

static ListElement copyFriendlyStatesList(ListElement friendlyStatesStr) {
    assert(friendlyStatesStr!=NULL);
    char* newName= malloc(sizeof(char)*strlen((char*)friendlyStatesStr)+1);
    strcpy(newName,(char*)friendlyStatesStr);
    return newName;
}

static void freeFriendlyStatesList(ListElement friendlyStatesStr) {
    free((char*)friendlyStatesStr);
}


List eurovisionRunGetFriendlyStates(Eurovision eurovision){
    Set tmp=setCopy(eurovision->states);
    if (tmp==NULL) return NULL;
    int topVoteId1=0, topVoteId2=0;
    // Creating a set to store the frendly states and sort them by state1 name (alphabetical order)
    Set friendlyStatesSet=setCreate(copyFriendlyStates,freeFriendlyStates,compareFriendlyStates);
    // Gets the top voted state (stateIterator) for each state and sees if the top voted state voted (at first place) for stateIterator.
    SET_FOREACH(State ,stateIterator,tmp){
        int *topVoteId1Array,*topVoteId2Array;
        topVoteId1Array=stateGetVotes(stateIterator);
        topVoteId1=topVoteId1Array[0];
        if(topVoteId1>=0){
            State stateTmp=getStateById(eurovision->states,topVoteId1);
            topVoteId2Array=stateGetVotes(stateTmp);
            topVoteId2=topVoteId2Array[0];
            if (topVoteId2>=0 && topVoteId1==stateGetId(stateTmp) && topVoteId2==stateGetId(stateIterator)) {
                FriendlyStates friendlyStatesTmp=friendlyStatesCreate(stateGetName(stateIterator),stateGetName(stateTmp));
                setAdd(friendlyStatesSet,friendlyStatesTmp);
                friendlyStatesDestroy(friendlyStatesTmp);
            }
            free(topVoteId2Array);
        }
        free(topVoteId1Array);
    }
    // Creates a list ordered alphabeticaly for frendly states.
    List friendlyStatesList=listCreate(copyFriendlyStatesList,freeFriendlyStatesList);
    if (friendlyStatesList==NULL) return NULL;
    SET_FOREACH(FriendlyStates ,friendlyStatesIterator,friendlyStatesSet) {
        char* finalFriendlyStatesString=generateFriendlyStatesString(friendlyStatesIterator);
        listInsertLast(friendlyStatesList,finalFriendlyStatesString);
        free(finalFriendlyStatesString);
    }
    setDestroy(tmp);
    setDestroy(friendlyStatesSet);
    return friendlyStatesList;
}
