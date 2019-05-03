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
ErrorCode merge(Node *list1, Node *list2, Node *mergedCurrent);
ErrorCode appendList(Node *mergedCurrent,Node *list);
/*int main() {
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
    Node merged = createNode(0);
    ErrorCode result = mergeSortedLists(list1Head, list2Head, &merged);
    while (merged != NULL){
        printf("%d\n",merged->x);
        merged = merged->next;
    }
    return 0;
}
*/
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
    if (mergedOut ==NULL) {
        return NULL_ARGUMENT;
    }
    if(list1==NULL || list2 ==NULL){
        return EMPTY_LIST;
    }
    if(!isListSorted(list1) || !isListSorted(list2)){
        return UNSORTED_LIST;
    }
    //Initialize list head
    Node mergedCurrent = NULL;
    if(list1->x < list2->x){
        mergedCurrent = createNode(list1->x);
        list1 = list1->next;
    }
    else{
        mergedCurrent = createNode(list2->x);
        list2 = list2->next;
    }
    if(mergedCurrent == NULL){
        return MEMORY_ERROR;
    }
    //mergedOut points to the list head
    *mergedOut = mergedCurrent;
    ErrorCode mergeResult = merge(&list1,&list2,&mergedCurrent);
    if(mergeResult == MEMORY_ERROR){
        return MEMORY_ERROR;
    }
    ErrorCode resultAppend=SUCCESS;
    if(list1!=NULL && list2==NULL){
        resultAppend = appendList(&mergedCurrent,&list1);
    }
    if(list2!=NULL &&list1==NULL){
        resultAppend = appendList(&mergedCurrent,&list2);
    }
    if(resultAppend==MEMORY_ERROR){
        return MEMORY_ERROR;
    }
    return SUCCESS;
}
/**
 * Merging the two lists into mergedCurrent until the end of one of the lists.
 * @param list1 sorted list
 * @param list2 sorted list
 * @param mergedCurrent the pointer to the current node in the mergedOut list
 * @return MEMORY_ERROR if a memory error occurred else returns SUCCESS
 */
ErrorCode merge(Node *list1, Node *list2, Node *mergedCurrent){
    while (*list1 != NULL && *list2 != NULL){
        if((*list1)->x < (*list2)->x){
            NodeAppend(*mergedCurrent,createNode((*list1)->x));
            *list1 = (*list1)->next;
        }
        else{
            NodeAppend(*mergedCurrent,createNode((*list2)->x));
            *list2 = (*list2)->next;
        }
        if((*mergedCurrent)->next == NULL){
            return MEMORY_ERROR;
        }
        *mergedCurrent = (*mergedCurrent)->next;
    }
    return SUCCESS;
}
/**
 * appends the remaining list to the merged list.
 * @param mergedCurrent the pointer to the current node in the mergedOut list
 * @param list the list to append to the end of the merged list
 * @return MEMORY_ERROR if a memory error occurred else returns SUCCESS
 */
ErrorCode appendList(Node *mergedCurrent,Node *list){
    while((*list)!=NULL) {
        NodeAppend(*mergedCurrent, createNode((*list)->x));
        if((*mergedCurrent)->next == NULL){
            return MEMORY_ERROR;
        }
        *mergedCurrent = (*mergedCurrent)->next;
        *list = (*list)->next;
    }
    return SUCCESS;
}
int getListLength(Node list){
    Node temp=list;
    int counter=0;
    while(temp){
        counter++;
        temp=temp->next;
    }
    return counter;
}

bool isListSorted(Node list){
    Node temp=list;
    while(temp){
        if(temp->next&&temp->next->x < temp->x)
            return false;
        temp=temp->next;
    }
    return true;
}