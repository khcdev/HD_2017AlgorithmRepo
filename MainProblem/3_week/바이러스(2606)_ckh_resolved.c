#include <stdio.h>
#include <stdlib.h>

#define QMAXDATANUM 100

typedef struct node {
	int vertix;
	struct node *nextNode;
}node;

node *graphArr;
int *visit;
node *getNode();
int numInfectedComputer=0;
void initGraphArr();
void nodeInsertIntoList(node *Head, int vertix);
void DFS(int vertix);

int main() {
	initGraphArr();
	DFS(0);
	printf("%d", numInfectedComputer-1);
	return 0;
}

node *getNode() {
	node *newNode;
	newNode = (node*)malloc(sizeof(node));
	return newNode;
}

void initGraphArr() {
	int nodeNum, numPairCom;
	int a, b, i;
	node *Head = NULL, *temp = NULL;
	scanf("%d", &nodeNum);
	visit = (int*)malloc(sizeof(int)*nodeNum);
	graphArr = (node*)malloc(sizeof(node)*nodeNum);
	for (i = 0; i < nodeNum; i++) visit[i] = 0;
	for (i = 0; i < nodeNum; i++) graphArr[i].nextNode = NULL;
	scanf("%d", &numPairCom);
	for (i = 0;i<numPairCom;i++) {
		scanf("%d%d", &a, &b);
		nodeInsertIntoList(&graphArr[a-1], b-1);
		nodeInsertIntoList(&graphArr[b-1], a-1);
	}
}

void nodeInsertIntoList(node *Head, int vertix) {
	node *newNode, *temp;
	temp = Head;
	newNode = getNode();
	newNode->nextNode = NULL;
	newNode->vertix = vertix;

	if (temp->nextNode == NULL) {
		temp->nextNode = newNode;
		return;
	}
	while (temp->nextNode != NULL && temp->nextNode->vertix < newNode->vertix)
		temp = temp->nextNode;
	if (temp->nextNode != NULL) {
		newNode->nextNode = temp->nextNode;
		temp->nextNode = newNode;
	}
	else temp->nextNode = newNode;

}

void DFS(int vertix) {
	node *temp;

	visit[vertix] = 1;
	numInfectedComputer++;
	for (temp = graphArr[vertix].nextNode; temp; temp = temp->nextNode)
		if (visit[temp->vertix] == 0) DFS(temp->vertix);

}
