#include "judge.h"
#define JUDGE_NUMBER_OF_VOTES 10

struct Judge_t{
    int id;
    char *name;
    int *votes;
};

static void copyArray (int* votesCopy, const int* votes);

Judge judgeCreate(int id, const char *name,int *votes){
    Judge ptrJudge = malloc(sizeof(*ptrJudge));
    if(!ptrJudge){
        return NULL;
    }
    ptrJudge->id=id;
    ptrJudge->name = malloc(sizeof(char)*strlen(name)+1);
    if (ptrJudge->name==NULL) return NULL;
    strcpy(ptrJudge->name,name);
    int* ptrVotes = malloc(sizeof(int)*JUDGE_NUMBER_OF_VOTES);
    if(!ptrVotes){
        return NULL;
    }
    copyArray(ptrVotes, votes);
    ptrJudge->votes=ptrVotes;
    return ptrJudge;
}

/**
 *Creates a copy of target array.
 *
 * The new copy will contain all the cells from the source array in the same order
 *
 * @param array The target array to copy
 * @return A array pointer that containing the same cells with same order.
 */
static void copyArray (int* votesCopy, const int* votes) {
    for (int i=0; i<JUDGE_NUMBER_OF_VOTES; i++) {
        votesCopy[i]=votes[i];
    }
}

JudgeResult judgeDestroy(Judge judge){
    if(judge==NULL) return JUDGE_NULL_ARGUMENT;
    free(judge->name);
    free(judge->votes);
    free(judge);
    return JUDGE_SUCCESS;
}

int judgeCompare(Judge judge1, Judge judge2) {
    assert(judge1!=NULL && judge2!=NULL);
    return judge1->id-judge2->id;
}

Judge judgeCopy(Judge judge){
    if (judge==NULL) return NULL;
    return judgeCreate(judge->id, judge->name, judge->votes);
}

int judgeCompareById(int judgeId1, int judgeId2) {
    return judgeId1-judgeId2;
}

int judgeGetId(Judge judge) {
    return judge->id;
}

int* judgeGetVotes(Judge judge) {
    return judge->votes;
}
