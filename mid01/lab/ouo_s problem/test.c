// Author: justin0u0 <justin0u0@gapp.nthu.edu.tw>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 12679 - Ouo's problem
//#include "function.h"
struct Node {
	const int val;
	struct Node *prevPtr;
	struct Node *nextPtr;
};
typedef struct Node Node;

// Example of creating new Node
// Node *newNode = createNode(1);
Node *createNode(int val) {
	Node newNodeInst = {
		.val = val,
		.prevPtr = NULL,
		.nextPtr = NULL
	};
	Node *newNode = (Node *)malloc(sizeof(Node));
	memcpy(newNode, &newNodeInst, sizeof(newNodeInst));
	return newNode;
}
/* You need to implement the following functions, good luck! */
Node *getNextPersonOut(int peopleLeft, int m, Node *startNode);
void connectNodes(Node *personInFront, Node *personInBack);
void swapNodes(Node *personInFront, Node *personInBack);

Node *buildDoublyCircularLinkedList(int n)
{
	Node *new ;
	Node *head;
	new = createNode(1);
	head = new;
	int i;
	for(i = 2; i <= n; i ++){
		Node *next = createNode(i);
		new->nextPtr = next;
		next->prevPtr = new;
		new = next;
	}
	new->nextPtr = head;
	head->prevPtr = new;
	return head;
}
Node *getNextPersonOut(int peopleLeft, int m, Node *startNode)
{
	int step;
	if(m % peopleLeft == 0)
		step = m;
	else step = m % peopleLeft;
	Node *cur = startNode;
	step -= 1;
	while(step--){
		cur = cur->nextPtr;
	}
	printf("%d ",cur->val);
	return cur;
}

void connectNodes(Node *personInFront, Node *personInBack)
{
	personInFront->nextPtr = personInBack;
	personInBack->prevPtr = personInFront;
	return;
}
void swapNodes(Node *personInFront, Node *personInBack)
{
	int front = personInFront->val;
	int back = personInBack->val;
	Node *newfront, *newback;
	newfront = createNode(back);
	newfront->prevPtr = personInFront->prevPtr;
	newback = createNode(front);
	newback->nextPtr = personInBack;
	newfront->nextPtr = newback;
	newback->prevPtr = newfront;
	personInFront = newfront;
	personInBack = newback;

	return;
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	/* Build a circlular linked list from 1 ~ N */
	Node *node = buildDoublyCircularLinkedList(n);
	
	/* Start N-1 rounds process */
	/* Start N-1 rounds process */
	for (int i = n; i > 1; i--) {
		int peopleLeft = i;
		Node *nextPersonOut = getNextPersonOut(peopleLeft, m, node);
		Node *personInFront = nextPersonOut->prevPtr;
		Node *personInBack = nextPersonOut->nextPtr;
		free(nextPersonOut);
		connectNodes(personInFront, personInBack);
		if (peopleLeft > 3)
		  swapNodes(personInFront, personInBack);
		if (personInFront->val < personInBack->val)
			node = personInFront;
		else
			node = personInBack;
	}
	
	// Output the value of the last person
	printf("%d\n", node->val);
	return 0;
}

