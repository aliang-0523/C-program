#include<iostream>
#include<stdlib.h>
using namespace std;
#define getArraylength(array,len){len=sizeof(array)/sizeof(array[0]);}
typedef struct LNode{
    int data;
    LNode *next;
};
//合并两个单链表
void merge(LNode *A,LNode *B,LNode *&c){
    LNode *p=A->next;
    LNode *q=B;
    LNode *r;
    c=A;
    c->next=NULL;
    free(B);
    r=c;
    while(p!=NULL&&q!=NULL){
        if(p->data<q->data){
            r->next=p;
            p=p->next;
            r=r->next;
        }
        else{
            r->next=q;
            q=q->next;
            r=r->next;
        }
    }
    if(p!=NULL)r->next=p;
    if(q!=NULL)r->next=q;
    A=NULL;
}
//尾插法创建链表
void createListBehind(LNode *&c,int a[],int len){
    LNode *s,*r;
    c=(LNode *)malloc(sizeof(LNode));
    c->data=a[0];
    c->next=NULL;
    r=c;
    for(int i=1;i<len;i++){
        s=(LNode *)malloc(sizeof(LNode));
        s->data=a[i];
        r->next=s;
        r=r->next;
    }
    r->next=NULL;
}
//头插法创建链表
void createListFront(LNode *&c,int a[],int len){
    LNode *s;
    c=(LNode *)malloc(sizeof(LNode));
    c->data=a[len-1];
    c->next=NULL;
    for(int i=0;i<len-1;i++){
        s=(LNode *)malloc(sizeof(LNode));
        s->data=a[i];
        s->next=c->next;
        c->next=s;
    }
}
//寻找指定元素并删除
int findAndDelete(LNode *c,int x){
    LNode *p,*q;
    p=c;
    while(p->next!=NULL){
        if(p->next->data=x){
            break;
        }
        p=p->next;
    }
    if(p->next==NULL){
        return 0;
    }
    else{
        q=p->next;
        p->next=p->next->next;
        free(q);
        return 1;
    }
}
//删除链表重复项
void deleteSame(LNode *s){
    int temp=s->data;
    LNode *next=s->next;
    LNode *before=s;
    while(next!=NULL){
        if(before->data==next->data){
            before->next=next->next;
            next=next->next;
        }
        else{
            before=next;
            next=next->next;
        }
    }
}
int main(){
    int a[]={1,1,2,3,3,4,4,5};
    LNode *c;
    int c1;
    getArraylength(a,c1);
    createListFront(c,a,c1);
    deleteSame(c);
    cout<<"finished";
    system("pause");
    return 0;
}