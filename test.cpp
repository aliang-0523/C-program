#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
template<class T>class Stack
{
private:
	struct Node
	{
		T data;
		Node *next;
	};
	Node *head;
	Node *p;
	int length;
 
public:
	Stack()
	{
		head = NULL;
		length = 0;
	}
	void push(T n)//入栈
	{
		Node *q = new Node;
		q->data = n;
		if (head == NULL)
		{
			q->next = head;
			head = q;
			p = q;
		}
		else
		{
			q->next = p;
			p = q;
		}
		length++;
	}
 
	T pop()//出栈并且将出栈的元素返回
	{
		if (length <= 0)
		{
			abort();
		}
		Node *q;
		T data;
		q = p;
		data = p->data;
		p = p->next;
		delete(q);
		length--;
		return data;
	}
	int size()//返回元素个数
	{
		return length;
	}
	T top()//返回栈顶元素
	{
		return p->data;
	}
	bool isEmpty()//判断栈是不是空的
	{
		if (length == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void clear()//清空栈中的所有元素
	{
		while (length > 0)
		{
			pop();
		}
	}
};

int main()
{
	Stack<char> *s=new Stack<char>;
	s->push('a');
	s->push('b');
	s->push('c');
	while (!s->isEmpty())
	{
		cout << s->pop() << endl;
	}
	system("pause");
	return 0;
}