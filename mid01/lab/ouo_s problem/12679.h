// Author: justin0u0 <justin0u0@gapp.nthu.edu.tw>

#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
	const int val;
	struct Node *prevPtr;
	struct Node *nextPtr;
};
typedef struct Node Node;

/* The below function is already implement above the main function */
Node *createNode(int val);
/* You need to implement the following functions, good luck! */
Node *buildDoublyCircularLinkedList(int n);
Node *getNextPersonOut(int peopleLeft, int m, Node *startNode);
void connectNodes(Node *personInFront, Node *personInBack);
void swapNodes(Node *personInFront, Node *personInBack);

#endif

