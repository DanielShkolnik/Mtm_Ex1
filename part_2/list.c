#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;
typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;
int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut);
Node createNode(int num);
int main() {
    Node list1 = createNode(3);
    Node list1Head = list1;
    list1->next = createNode(7);
    list1 = list1->next;
    list1->next = createNode(9);
    list1 = list1->next;
    list1->next = createNode(11);
    list1 = list1->next;
    list1->next = NULL;
    Node list2 = createNode(1);
    Node list2Head = list2;
    list2->next = createNode(3);
    list2 = list2->next;
    list2->next = createNode(4);
    list2 = list2->next;
    list2->next = createNode(6);
    list2 = list2->next;
    list2->next = NULL;
    Node merged = NULL;
    ErrorCode result = mergeSortedLists(list1Head, list2Head, &merged);
    while (merged != NULL){
        printf("%d\n",merged->x);
        merged = merged->next;
    }
    return 0;
}

Node createNode(int num){
    Node ptr = malloc(sizeof(*ptr));
    if(!ptr){
        return NULL;
    }
    ptr -> x = num;
    ptr ->next = NULL;
    return  ptr;
}

void NodeAppend(Node node1, Node node2){
    node1->next = node2;
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut){
    if (list1==NULL || list2 ==NULL || mergedOut ==NULL) {
        return NULL_ARGUMENT;
    }
    if(getListLength(list1) == 0 && getListLength(list2) == 0){
        return EMPTY_LIST;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        return UNSORTED_LIST;
    }
    Node mergedCurrent = NULL;

    if(list1->x < list2->x){
        mergedCurrent = createNode(list1->x);
        list1 = list1->next;
    }
    else{
        mergedCurrent = createNode(list2->x);
        list2 = list2->next;
    }
    *mergedOut = mergedCurrent;
    if(mergedCurrent == NULL){
        return MEMORY_ERROR;
    }
    while (list1 != NULL && list2 != NULL){
        if(list1->x < list2->x){
            NodeAppend(mergedCurrent,createNode(list1->x));
            list1 = list1->next;
        }
        else{
            NodeAppend(mergedCurrent,createNode(list2->x));
            list2 = list2->next;
        }
        mergedCurrent = mergedCurrent->next;
        if(mergedCurrent == NULL){
            return MEMORY_ERROR;
        }
    }
    while(list2 != NULL) {
        NodeAppend(mergedCurrent, createNode(list2->x));
        if(mergedCurrent->next == NULL){
            return MEMORY_ERROR;
        }
        mergedCurrent = mergedCurrent->next;
        list2 = list2->next;
    }
    while(list1 != NULL) {
        NodeAppend(mergedCurrent, createNode(list1->x));
        if(mergedCurrent->next == NULL){
            return MEMORY_ERROR;
        }
        mergedCurrent = mergedCurrent->next;
        list1 = list1->next;
    }
    return SUCCESS;
}

int getListLength(Node list){
    int counter = 0;
    while (list != NULL){
        list = list->next;
        counter++;
    }
    return counter;
}
bool isListSorted(Node list){
    int mergedCurrent = list->x;
    while (list->next != NULL){
        list = list->next;
        if (mergedCurrent > list->x){
            return false;
        }
        mergedCurrent = list->x;
    }
    return true;
}

