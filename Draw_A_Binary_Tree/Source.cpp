#include "iostream"
#include "windows.h"
#include "fstream"
using namespace std;

struct node {
	int data;
	node* left, * right;
};
typedef node* nodeptr;
typedef node* BST;


void init(BST& root) {
	root = NULL;
}

bool isEmpty(BST root) {
	return root == NULL;
}

nodeptr makeNode(int x) {
	nodeptr p = new node;
	if (p == NULL) return NULL;
	p->data = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void insert(BST& root, int x) {
	if (root == NULL)
		root = makeNode(x);
	else if (x == root->data)
		cout << "\nAlready here";
	else if (x < root->data)
		insert(root->left, x);
	else
		insert(root->right, x);
}

void readText(BST& root) {
	ifstream infile("Text.txt");
	if (!infile.is_open()) {
		cout << "\nCannot open file";
		return;
	}
	int n;
	infile >> n;
	for (int i = 0; i < n; i++) {
		int x;
		infile >> x;
		insert(root, x);
	}

	infile.close();
}

void gotoxy(short x, short y) {
	HANDLE consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(consol, pos);
}

void textColor(int x) {
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}

void NLR2(BST root, int x, int y, int d) {
	if (root) {
		gotoxy(x, y);
		cout << "(" << root->data << ")";
		if (root->left) {
			gotoxy(x + 1, y + 1);
			cout << "|";
			for (int i = x - d / 2 + 2; i <= x + 2; i++) {
				gotoxy(i, y + 2);
				cout << "-";
			}
			NLR2(root->left, x - d / 2, y + 3, d / 2);
		}
		if (root->right) {
			gotoxy(x + 1, y + 1);
			cout << "|";
			for (int i = x + 2; i <= x + d / 2 + 2; i++) {
				gotoxy(i, y + 2);
				cout << "-";
			}
			NLR2(root->right, x + d / 2, y + 3, d / 2);
		}
	}
}

int main() {
	BST Tree;
	init(Tree);
	readText(Tree);
	insert(Tree, 999);
	textColor(3);
	NLR2(Tree, 60, 1, 30);
	textColor(7);
}