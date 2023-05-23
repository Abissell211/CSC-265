#include<iostream>
using namespace std;

//Class for stack
template <class T>//using templete class
class Stack
{
private:
T * stackPtr;
int maxLen;
int topSub;
public:
//parameterize constructor that will recives the size of the stack
Stack(int size);
~Stack();
void push(T element);
void pop();
T top();
int empty();
};
template<class T>
Stack<T>::Stack(int size)
{
stackPtr = new T[size];
maxLen = size - 1;
topSub = -1;
}
template<class T>
Stack<T>::~Stack()
{ delete[]stackPtr; }

template<class T>
void Stack<T>::push(T item)
{
if (topSub == maxLen)
cerr << "Error in push--stack is full\n";
else
stackPtr[++topSub] = item;
}
template<class T>
void Stack<T>::pop()
{
if (empty())
cerr << "Error in pop--stack is empty\n";
else
topSub--;
}
template<class T>
int Stack<T>::empty()
{
return (topSub == -1);
}
template<class T>
T Stack<T>::top()
{
if (empty())
cerr << "Error in top--stack is empty\n";
else
return(stackPtr[topSub]);
}

int main()
{
Stack<int>intStack(5);
Stack<float>floatStack(5);

intStack.push(10);
intStack.push(20);
cout << "Top element in int stak:" << intStack.top() << endl;
intStack.pop();
cout << "After pop opration top element in int stak:" << intStack.top() << endl;

floatStack.push(10.20f);
floatStack.push(20.20f);
cout << "\nTop element in float stak:" << floatStack.top() << endl;
floatStack.pop();
cout << "After pop opration top element in float stak:" << floatStack.top() << endl;

system("pause");
return 0;
}
