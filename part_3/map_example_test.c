#include "test_utilities.h"
#include <stdlib.h>
#include "map.h"

/** Function to be used for copying an int as a key to the map */
static MapKeyElement copyKeyInt(MapKeyElement n) {
    if (!n) {
        return NULL;
    }
    int *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

/** Function to be used for copying a char as a data to the map */
static MapDataElement copyDataChar(MapDataElement n) {
    if (!n) {
        return NULL;
    }
    char *copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(char *) n;
    return (MapDataElement) copy;
}

/** Function to be used by the map for freeing elements */
static void freeInt(MapKeyElement n) {
    free(n);
}

/** Function to be used by the map for freeing elements */
static void freeChar(MapDataElement n) {
    free(n);
}

/** Function to be used by the map for comparing elements */
static int compareInts(MapKeyElement n1, MapKeyElement n2) {
    return (*(int *) n1 - *(int *) n2);
}

bool testMapCreateDestroy() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    ASSERT_TEST(map != NULL);
    ASSERT_TEST(mapGetSize(map) == 0);
    ASSERT_TEST(mapGetFirst(map) == NULL);
    mapDestroy(map);
    return true;

}

bool testMapAddAndSize() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }

    mapDestroy(map);
    return true;
}

bool testMapGet() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }

    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        char *getVal = (char *) mapGet(map, &i);
        ASSERT_TEST(*getVal == j);
    }
    int i = 0;
    ASSERT_TEST(mapGet(map, &i) == NULL);
    i = 1000;
    ASSERT_TEST(mapGet(map, &i) == NULL);
    mapDestroy(map);
    return true;
}

bool testIterator() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 400; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }

    for (int i = 800; i >= 400; --i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }

    for (int i = 801; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }

    int i = 1;
    MAP_FOREACH(int *, iter, map) {
        ASSERT_TEST(*iter == i);
        i++;
    }
    mapDestroy(map);
    return true;
}

int main() {
    RUN_TEST(testMapCreateDestroy);
    RUN_TEST(testMapAddAndSize);
    RUN_TEST(testMapGet);
    RUN_TEST(testIterator);
    printf ("Tomer's test of mapCopy, based on testMapAddAndSize\nIf it "
            "works ther will be no massage.\n");
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }
    Map map_copy = mapCopy(map);
    ASSERT_TEST(mapGetSize(map_copy) == 999);
    for (int i = 1; i < 1000; ++i) {
        ASSERT_TEST( *(char*)mapGet(map,&i) ==
        *(char*)mapGet(map_copy,&i) );
    }
    mapDestroy(map);
    mapDestroy(map_copy);
    return 0;
}

// GREY: NADAV'S TEST

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include "map.h"
//
//MapDataElement copyDataFunction(MapDataElement data);
//MapKeyElement copyKeyFunction(MapKeyElement key);
//void freeDataFunction(MapDataElement data);
//void freeKeyFunction(MapKeyElement key);
//int compareKeyFunction(MapKeyElement key1, MapKeyElement key2);
//
//int main() {
//    printf("Hello, World!\n");
//    copyMapDataElements copy_data = copyDataFunction;
//    copyMapKeyElements   copy_key = copyKeyFunction;
//    freeMapDataElements free_data = freeDataFunction;
//    freeMapKeyElements free_key= freeKeyFunction;
//    compareMapKeyElements compare = compareKeyFunction;
//    Map map = mapCreate(copy_data, copy_key, free_data, free_key, compare);
//    int a=1,b=2,c=3,d=4; //keys
//    int aa=11,bb=22,cc=33,dd=44; //data
//    mapPut(map,&a,&aa);
//    mapPut(map, &b,&bb);
//    mapPut(map,&c,&cc);
//    mapPut(map, &d, &dd);
//    //mapPut(map, &c, &aa);
//    //mapRemove(map,&b);
//    MapKeyElement key;
//    key = mapGetFirst(map);
//    while(key){
//        int data = *(int*)mapGet(map, key);
//        printf("for key: %d, the data is: %d\n",*(int*)key, data);
//        // it gets the KEY of tje next node, not the next node itself!
//        key = mapGetNext(map);
//        if (!key) printf("now key is NULL\n");
//        else printf("now key is: %d\n",*(int*)key);
//    }
//    printf("size of map is:%d\n",mapGetSize(map));
//    mapDestroy(map);
//
//    return 0;
//}
//MapDataElement copyDataFunction(MapDataElement data){
//    MapDataElement new_data = (MapDataElement)malloc(sizeof(int));
//    *(int*)new_data = *(int*)data;
//    return new_data;
//}
//MapKeyElement copyKeyFunction(MapKeyElement key){
//    MapKeyElement new_key = (MapKeyElement)malloc(sizeof(int));
//    *(int*)new_key = *(int*)key;
//    return new_key;
//}
//void freeDataFunction(MapDataElement data){
//    free(data);
//}
//void freeKeyFunction(MapKeyElement key){
//    free(key);
//}
//int compareKeyFunction(MapKeyElement key1, MapKeyElement key2){
//    return  (*(int*)key1 - *(int*)key2);
//}