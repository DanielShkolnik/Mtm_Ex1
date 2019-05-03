
#ifndef PART_4_JUDGE_H
#define PART_4_JUDGE_H
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

/** Type for defining the Judge struct */
typedef struct Judge_t *Judge;

/** Type used for returning error codes from Judge functions */
typedef enum {
    JUDGE_SUCCESS,
    JUDGE_OUT_OF_MEMORY,
    JUDGE_NULL_ARGUMENT,
    JUDGE_ITEM_ALREADY_EXISTS,
    JUDGE_ITEM_DOES_NOT_EXIST
} JudgeResult;

/**
 * Allocates a new Judge.
 * Create Judge with id number (int), judge name (string)
 * and votes array with 10 state id numbers that is sorted by the highest
 * state score first.
 *
 * @param id = id number of the judge
 * @param name = name of the judge
 * @param votes = votes array with 10 cells
 * @return new Judge pointer with the params inserted
 */
Judge judgeCreate(int id,const char *name,int *votes);

/**
 * judgeDestroy: Deallocates an existing Judge.
 * Clears all elements.
 *
 * @param judge Target Judge to be deallocated. If list is NULL nothing will be
 * done.
 *
 * @return
 * JUDGE_NULL_ARGUMENT if Judge pointer is NULL
 * JUDGE_SUCCESS if the Judge destroyed successfully.
 */
JudgeResult judgeDestroy(Judge judge);

/**
 * Compare 2 Judges by their id number.
 *
 * @param judge1 to compare
 * @param judge2 to compare
 * @return int number that is negative if judge2 bigger than judge1, equals zero
 * if the 2 judges id is the same or positive if judge1 bigger than judge2.
 */
int judgeCompare(Judge judge1, Judge judge2);

/**
*Creates a copy of target judge.
*
* The new copy will contain all the elements from the source judge in the same order
*
* @param judge The target judge to copy
* @return
* NULL if a NULL was sent or a memory allocation failed.
* A Judge containing the same elements with same order.
*
 */
Judge judgeCopy(Judge judge);

/**
 * Compare 2 Judges Id.
 *
 * @param judgeId1 to compare
 * @param judgeId2 to compare
 * @return int number that is negative if judgeId2 bigger than judgeId1, equals zero
 * if the 2 judges id is the same or positive if judgeId1 bigger than judgeId2.
 */
int judgeCompareById(int judgeId1, int judgeId2);

/**
 * Returns the judge Id.
 *
 * @param judge The Judge for which to get the id
 * @return The judge id from the Judge inserted
 */
int judgeGetId(Judge judge);

/**
 * Returns the judge votes array.
 *
 * @param judge The Judge for which to get the votes array
 * @return The judge votes array from the Judge inserted
 */
int* judgeGetVotes(Judge judge);



#endif //PART_4_JUDGE_H
