#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;
#define foo(arr) sizeof(arr)/sizeof(arr[0])
#define getArraylength(array,len){len=sizeof(array)/sizeof(array[0]);}
template <typename T, size_t N>
inline size_t Count(T (&arr)[N]) {
    return N;
}
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
class solution{
    public:
    TreeNode *postordered(vector<int> &inorder, vector<int> &postorder, int begin, int end, int &pos){
        if(pos<0 || begin>=end) return NULL;
        TreeNode *r= new TreeNode(postorder[--pos]);
        int cur=0;
        for(cur=begin; cur<end && inorder[cur]!=r->val; ++cur);
        r->right=postordered(inorder,postorder,cur+1,end,pos);
        r->left=postordered(inorder,postorder,begin,cur,pos);
        return r;
    }
    TreeNode* buildtree(vector<int>&inorder,vector<int>& postorder);
};
TreeNode*solution::buildtree(vector<int>& inorder,vector<int>& postorder){
    int pos=postorder.size();
    return postordered(inorder,postorder,0,inorder.size(),pos);
}
typedef struct node{
    int data;
    struct node *next;
}Node;
int main(int argc,char ** argv){
    int *a2=new int[4]{1,2,3,4};
    cout<<a2[1]<<" "<<*a2;
    int a1[]={1,2,3,4,5,6};
    int j;
    getArraylength(a1,j);
    solution s;
    vector<int> inorder;
    int a[5]={9,3,15,20,7};
    vector<int> postorder;
    int b[5]={9,15,7,20,3};
    cout<<"this is a test";
    s.buildtree(inorder,postorder);
    for(int i=0;i<Count(b);i++){
        postorder.push_back(b[i]);
    }
    system("pause");
}