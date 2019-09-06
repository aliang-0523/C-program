#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX 999999 //一个极大值
#define NUM 10

//存储哈夫曼树每个结点
typedef struct Node {
    char ch;
    int weight; //权值
    int parent;
    int lchild,rchild;
}HFNode;
//存储每个字符及其哈夫曼编码
typedef struct {
    char ch;
    char code[NUM];
}HFCharCode;

HFNode HT[28*2-1]; //哈夫曼树结构体
HFCharCode HCD[28]; //哈夫曼编码结构体
int LeafNum; //叶子结点数
int NodeNum; //所有结点数
char EnterStr[MAX]; //输入的待编码电文
char EnterCode[MAX]; //输入的待解码密文
char RealStr[MAX]; //密文解码后的电文
int AllWeight[28]; //存储所有28个字符的权值

void Statistics();
void CreateHFTree();
    void SelectMin(int &min1, int &min2);
void CreateHFCode();
    void ReverseStr(char *str);
void EncodeStr();
void DecodeHFCode();

int main() {
    printf("****** 哈夫曼编码与解码 ******\n\n");
    printf("*** 输入一串字符串 ***\n");
    scanf("%s", EnterStr);
    getchar();
    Statistics();
    CreateHFTree();
    CreateHFCode();
    EncodeStr();
    printf("\n*** 输入想解码的内容 ***\n");
    scanf("%s", EnterCode);
    getchar();
    DecodeHFCode();
    return 0;
}

//统计每个字符权值
void Statistics() {
    int len = strlen(EnterStr);
    for(int i = 0; i <= 27; i++)
        AllWeight[i] = 0;
    for(int j = 0; j <= len - 1; j++) {
        if(isalpha(EnterStr[j])) {
            EnterStr[j] = tolower(EnterStr[j]);
            AllWeight[EnterStr[j]-'a']++;
        }
        else if((int)EnterStr[j] == 44)
            AllWeight[26]++;
        else if((int)EnterStr[j] == 46)
            AllWeight[27]++;
        else {
            printf("\n输入不符合要求!\n\n");
            exit(-1);
        }
    }
    int i = 0, j = 0;
    for( ; i <= 25; i++) {
        if(AllWeight[i] != 0) {
                HT[j].weight  = AllWeight[i];
                HT[j].ch = i+'a';
                j++;
        }
    }
    if(AllWeight[i] != 0) {
            HT[j].weight = AllWeight[i];
            HT[j].ch = ',';
            j++;
            i++;
    }
    if(AllWeight[i] != 0) {
            HT[j].weight = AllWeight[i];
            HT[j].ch = '.';
    }
    printf("\n*** 打印每个字符的权值 ***\n");
    int n = 0;
    for(int i = 0; i <= 27; i++) {
        if(AllWeight[i] != 0) {
            n++;
            if(i <= 25)
                putchar('a'+i);
            else if(i == 26)
                printf(",");
            else
                printf(".");
            printf(": %d\n", AllWeight[i]);
        }
    }
    LeafNum = n;
    NodeNum = 2*LeafNum-1;
}

//构造哈夫曼树
void CreateHFTree() {
    int i;
    for(i = 0; i <= LeafNum-1; i++) {
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
        HT[i].weight = HT[i].weight;
    }
    for(; i <= NodeNum-1; i++) {
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
        HT[i].weight = MAX;
    }
    int min1, min2;
    for(i = LeafNum; i <= NodeNum-1; i++) {
        SelectMin(min1, min2);
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].lchild = min1;
        HT[i].rchild = min2;
        HT[i].weight = HT[min1].weight + HT[min2].weight;
    }
    // printf("\n*** 打印哈夫曼树 ***\n");
    // for(int i = 0; i <= NodeNum-1; i++) {
    //     printf("序号:%d 字符:%c 权值:%d 双亲:%d 左孩:%d 右孩:%d\n", i, HT[i].ch, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    // }
}
    //找到两个权值最小的二叉树的序号
    void SelectMin(int &min1, int &min2) {
        int i = 0;
        int temp;
        int wetmin1, wetmin2;
        while(HT[i].parent != -1) 
            i++;
        wetmin1 = HT[i].weight;
        min1 = i;
        i++;
        while(HT[i].parent != -1) 
            i++;
        wetmin2 = HT[i].weight;
        min2 = i;
        i++;
        if(wetmin1 > wetmin2) {
            temp = wetmin2;
            wetmin2 = wetmin1;
            wetmin1 = temp;
            temp = min2;
            min2 = min1;
            min1 = temp;
        }
        for(; i <= NodeNum-1; i++) {
            if(HT[i].weight < wetmin1 && HT[i].parent == -1) {
                wetmin2 = wetmin1;
                wetmin1 = HT[i].weight;
                min2 = min1;
                min1 = i;
            } else if(HT[i].weight < wetmin2 && HT[i].parent == -1) {
                wetmin2 = HT[i].weight;
                min2 = i;
            }
        }
    }

//进行哈夫曼编码
void CreateHFCode() {
    int i, j, len; 
    for(i = 0; i <= LeafNum-1; i++) {  
        len = 0;  
        j = i;
        HCD[i].ch = HT[j].ch;
        while(HT[j].parent != -1) {  //不是根节点
            if(HT[HT[j].parent].lchild == j) {  //是双亲结点的左孩子
                HCD[i].code[len++] = '0'+0;  //加上字符0
            }else  //是右孩子
                HCD[i].code[len++] = '0'+1;  //加上字符1
            j = HT[j].parent;  //往上遍历
        }
        HCD[i].code[len] = '\0'; //字符串末尾 
        ReverseStr(HCD[i].code); 
    }
    printf("\n*** 打印每个字符的编码 ***\n");
    for(int i = 0; i <= LeafNum-1; i++)
        printf("%c: %s\n", HT[i].ch, HCD[i].code);
}
    //将一个字符串反转  
    void ReverseStr(char *str) {  
        int i, j;  
        char c;  
        for(i = 0, j = strlen(str)-1; i < j; i++, j--) {  
            c = str[i];  
            str[i] = str[j];  
            str[j] = c;  
        }
    }

//哈夫曼编码
void EncodeStr() {
    int len = strlen(EnterStr);
    printf("\n*** 编码结果 ***\n");
    for(int i = 0; i <= len-1; i++) {
        for(int j = 0; j <= LeafNum-1; j++) {
            if(EnterStr[i] == HCD[j].ch)
                printf("%s", HCD[j].code);
        }
    }
    printf("\n");
}

//哈夫曼解码
void DecodeHFCode() {
    int k = NodeNum-1; //根结点序号, 开始时一定在最后一个
    int len = 0, i = 0;  
    while(EnterCode[i]) {  
        if(EnterCode[i] == '0'+0)  
            k = HT[k].lchild;  
        else if(EnterCode[i] == '0'+1)  
            k = HT[k].rchild;  
        else {
            printf("\n错误! 密文中仅能含有1和0!\n\n");
            exit(-1);
        }  
        if(HT[k].lchild == -1 && HT[k].rchild == -1) {  
            RealStr[len++] = HT[k].ch;
            k = NodeNum-1;
        }  
        i++;  
    }
    RealStr[len] = '\0';
    if(k == NodeNum-1) {     
        printf("\n*** 解码结果 ***\n%s\n\n", RealStr);
        exit(0);
    }
    printf("\n错误! 部分密文无法解密!\n\n");
    exit(-1);  
}