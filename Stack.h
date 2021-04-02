#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Stack
{
	struct List
	{
		T item;
		List* next;
	}*list;

public:
	Stack() { list = nullptr; }

	Stack(const Stack<T>& S) { *this = S; }

	Stack<T>& operator= (const Stack<T>& S)
	{
		if (list != nullptr) Empty();
		List* p = S.list;
		List* p2;
		List* p3 = nullptr;
		while (p != nullptr)
		{
			p2 = new List;
			p2->item = p->item;
			p2->next = nullptr;

			if (list == nullptr)
			{
				list = p2;
				p3 = p2;
			}
			else
			{
				p3->next = p2;
				p3 = p3->next;
			}
			p = p->next;
		}
		return *this;
	}

	bool isEmpty() { return list == nullptr; }

	~Stack() { Empty(); }

	void push(const T item)
	{
		List* p = new List;
		p->item = item;
		p->next = list;
		list = p;
	}

	T pop()
	{
		if (list == nullptr) return 0;
		List* p2;
		T item = list->item;
		p2 = list;
		list = list->next;
		delete p2;

		return item;
	}

	int count()
	{
		if (list == nullptr)
			return 0;
		List* p = list;
		int count = 0;
		while (p != nullptr)
		{
			count++;
			p = p->next;
		}
		return count;
	}

	void Empty()
	{
		List* p = list;
		List* p2;
		while (p != nullptr)
		{
			p2 = p;
			p = p->next;
			delete p2;
		}
		list = nullptr;
	}

	friend ostream& operator<< (ostream& out, const Stack<T>& S)
	{
		List* p = S.list;
		if (p == nullptr)
			out << "List is empty";
		while (p != nullptr)
		{
			out << p->item << ' ';
			p = p->next;
		}
		//out << '\n';
		return out;
	}

	void print(const char* name = 0)
	{
		if (name)
			cout << "Object: " << name << '\n';
		if (list == nullptr)
			cout << "List is empty\n";
		else
		{
			List* p = list;
			while (p != nullptr)
			{
				cout << p->item << ' ';
				p = p->next;
			}
			cout << '\n';
		}
	}

	T top()
	{
		if (list == nullptr) return NULL;
		T item = list->item;
		return item;
	}
};
