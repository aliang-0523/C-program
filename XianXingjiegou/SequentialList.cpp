#include<iostream>
#include<stdlib.h>
using namespace std;
#define maxsize 10
//顺序表
typedef struct{
    int data[maxsize];
    int length;
}sqlist;
//寻找指定元素
int fildElement(sqlist s,int j){
    int i;
    for(i=0;i<s.length;i++){
        if(s.data[i]>j){
            return j-1;
        }
    }
    return i;
}
//在指定元素后插入某元素(顺序表按序排列)
void insert(sqlist& K,int k){
    int p,j;
    p=fildElement(K,k);
    for(j=K.length;j>p;j--){
        K.data[j]=K.data[j-1];
    }
    K.data[p]=k;
    K.length++;
}
//删除指定元素
int deleteElement(sqlist& K,int k){
    int i;
    if(k<0||k>K.length-1){
        return 0;
    }
    for(i=k;i<K.length;++i){
        K.data[i]=K.data[i+1];
    }
    --K.length;
    return 1;
}
//反转数组
void reverseArray(int a[],int len){
    for(int i=0;i<len;i++,len--){
        int temp=a[i];
        a[i]=a[len-1];
        a[len-1]=temp;
    }
}
//删除第i-j元素
void deletIJ(sqlist &l,int i,int j){
    for(int k=i;k<l.length;k++){
        l.data[k]=l.data[k+j-i+1];
    }
    l.length=l.length-j+i-1;
}
//将顺序表重新排列，使第一个元素的左边元素都小于该元素，右边元素都大于该元素
void put_int(sqlist &l){
    int temp=l.data[0];
    int i=0,j=l.length;
    while(i<j){
        while(i<j&&l.data[j]>temp)j--;
        if(i<j){
            l.data[i]=l.data[j];
            i++;
        }
        while(i<j&&l.data[i]<temp)i++;
        if(i<j){
            l.data[i]=l.data[j];
            j--;
        }
    }
    l.data[i]=temp;
}
int main(){
    sqlist s={{3,2,4,5,6,1},6};
    insert(s,3);

    for(int i=0;i<5;i++){
        cout<<s.data[i];
    }
    cout<<endl<<s.length<<endl;
    deleteElement(s,2);
    deletIJ(s,2,3);
    for(int i=0;i<5;i++){
        cout<<s.data[i];
    }
    cout<<s.length<<endl;
    system("pause");
}