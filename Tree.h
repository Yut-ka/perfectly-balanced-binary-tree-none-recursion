#pragma once
#include <string>
#include <iostream>
#include <time.h>

struct Tree_Item {
public:
	int inf;
	Tree_Item* left;
	Tree_Item* right;
};

struct Stack_Item {
	int t;
	Tree_Item* pTree;
	Stack_Item* next;
};

struct Stack {
	Stack_Item* sp;
	Stack() {
		sp = NULL;
	}
};

void Push(Stack* stack, Tree_Item* tree, int t) {
	Stack_Item* pTemp = new Stack_Item();
	pTemp->t = t;
	pTemp->pTree = tree;
	pTemp->next = stack->sp;
	stack->sp = pTemp;
}

int Get_tab(Stack* stack) {
	return stack->sp->t;
}

Tree_Item* Get_tree(Stack* stack) {
	if (stack->sp == NULL) return 0;
	Stack_Item* pTemp = stack->sp;
	stack->sp = stack->sp->next;
	return pTemp->pTree;
}




void AddNodes(Tree_Item*& pCurrent, int N) {
	if (N <= 0) { pCurrent = NULL;}
	else {
		Tree_Item* pTemp;
		int N_left, N_right;
		N_left = N / 2;
		N_right = N - N_left - 1;
		pTemp = new Tree_Item();
		pTemp->inf = rand() % 100;
		AddNodes(pTemp->left, N_left);
		AddNodes(pTemp->right, N_right);
		pCurrent = pTemp;
	}
}

void Preorder_traversal(std::string& str, Tree_Item* pCurrent, int t = 0) {
	if (pCurrent != NULL) {
		std::string line = "";
		for (int i = 0; i < t; i++) line += "\t";
		line = line + std::to_string(pCurrent->inf);
		str = str + line + "\n";
		Preorder_traversal(str, pCurrent->left, t + 1);
		Preorder_traversal(str, pCurrent->right, t + 1);
	}
}

void Inorder_traversal(std::string& str, Tree_Item* pRoot) {
	Tree_Item* pCurrent = pRoot;
	Stack* a = new Stack();
	bool stop = false;
	int t = 0;
	while (!stop) {
		while (pCurrent != NULL) {
			Push(a, pCurrent, t);
			pCurrent = pCurrent->left;
			t++;
			if(pCurrent == NULL) t=Get_tab(a);
		}
		if (a->sp == NULL) stop = true;
		else {
			t = Get_tab(a);
			pCurrent = Get_tree(a);
			std::string line = "";
			for (int i = 0; i < t; i++) line += "\t";
			line = line + std::to_string(pCurrent->inf);
			str = str + line + "\n";
			pCurrent = pCurrent->right;
			if (pCurrent == NULL) t--;
			else t++;
		}
	}
}

void Reverse_Inorder_traversal(std::string& str, Tree_Item* pCurrent, int t = 0) {
	if (pCurrent != NULL) {
		Reverse_Inorder_traversal(str, pCurrent->right, t + 1);
		std::string line = "";
		for (int i = 0; i < t; i++) line += "\t";
		line = line + std::to_string(pCurrent->inf);
		str = str + line + "\n";
		Reverse_Inorder_traversal(str, pCurrent->left, t + 1);
	}
}