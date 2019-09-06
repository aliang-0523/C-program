#include<iostream>
#include<stdlib.h>
using namespace std;
struct LNode{
    int data;
    LNode *next;
    LNode *prior;
};
//创建双链表
void createDlistR(LNode *c,int a[],int len){
    LNode *s,*r;
    c=(LNode *)malloc(sizeof(LNode));
    c->next=NULL;
    c->prior=NULL;
    for(int i=0;i<len;i++){
        s=(LNode *)malloc(sizeof(LNode));
        s->data=a[i];
        r->next=s;
        s->prior=r;
        r=s;
    }
    r->next=NULL;
}
//寻找指定结点
LNode *find(LNode *c,int x){
    LNode *p=c->next;
    while(p!=NULL){
        if(p->data==x){
            break;
        }
        p=p->next;
    }
    return p;
}
//双链表中插入结点
void insertLNode(LNode *p,int x){
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=x;
    s->next=p->next;
    s->prior=p;
    p->next=s;
    s->next->prior=s;//p为最后一个结点的话可以去除本行
}
//删除p结点下一个节点
void deleteLNode(LNode *p){
    LNode *q=(LNode *)malloc(sizeof(LNode));
    q=p->next;
    p->next=q->next;
    q->next->prior=p;
    free(q);
}