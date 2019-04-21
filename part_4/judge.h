
#ifndef PART_4_JUDGE_H
#define PART_4_JUDGE_H
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"


typedef struct Judge_t *Judge;

typedef enum {
    JUDGE_SUCCESS,
    JUDGE_OUT_OF_MEMORY,
    JUDGE_NULL_ARGUMENT,
    JUDGE_ITEM_ALREADY_EXISTS,
    JUDGE_ITEM_DOES_NOT_EXIST
} JudgeResult;

Judge judgeCreate(int id, char *name,int *votes);
JudgeResult judgeDestroy(Judge judge);
int judgeCompare(Judge judge1, Judge judge2);
Judge judgeCopy(Judge judge);




#endif //PART_4_JUDGE_H
