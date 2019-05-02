#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "list.c"

void destroyList(Node list);

Node createNode1();
Node createNode2();
Node createNode3();
Node createNode4();
void TEST4(Node node1,Node node2);
void TEST3(Node node1,Node node2);
void TEST2(Node node1,Node node2);
void TEST1(Node node1,Node node2);

int main() {
    Node node1=createNode1(); //empty list
    Node node2=createNode2(); // 3-5-11-2
    Node node3=createNode3(); //4-8-9-12
    Node node4=createNode4(); //5-7-11-17
    TEST1(node1,node2);
    TEST2(node2,node3);
    TEST3(node3,node4);
    TEST4(node3,node4);
    destroyList(node1);
    destroyList(node2);
    destroyList(node3);
    destroyList(node4);
    return 0;
}



void destroyList(Node list){
    if(list==NULL){
        return ;
    }
    Node temp=list;
    list=list->next;
    temp->next=NULL;
    free(temp);
    destroyList(list);
}

Node createNode1(){
    return NULL;
}
Node createNode2(){
    Node temp=malloc(sizeof(*temp));
    if(temp==NULL) return NULL;
    Node temp2=malloc(sizeof(*temp));
    if(temp2==NULL){
        free(temp);
        return NULL;
    }
    Node temp3=malloc(sizeof(*temp));
    if(temp3==NULL){
        free(temp);
        free(temp2);
        return NULL;
    }
    Node temp4=malloc(sizeof(*temp));
    if(temp4==NULL){
        free(temp);
        free(temp2);
        free(temp3);
        return NULL;
    }
    temp->x=3;
    temp2->x=5;
    temp3->x=11;
    temp4->x=2;
    temp->next=temp2;
    temp2->next=temp3;
    temp3->next=temp4;
    temp4->next=NULL;
    return temp;
}
Node createNode3(){
    Node temp=malloc(sizeof(*temp));
    if(temp==NULL) return NULL;
    Node temp2=malloc(sizeof(*temp));
    if(temp2==NULL){
        free(temp);
        return NULL;
    }
    Node temp3=malloc(sizeof(*temp));
    if(temp3==NULL){
        free(temp);
        free(temp2);
        return NULL;
    }
    Node temp4=malloc(sizeof(*temp));
    if(temp4==NULL){
        free(temp);
        free(temp2);
        free(temp3);
        return NULL;
    }
    temp->x=4;
    temp2->x=8;
    temp3->x=9;
    temp4->x=12;
    temp->next=temp2;
    temp2->next=temp3;
    temp3->next=temp4;
    temp4->next=NULL;
    return temp;
}
Node createNode4(){
    Node temp=malloc(sizeof(*temp));
    if(temp==NULL) return NULL;
    Node temp2=malloc(sizeof(*temp));
    if(temp2==NULL){
        free(temp);
        return NULL;
    }
    Node temp3=malloc(sizeof(*temp));
    if(temp3==NULL){
        free(temp);
        free(temp2);
        return NULL;
    }
    Node temp4=malloc(sizeof(*temp));
    if(temp4==NULL){
        free(temp);
        free(temp2);
        free(temp3);
        return NULL;
    }
    temp->x=5;
    temp2->x=7;
    temp3->x=11;
    temp4->x=17;
    temp->next=temp2;
    temp2->next=temp3;
    temp3->next=temp4;
    temp4->next=NULL;
    return temp;
}
void TEST1(Node node1,Node node2){
    Node merge=NULL;
    ErrorCode error=mergeSortedLists(node1,node2,&merge);
    destroyList(merge);
    if(error==EMPTY_LIST)
    {
        printf("TEST1:OK\n");
        return;
    }
    printf("TEST1:FAIL\n");
}
void TEST2(Node node1,Node node2){
    Node merge=NULL;
    ErrorCode error=mergeSortedLists(node1,node2,&merge);
    destroyList(merge);
    if(error==UNSORTED_LIST)
    {
        printf("TEST2:OK\n");
        return;
    }
    printf("TEST2:FAIL\n");
}
void TEST3(Node node1,Node node2){
    Node merge=NULL;
    ErrorCode error=mergeSortedLists(node1,node2,&merge);
    Node temp=merge;
    //4-5-7-8-9-11-12-17
    assert(getListLength(merge)==8);
    assert(merge->x==4);
    assert(merge->next->x==5);
    assert(merge->next->next->x==7);
    assert(merge->next->next->next->x==8);
    assert(merge->next->next->next->next->x==9);
    assert(merge->next->next->next->next->next->x==11);
    assert(merge->next->next->next->next->next->next->x==12);
    assert(merge->next->next->next->next->next->next->next->x==17);
    if(error==SUCCESS){
        while(merge!=NULL){
            if(merge->next&&merge->next->x < merge->x){
                printf("TEST3:FAIL\n");
                destroyList(temp);
                return;
            }
            merge=merge->next;
        }
        printf("TEST3:OK\n");
        destroyList(temp);
        return;
    }
    destroyList(temp);
    printf("TEST3:FAIL\n");
}

void TEST4(Node node1,Node node2){
    ErrorCode error=mergeSortedLists(node1,node2,NULL);
    if(error==NULL_ARGUMENT)
    {
        printf("TEST4:OK\n");
        return;
    }
    printf("TEST4:FAIL\n");
}