/*
中缀转后缀C++代码实现(比较方便)
1.遇到操作数：添加到后缀表达式中或直接输出
2.栈空时：遇到运算符，直接入栈
3.遇到左括号：将其入栈
4.遇到右括号：执行出栈操作，输出到后缀表达式，直到弹出的是左括号
注意：左括号不输出到后缀表达式
5.遇到其他运算符：弹出所有优先级大于或等于该运算符的栈顶元素，然后将该运算符入栈
6.将栈中剩余内容依次弹出后缀表达式
*/
 
#include<iostream>
#include<stack>
#include<queue>
#include<map>
#include<string>
#include<cstdio>
#define MAX 100
using namespace std;
 
//设置优先级(注意默认操作数的优先级最高，即其不需要进栈，进栈的都是运算符)
map<char, int> p;
 
//一些初始化********************************************
struct Node{
	double num;//操作数
	char op;//操作符
	bool flag;//true表示操作数，false表示操作符
};
typedef struct Node node;
 
stack<node> s;//操作符栈
stack<node> s1;//存放操作数的，为了计算后缀表达式的值
queue<node> q;//后缀表达式队列
 
//******************************************************
//中缀转后缀函数
void change(string str){
	node temp;
	for (int i = 0; i < str.length();){
		if (str[i] == '('){//3.遇到左括号：将其入栈
			temp.flag = false;
			temp.op = str[i];
			s.push(temp);
			i++;
		}
		else if (str[i] == ')'){//4.遇到右括号：执行出栈操作，输出到后缀表达式，直到弹出的是左括号
			while (!s.empty() && s.top().op != '('){
				q.push(s.top());
				s.pop();
			}
			s.pop();//弹出左括号
			i++;
		}
		else if (str[i] >= '0'&&str[i] <= '9'){
			//如果是数字
			temp.flag = true;
			temp.num = str[i] - '0';
			i++;//后移一位,因为数字不一定是个位数
			while (i < str.length() && str[i] >= '0'&&str[i] <= '9'){
				temp.num = temp.num * 10 + (str[i] - '0');
				i++;
			}
			q.push(temp);//操作数进入后缀表达式
		}
		else{
			//如果是操作符
			//5.遇到其他运算符：弹出所有优先加大于或等于该运算符的栈顶元素，然后将该运算符入栈
			temp.flag = false;
			while (!s.empty() && p[s.top().op] >= p[str[i]]){
				q.push(s.top());
				s.pop();
			}
			temp.op = str[i];
			s.push(temp);
			i++;
		}
	}
	//6.将栈中剩余内容依次弹出后缀表达式
	while (!s.empty()){
		q.push(s.top());
		s.pop();
	}
}
 
//*************************************************************
//后缀表达式的计算
/*
从左到右扫描后缀表达式
1）若是操作数，就压栈，
2）若是操作符，就连续弹出两个操组数
3）栈顶的值即为所需结果
注：先弹出的是第一操作数，后弹出的是第二操作数
*/
double  calculate(){
	double num_a, num_b;//操作数a,b
	node cur, temp;
	while (!q.empty()){//后缀队列非空
		cur = q.front();//记录队首元素
		q.pop();
		if (cur.flag == true){//是操作数进入栈
			s1.push(cur);
		}
		else{//是操作符就运算
			num_b = s1.top().num;
			s1.pop();//弹出第二操作数
			num_a = s1.top().num;
			s1.pop();//弹出第一操作数
			temp.flag = true;
			if (cur.op == '+'){
				temp.num = num_a + num_b;
			}
			else if (cur.op == '-'){
				temp.num = num_a - num_b;
 
			}
			else if (cur.op == '*'){
				temp.num = num_a * num_b;
			}
			else{
				temp.num = num_a / num_b;
			}
			s1.push(temp);//把计算后的结果再次压栈
		}
	}
	return s1.top().num;
 
}
//*************************************************************
 
 
int main()
{
	string str;
	p['+'] = p['-'] = 1;//通过hashmap赋值
	p['*'] = p['/'] = 2;
	cin >> str;
	change(str);
	//*****************************************************
	//中缀转后缀
	/*while (!q.empty()){
		cur = q.front();
		if (cur.flag == true) cout << cur.num << " ";
		else cout << cur.op << " ";
		q.pop();
	}*/
	while (!s1.empty()){//初始化栈s1
		s1.pop();
	}
	double answer=calculate();
	cout << answer<<endl;
	return 0;
}