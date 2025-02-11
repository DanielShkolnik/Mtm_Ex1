#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../list.h"
#include "../eurovision.h"
#include "eurovisionTests.h"

#define POINTS_OPTIONS_NUMBER 10

#define CHECK(b,res)                            \
  if((b) != (res)) do{                          \
      printf("fail: %s != %s\n", #b, #res);     \
      eurovisionDestroy(eurovision);            \
      return false;                             \
    } while(0)

#define CHECK_WITH_FREE(b,res,f)                \
  if((b) != (res)) do{                          \
      printf("fail: %s != %s\n", #b, #res);     \
      eurovisionDestroy(eurovision);            \
      free(f);                                  \
      return false;                             \
    } while(0)

static Eurovision setupEurovision() {
  Eurovision eurovision = eurovisionCreate();
  assert(eurovision);
  return eurovision;
}

static void setupEurovisionStates(Eurovision eurovision) {
  eurovisionAddState(eurovision, 0, "israel", "home");
  eurovisionAddState(eurovision, 1, "malta", "chameleon");
  eurovisionAddState(eurovision, 2, "croatia", "the dream");
  eurovisionAddState(eurovision, 3, "russia", "scream");
  eurovisionAddState(eurovision, 4, "moldova", "stay");
  eurovisionAddState(eurovision, 5, "cyprus", "replay");
  eurovisionAddState(eurovision, 6, "spain", "la venda");
  eurovisionAddState(eurovision, 7, "italy", "soldi");
  eurovisionAddState(eurovision, 8, "france", "roi");
  eurovisionAddState(eurovision, 9, "germany", "sister");
  eurovisionAddState(eurovision, 10, "united kingdom", "bigger than us");
  eurovisionAddState(eurovision, 11, "armenia", "walking out");
  eurovisionAddState(eurovision, 12, "austria", "limits");
  eurovisionAddState(eurovision, 13, "ireland", "twenty two");
  eurovisionAddState(eurovision, 14, "netherlands", "arcade");
  eurovisionAddState(eurovision, 15, "sweden", "too late for love");
}

static int *makeJudgeResults(int id0, int id1, int id2, int id3, int id4,
                             int id5, int id6, int id7, int id8, int id9) {
  int *results = malloc(POINTS_OPTIONS_NUMBER * sizeof(*results));
  assert(results);
  results[0] = id0;
  results[1] = id1;
  results[2] = id2;
  results[3] = id3;
  results[4] = id4;
  results[5] = id5;
  results[6] = id6;
  results[7] = id7;
  results[8] = id8;
  results[9] = id9;
  return results;
}

/** total judge result: (stateid: score)
 * 0: (12 + 2  + 0) / 3  = 14 / 3 = 4.6667
 * 1: (10 + 0  + 0) / 3  = 10 / 3 = 3.3333
 * 2: (8  + 1  + 0) / 3  =  9 / 3 = 3
 * 3: (7  + 0  + 7) / 3  = 14 / 3 = 4.6667
 * 4: (6  + 6  + 6) / 3  = 18 / 3 = 6
 * 5: (5  + 5  + 5) / 3  = 15 / 3 = 5
 * 6: (4  + 4  + 4) / 3  = 12 / 3 = 4
 * 7: (3  + 0  + 3) / 3  =  6 / 3 = 2
 * 8: (2  + 7  + 2) / 3  = 11 / 3 = 3.6667
 * 9: (1  + 0  + 1) / 3  =  2 / 3 = 0.6667
 * 10:(0  + 8  + 12) / 3 = 20 / 3 = 6.6667
 * 11:(0  + 0  + 10) / 3 = 10 / 3 = 3.3333
 * 12:(0  + 0  + 8) / 3  =  8 / 3 = 2.6667
 * 13:(0  + 10 + 0) / 3  = 10 / 3 = 3.3333
 * 14:(0  + 12 + 0) / 3  = 12 / 3 = 4
 * 15:(0  + 3  + 0) / 3  =  3 / 3 = 1
 */
static void setupEurovisionJudges(Eurovision eurovision) {
  int *results;
  results = makeJudgeResults( 0,  1,  2, 3, 4, 5, 6,  7, 8, 9);
  eurovisionAddJudge(eurovision, 0, "olsen", results);
  free(results);
  results = makeJudgeResults(14, 13, 10, 8, 4, 5, 6, 15, 0, 2);
  eurovisionAddJudge(eurovision, 1, "tanel", results);
  free(results);
  results = makeJudgeResults(10, 11, 12, 3, 4, 5, 6,  7, 8, 9);
  eurovisionAddJudge(eurovision, 2, "marie", results);
  free(results);
}

static void giveVotes(Eurovision eurovision, int giver, int taker, int votes) {
  for (int i = 0; i < votes; i++) {
    if (eurovisionAddVote(eurovision, giver, taker) != EUROVISION_SUCCESS) {
      printf("error in eurovisionAddVote %d -> %d\n", giver, taker);
    }
  }
}

static void setupEurovisionVotes(Eurovision eurovision) {
  giveVotes(eurovision, 1, 12, 4);
  giveVotes(eurovision, 2, 8, 2);
  giveVotes(eurovision, 3, 4, 1);
}

/** total voters result:
 * 1:  (0  + 12 + 0  + 0) / 16  = 12 / 16 = 0.75
 * 2:  (12 + 0  + 8  + 0) / 16  = 20 / 16 = 1.25
 * 3:  (10 + 6  + 0  + 12) / 16 = 28 / 16 = 1.75
 * 4:  (8  + 7  + 12 + 0) / 16  = 27 / 16 = 1.6875
 * 5:  (7  + 8  + 4  + 0) / 16  = 19 / 16 = 1.1875
 * 6:  (6  + 10 + 7  + 0) / 16  = 23 / 16 = 1.4375
 * 7:  (5  + 5  + 5  + 0) / 16  = 15 / 16 = 0.9375
 * 8:  (4  + 0  + 6  + 0) / 16  = 10 / 16 = 0.625
 * 9:  (3  + 0  + 3  + 0) / 16  =  6 / 16 = 0.375
 * 10: (2  + 0  + 10 + 0) / 16  = 12 / 16 = 0.75
 * 11: (1  + 0  + 0  + 0) / 16  =  1 / 16 = 0.0625
 * 13: (0  + 0  + 1  + 0) / 16  =  1 / 16 = 0.0625
 * 14: (0  + 0  + 2  + 0) / 16  =  2 / 16 = 0.125
 */
static void setupEurovisionVotes2(Eurovision eurovision) {
  giveVotes(eurovision, 1, 2, 20);
  giveVotes(eurovision, 1, 3, 18);
  giveVotes(eurovision, 1, 5, 16);
  giveVotes(eurovision, 1, 4, 14);
  giveVotes(eurovision, 1, 6, 12);
  giveVotes(eurovision, 1, 7, 10);
  giveVotes(eurovision, 1, 8, 8);
  giveVotes(eurovision, 1, 9, 6);
  giveVotes(eurovision, 1, 10, 5);
  giveVotes(eurovision, 1, 11, 4);
  giveVotes(eurovision, 1, 12, 3);
  giveVotes(eurovision, 1, 13, 2);
  giveVotes(eurovision, 1, 14, 1);

  giveVotes(eurovision, 2, 1, 20);
  giveVotes(eurovision, 2, 6, 18);
  giveVotes(eurovision, 2, 5, 16);
  giveVotes(eurovision, 2, 4, 14);
  giveVotes(eurovision, 2, 3, 12);
  giveVotes(eurovision, 2, 7, 10);

  giveVotes(eurovision, 3, 4, 14);
  giveVotes(eurovision, 3, 10, 13);
  giveVotes(eurovision, 3, 2, 12);
  giveVotes(eurovision, 3, 8, 11);
  giveVotes(eurovision, 3, 6, 11);
  giveVotes(eurovision, 3, 7, 10);
  giveVotes(eurovision, 3, 5, 9);
  giveVotes(eurovision, 3, 9, 8);
  giveVotes(eurovision, 3, 14, 7);
  giveVotes(eurovision, 3, 13, 6);
  giveVotes(eurovision, 3, 12, 5);
  giveVotes(eurovision, 3, 11, 4);

  giveVotes(eurovision, 4, 3, 2);
}

bool testAddState() {
  Eurovision eurovision = setupEurovision();
  CHECK(eurovisionAddState(eurovision, 0, "israel", "home"), EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision, 1, "malta", "chameleon"), EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision, 0, "croatia", "the dream"), EUROVISION_STATE_ALREADY_EXIST);
  CHECK(eurovisionAddState(eurovision, 0, "israel", "home"), EUROVISION_STATE_ALREADY_EXIST);
  CHECK(eurovisionAddState(eurovision, -1, "croatia", "the dream"), EUROVISION_INVALID_ID);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveState() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionRemoveState(eurovision, 24), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveState(eurovision, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveState(eurovision, 1), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveState(eurovision, 1), EUROVISION_STATE_NOT_EXIST);
  eurovisionDestroy(eurovision);
  return true;
}

bool testAddJudge() {
  int *results;
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionAddJudge(eurovision, -1, "olsen", NULL), EUROVISION_NULL_ARGUMENT);
  results = makeJudgeResults(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, -1, "olsen", results), EUROVISION_INVALID_ID, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 0, "olsen", results), EUROVISION_SUCCESS, results);
  free(results);
  results = makeJudgeResults(0, 1, -2, -3, 4, 5, 6, 7, 8, -9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_INVALID_ID, results);
  free(results);
  results = makeJudgeResults(100, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_STATE_NOT_EXIST, results);
  free(results);
  results = makeJudgeResults(14, 13, 10, 8, 4, 5, 6, 15, 0, 2);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results), EUROVISION_SUCCESS, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "marie", results), EUROVISION_JUDGE_ALREADY_EXIST, results);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 2, "marie", results), EUROVISION_SUCCESS, results);
  free(results);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveJudge() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  CHECK(eurovisionRemoveJudge(eurovision, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveJudge(eurovision, 5), EUROVISION_JUDGE_NOT_EXIST);
  CHECK(eurovisionRemoveJudge(eurovision, 0), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveJudge(eurovision, 0), EUROVISION_JUDGE_NOT_EXIST);
  eurovisionDestroy(eurovision);
  return true;
}

bool testAddVote() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  CHECK(eurovisionAddVote(eurovision, -1, 12), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision, 12, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision, 100, 12), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision, 12, 100), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision, 12, 1), EUROVISION_SUCCESS);
  eurovisionDestroy(eurovision);
  return true;
}

bool testRemoveVote() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionVotes(eurovision);
  CHECK(eurovisionRemoveVote(eurovision, -1, 12), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveVote(eurovision, 12, -1), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveVote(eurovision, 100, 12), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveVote(eurovision, 12, 100), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveVote(eurovision, 1, 12), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 3, 4), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 3, 7), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 8, 3), EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveVote(eurovision, 10, 11), EUROVISION_SUCCESS);
  eurovisionDestroy(eurovision);
  return true;
}

/** combined scores:
 * 10: 0.75   * 0.4 + 6.6667 * 0.6 = 4.3 (united kingdom)
 * 4:  1.6875 * 0.4 + 6      * 0.6 = 4.275 (moldova)
 * 3:  1.75   * 0.4 + 4.6667 * 0.6 = 3.5 (russia)
 * 5:  1.1875 * 0.4 + 5      * 0.6 = 3.475 (cyprus)
 * 6:  1.4375 * 0.4 + 4      * 0.6 = 2.975 (spain)
 * 0:  0      * 0.4 + 4.6667 * 0.6 = 2.8 (israel)
 * 8:  0.625  * 0.4 + 3.6667 * 0.6 = 2.45 (france)
 * 14: 0.125  * 0.4 + 4      * 0.6 = 2.45 (netherlands)
 * 1:  0.75   * 0.4 + 3.3333 * 0.6 = 2.3 (malta)
 * 2:  1.25   * 0.4 + 3      * 0.6 = 2.3 (croatia)
 * 11: 0.0625 * 0.4 + 3.3333 * 0.6 = 2.025 (armenia)
 * 13: 0.0625 * 0.4 + 3.3333 * 0.6 = 2.025 (ireland)
 * 12: 0      * 0.4 + 2.6667 * 0.6 = 1.6 (austria)
 * 7:  0.9375 * 0.4 + 2      * 0.6 = 1.575 (italy)
 * 15: 0      * 0.4 + 1      * 0.6 = 0.6 (sweden)
 * 9:  0.375  * 0.4 + 0.6667 * 0.6 = 0.55 (germany)
 */
bool testRunContest() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  setupEurovisionVotes2(eurovision);

  List ranking = eurovisionRunContest(eurovision, 40);
  CHECK(listGetSize(ranking), 16);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}



bool testRunAudienceFavorite() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  setupEurovisionVotes2(eurovision);

  List ranking = eurovisionRunAudienceFavorite(eurovision);
  CHECK(listGetSize(ranking), 16);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}

/* friendlies: malta-croatia, russia-moldova */
bool testRunGetFriendlyStates() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  /* setupEurovisionJudges(eurovision); */
  setupEurovisionVotes2(eurovision);

  List friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK((friendlies == NULL), false);
  CHECK(listGetSize(friendlies), 2);
  char *current = (char *)listGetFirst(friendlies);
  CHECK(strcmp(current, "croatia - malta"), 0);
  current  = (char*)listGetNext(friendlies);
  CHECK(strcmp(current, "moldova - russia"), 0);

  listDestroy(friendlies);
  eurovisionDestroy(eurovision);
  return true;
}

/*
 * SPECIAL
 */

/*
 * 0 percent to citizens.
 */
bool specialTest1_OnlyJudges1() {
    Eurovision eurovision = setupEurovision();
    setupEurovisionStates(eurovision);
    setupEurovisionJudges(eurovision);
    List ranking = eurovisionRunContest(eurovision, 99); //NO VOTES!

    CHECK(listGetSize(ranking), 16);

    // By judges only
    char *current = (char*)listGetFirst(ranking);
    CHECK(strcmp(current, "united kingdom"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "moldova"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "cyprus"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "israel"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "russia"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "spain"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "netherlands"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "france"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "malta"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "armenia"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "ireland"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "croatia"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "austria"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "italy"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "sweden"), 0);
    current = (char*)listGetNext(ranking);
    CHECK(strcmp(current, "germany"), 0);

    listDestroy(ranking);
    eurovisionDestroy(eurovision);
    return true;
}

/*
 * No votes at all
 */
bool specialTest2_OnlyJudges2() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);

  List ranking = eurovisionRunContest(eurovision, 35);

  CHECK(listGetSize(ranking), 16);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "israel"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "netherlands"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "france"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "malta"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "armenia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "ireland"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "austria"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "italy"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "sweden"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "germany"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}

/*
 * No votes or judges, sort by id only
 */
bool specialTest3_NoVotesNoJudges() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  List ranking = eurovisionRunContest(eurovision, 2);

  CHECK(listGetSize(ranking), 16);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "israel"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "malta"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "italy"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "france"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "germany"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "armenia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "austria"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "ireland"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "netherlands"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "sweden"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;

}

/*
 * Check add and remove states.
 *
 */
bool specialTest4_addAndRemoveStatesLikeCrazy() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);

  for (int i=0; i<7 ; i++) {
    eurovisionRemoveState(eurovision,i);
  }

  List ranking = eurovisionRunContest(eurovision, 3);
  CHECK(listGetSize(ranking), 9);
  listDestroy(ranking);

  for (int i=0; i<70 ; i++) {
        eurovisionAddState(eurovision,i+20,"uga chaka","hakuna matata");
  }
  ranking = eurovisionRunContest(eurovision, 4);
  CHECK(listGetSize(ranking), 79);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);

  return true;

}

/*
 * invalid percent in run contest
 */
bool specialTest5_invalidPercent() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  setupEurovisionJudges(eurovision);
  setupEurovisionVotes(eurovision);

  List ranking1 = eurovisionRunContest(eurovision, -1);
  CHECK(ranking1, NULL);
  List ranking2 = eurovisionRunContest(eurovision, 101);
  CHECK(ranking2, NULL);
  List ranking3 = eurovisionRunContest(eurovision, 0);
  CHECK(ranking3, NULL);

  listDestroy(ranking1);
  listDestroy(ranking2);
  listDestroy(ranking3);
  eurovisionDestroy(eurovision);

  return true;

}

/*
 * No judges.
 */
bool specialTest6_NoJudges() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  giveVotes(eurovision,0,1,150);

  for (int i=0;i<100;i++) {
    eurovisionRemoveVote(eurovision,4,5);
  }

  giveVotes(eurovision,1,2,100);
  for (int i=0;i<100;i++) {
    eurovisionRemoveVote(eurovision,1,2);
  }
  List ranking = eurovisionRunContest(eurovision, 50);

  CHECK(listGetSize(ranking), 16);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "malta"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "israel"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "italy"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "france"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "germany"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "armenia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "austria"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "ireland"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "netherlands"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "sweden"), 0);

  listDestroy(ranking);

  eurovisionDestroy(eurovision);

  return true;

}
/*
 * checks what happen with 0/1 state.
 */
bool specialTest7_OneStateAndNoState() {
  Eurovision eurovision = setupEurovision();
  eurovisionAddState(eurovision,0,"kiryat ata","hakuna matata");

  List ranking = eurovisionRunContest(eurovision, 50);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "kiryat ata"), 0);
  listDestroy(ranking);

  eurovisionRemoveState(eurovision,0);
  ranking = eurovisionRunContest(eurovision, 50);
  CHECK(listGetSize(ranking),0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);

  return true;

}

/*
 * checks return order of votes.
 */
bool specialTest8_VoteLikeMad() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);

  CHECK(eurovisionAddVote(eurovision,0,0), EUROVISION_SAME_STATE);
  CHECK(eurovisionAddVote(eurovision,-20,20), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision,20,20), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision,20,0), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision,-20,0), EUROVISION_INVALID_ID);
  CHECK(eurovisionAddVote(eurovision,1,-20), EUROVISION_INVALID_ID);
  eurovisionRemoveState(eurovision,0);
  CHECK(eurovisionAddVote(eurovision,0,3), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionAddVote(eurovision,3,0), EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveVote(eurovision,-1,3), EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveVote(eurovision,1,1), EUROVISION_SAME_STATE);
  eurovisionRemoveState(eurovision,1);
  CHECK(eurovisionRemoveVote(eurovision,1,1), EUROVISION_STATE_NOT_EXIST);
  List ranking = eurovisionRunContest(eurovision, 12);

  CHECK(listGetSize(ranking), 14);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "italy"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "france"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "germany"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "armenia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "austria"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "ireland"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "netherlands"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "sweden"), 0);

  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;


}

/*
 * Checks stuff with judges:
 * errors with name, id and results - if id is more then once, or invalid.
 * play with add and remove judges and checks the winner list.
 */
bool specialTest9_allJudgesAreCrazy() {
  Eurovision eurovision = setupEurovision();
  setupEurovisionStates(eurovision);
  int *results;
  results = makeJudgeResults( 15,  0, 1,  2, 3, 4, 5, 6,  7, 8); //make sweden first
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 0, "olsen", results),EUROVISION_SUCCESS,results);
  free(results);

  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "olsen", NULL),EUROVISION_NULL_ARGUMENT,results);

  results = makeJudgeResults(0,9,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, -1, "tanel", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,1,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,-3,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,1,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "SHovava", results),EUROVISION_INVALID_NAME,results);
  free(results);

  results = makeJudgeResults(0,1,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "222zovava", results),EUROVISION_INVALID_NAME,results);
  free(results);

  results = makeJudgeResults(0,1,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, -1, "222zovava", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,0,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "222zovava", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,0,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "222zovava", results),EUROVISION_INVALID_ID,results); //make sure - order of EurovisionResult
  free(results);

  results = makeJudgeResults(0,-3,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results),EUROVISION_INVALID_ID,results);
  free(results);

  results = makeJudgeResults(0,5435343,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results),EUROVISION_STATE_NOT_EXIST,results);
  free(results);

  results = makeJudgeResults(0,13,1,2,3,4,5,6,7,8);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 0, "tanel", results),EUROVISION_JUDGE_ALREADY_EXIST,results);
  free(results);

  results = makeJudgeResults(13,14,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 1, "tanel", results),EUROVISION_SUCCESS,results); //make ireland first
  // and vote for the netherlands.
  free(results);

  results = makeJudgeResults(13,14,2,3,4,5,6,7,8,9);
  CHECK_WITH_FREE(eurovisionAddJudge(eurovision, 5, "tanel", results),EUROVISION_SUCCESS,results);
  // and vote for the netherlands.
  free(results);

  CHECK(eurovisionRemoveJudge(eurovision,5),EUROVISION_SUCCESS);
  CHECK(eurovisionRemoveJudge(eurovision,54),EUROVISION_JUDGE_NOT_EXIST);
  CHECK(eurovisionRemoveJudge(eurovision,-1),EUROVISION_INVALID_ID);


  eurovisionRemoveState(eurovision,14); // remove netherlands, now judge 1 removed!
  // sweden first again.

  List ranking = eurovisionRunContest(eurovision,21);

  CHECK(listGetSize(ranking), 15);

  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "sweden"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "israel"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "malta"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "croatia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "russia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "moldova"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "cyprus"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "spain"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "italy"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "france"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "germany"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "united kingdom"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "armenia"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "austria"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "ireland"), 0);


  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;

}

/*
 * Checks the "return order" of errors.
 */
bool specialTest10_statesGoingWild() {
  Eurovision eurovision = setupEurovision();

  CHECK(eurovisionAddState(eurovision,-1,"avocado","kadosh"),EUROVISION_INVALID_ID);
  CHECK(eurovisionAddState(eurovision,0,"avocado","kadosh"),EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision,1,"avocado","kadosh"),EUROVISION_SUCCESS);
  CHECK(eurovisionAddState(eurovision,1,"avocado","kadosh"),EUROVISION_STATE_ALREADY_EXIST);
  CHECK(eurovisionAddState(eurovision,1,"Avocado","kadosh"),EUROVISION_INVALID_NAME);
  CHECK(eurovisionAddState(eurovision,-1,"Avocado","kadosh"),EUROVISION_INVALID_ID);
  CHECK(eurovisionAddState(eurovision,2,"Avocado","kadosh"),EUROVISION_INVALID_NAME);
  CHECK(eurovisionAddState(eurovision,3,"hola",NULL),EUROVISION_NULL_ARGUMENT);

  CHECK(eurovisionRemoveState(eurovision,-1),EUROVISION_INVALID_ID);
  CHECK(eurovisionRemoveState(eurovision,3),EUROVISION_STATE_NOT_EXIST);
  CHECK(eurovisionRemoveState(eurovision,0),EUROVISION_SUCCESS);

  List ranking = eurovisionRunContest(eurovision,1);
  CHECK(listGetSize(ranking), 1);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "avocado"), 0);


  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;

}

/*
 * checks what happen when we remove all the votes for some state,
 *
 */
bool specialTest11_GiveAndTake() {
  Eurovision eurovision = setupEurovision();

  eurovisionAddState(eurovision,0,"stark","winter is coming");
  eurovisionAddState(eurovision,1,"targaryen","fire and blood");
  eurovisionAddState(eurovision,2,"white walkers","fuck the wall");


  giveVotes(eurovision,0,1,900); //give 900
  for (int i=0;i<1000;i++) {
    eurovisionRemoveVote(eurovision,0,1);
  } //remove 1000, now targaryen needs to be removed from Data structure of votes.

  giveVotes(eurovision,0,2,900);

  List ranking = eurovisionRunContest(eurovision,60);
  char *current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "white walkers"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "stark"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "targaryen"), 0);


  listDestroy(ranking);
  eurovisionDestroy(eurovision);
  return true;
}

/*
 * checks eurovisionRunGetFriendlyStates
 */
bool specialTest12_duasPoua() {
  Eurovision eurovision = setupEurovision();

  eurovisionAddState(eurovision,0,"stark","winter is coming");

  List friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK(listGetSize(friendlies),0);
  listDestroy(friendlies);

  eurovisionAddState(eurovision,1,"targaryen","fire and blood");
  eurovisionAddState(eurovision,2,"white walkers","fuck the wall");
  friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK(listGetSize(friendlies),0);
  listDestroy(friendlies);

  // stark - targaryen
  eurovisionAddVote(eurovision,0,1);
  eurovisionAddVote(eurovision,1,0);

  friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK(listGetSize(friendlies), 1);
  char *current = (char *)listGetFirst(friendlies);
  CHECK(strcmp(current, "stark - targaryen"), 0);
  listDestroy(friendlies);

  //stark - white walkers
  eurovisionRemoveVote(eurovision,0,1);
  eurovisionAddVote(eurovision,2,0);
  for (int i=0;i<1000;i++) {
    eurovisionAddVote(eurovision,0,2);
  }
  friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK(listGetSize(friendlies), 1);
  current = (char *)listGetFirst(friendlies);
  CHECK(strcmp(current, "stark - white walkers"), 0);
  listDestroy(friendlies);

  // no one
  eurovisionRemoveState(eurovision,2);
  friendlies = eurovisionRunGetFriendlyStates(eurovision);
  CHECK(listGetSize(friendlies),0);

  //just for fun
  List ranking = eurovisionRunContest(eurovision,1);
  CHECK(listGetSize(ranking), 2);
  current = (char*)listGetFirst(ranking);
  CHECK(strcmp(current, "stark"), 0);
  current = (char*)listGetNext(ranking);
  CHECK(strcmp(current, "targaryen"), 0);

  listDestroy(ranking);
  listDestroy(friendlies);
  eurovisionDestroy(eurovision);
  return true;
}
