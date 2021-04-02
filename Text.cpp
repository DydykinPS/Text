#include <string>
#include <iostream>
#include "Stack.h"
#include <conio.h>
#include <Windows.h>

using namespace std;

struct Node
{
	string val;

	Node* down;
	Node* next;

	Node(string v, Node* _next=NULL, Node* _down = NULL) :
		val(v), down(_down), next(_next) {}
};

void printTDN(ostream &o, Node* root, Node* curr, int level)
{
	if (root == NULL) return;

	if (root == curr)
		o << "*";
	else o << "|";
	for (int i = 0; i < level; ++i)
	{
		o << " ";
	}
	o << root->val << "\n";

	printTDN(o, root->down, curr, level + 1);
	printTDN(o, root->next, curr, level);
}

class Text 
{
	Node* curr;
	Node* root;
	Stack<Node*> path;
public:
	Text() {
		root = NULL;
		Node* l1 = new Node("l1");
		Node* l2 = new Node("l2");
		root = new Node("root", l1, l2);

		curr = root;
	}

	void addNext(string s) 
	{
		if (root == NULL) 
		{
			root = curr = new Node(s);
			return;
		}
		Node* p = new Node(s, curr->next);
		curr->next = p;
	}

	void addDown(string s)
	{
		if (root == NULL)
		{
			root = curr = new Node(s);
			return;
		}
		Node* p = new Node(s, curr->down);
		curr->down = p;
	}

	void down() {
		if (curr == NULL) throw "No elements";
		if (curr->down == NULL) throw "curr->next == NULL";
		path.push(curr);
		curr = curr->down;
	}

	void next() {
		if (curr == NULL) throw "No elements";
		if (curr->next == NULL) throw "curr->next == NULL";
		path.push(curr);
		curr = curr->next;
	}

	void top() {
		if (curr == NULL) throw "No elements";
		if (path.isEmpty()) throw "no way";
		curr = path.pop();
	}
	friend ostream& operator <<(ostream& o, Text& t) {
		printTDN(o, t.root, t.curr, 0);
		return o;
	}
	void FreeTree(Node*& root) 
	{
		if (root->next)  FreeTree(root->next);
		if (root->down)  FreeTree(root->down);

		delete root;
		root = nullptr;
	}


	void deleteCurr()
	{
		if (curr == nullptr)
			return;
		if (curr == root) {
			root = root->next;
			curr->next = nullptr;
			FreeTree(curr);
			curr = root;
		}
		else {
			Node* tmp = path.top();
			if (tmp->next == curr) {
				tmp->next = curr->next;
				curr->next = nullptr;
				FreeTree(curr);
				curr = tmp;
				path.pop();
			}
			else {
				tmp->down = curr->next;
				curr->next = nullptr;
				FreeTree(curr);
				curr = tmp;
				path.pop();
			}
		}
	}
};
int main() {
	Text t;
	string tstr;
	int op;
	while (true)
	{
		system("cls");
		cout << t;
		cout << "0. Exit \n";
		cout << "1. Down \n";
		cout << "2. Next \n";
		cout << "3. Top \n";
		cout << "4. AddNext \n";
		cout << "5. AddDown \n";
		cout << "6. Delete \n";
		cin >> op;
		try {
			switch (op)
			{
			case 0:
				return 0;
				break;
			case 1:
				t.down();
				break;
			case 2:
				t.next();
				break;
			case 3:
				t.top();
				break;
			case 4:
				cin >> tstr;
				t.addNext(tstr);
				break;
			case 5:
				cin >> tstr;
				t.addDown(tstr);
				break;
			case 6:
				t.deleteCurr();
				break;
			}
		}
		catch (const char* s)
		{
			cout << s << "\n";
			_getch();
		}
	}
	return 0;
}