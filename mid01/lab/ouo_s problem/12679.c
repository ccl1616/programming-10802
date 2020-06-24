// Author: justin0u0 <justin0u0@gapp.nthu.edu.tw>
#include <stdio.h>
#include <stdlib.h>
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

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	/* Build a circlular linked list from 1 ~ N */
	Node *node = buildDoublyCircularLinkedList(n);

	/* Start N-1 rounds process */
	for (int i = n; i > 1; i--) {
		int peopleLeft = i;
		// 1. Get the node that will get out of the circle this round
		Node *nextPersonOut = getNextPersonOut(peopleLeft, m, node);
		// 2. Get it's neighbors, remove the person out of the circle (free the node)
		Node *personInFront = nextPersonOut->prevPtr;
		Node *personInBack = nextPersonOut->nextPtr;
		free(nextPersonOut);
		// 3. Build connection between 'personInFront' and 'personInBack'
		connectNodes(personInFront, personInBack);
		// 3. Swap the neighbors' position
		if (peopleLeft > 3)
		  swapNodes(personInFront, personInBack);
		// 4. Get the smaller value node
		if (personInFront->val < personInBack->val)
			node = personInFront;
		else
			node = personInBack;
	}
	
	// Output the value of the last person
	printf("%d\n", node->val);
	return 0;
}

