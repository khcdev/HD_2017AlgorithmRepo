#include <stdio.h>
#include <stdlib.h>
/* ���� ���� �˰��� */
#define INFINITE 100000
typedef struct node {
	int vertices;
	int weight;
	struct node *nextNode;
}node;

node *graphArr;
node *getNode();

void nodeInsertIntoList(node *Head, int vertix,int weight);

int main() {

	//����, ���� ����
	int nVertices, nEdges;
	// index������ �Ÿ��� ��Ÿ���� �迭
	int *aryDistance;

	int startPoint=1;
	int targetIndex;
	int minusCycle = 0;

	/*----------Default Initialization----------*/
	scanf("%d%d", &nVertices, &nEdges);


	graphArr = (node*)malloc(sizeof(node)*(nVertices+1));
	for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;
	aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));
	
	//���� �迭 �ʱ�ȭ ����ġ �ʱ�ȭ
	for (int i = 0; i < nEdges; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		//����׷����̱� ������ �ѹ��� ȣ�� �ϸ� ��.
		nodeInsertIntoList(&graphArr[t1], t2, t3);
	}

	for (int i = 0; i <= nVertices; i++) {
		aryDistance[i] = INFINITE;
	}
	/*------------------------------------------*/


	/*--------------Start Bellman-Ford--------------*/
	// (v-1)���� dist �迭�� �ϼ� �Ǿ�� �ϰ� v loop���� ���� ������ �Ͼ�ٸ� ���� ����Ŭ�� �����Ѵٴ� �ǹ��̴�.
	aryDistance[startPoint] = 0;
	for (int i = 0; i < nVertices; i++) {
		for (int j = 1; j <= nVertices; j++) {
			node *temp = graphArr[j].nextNode;
			while (temp != NULL) {
				if (aryDistance[j] != INFINITE && aryDistance[temp->vertices] > aryDistance[j] + temp->weight) {
					aryDistance[temp->vertices] = aryDistance[j] + temp->weight;
					if (i == nVertices - 1) minusCycle = 1;
				}
				temp = temp->nextNode;
			}
			
		}
	}
	/*------------------Result------------------*/
	if (minusCycle) printf("-1");
	else {
		for (int i = 2; i <= nVertices; i++) {
			if (aryDistance[i] == INFINITE)printf("-1\n");
			else printf("%d\n", aryDistance[i]);
		}
	}
	/*------------------------------------------*/
	return 0;
}

node *getNode() {
	node *temp = (node*)malloc(sizeof(node));
	return temp;
}
void nodeInsertIntoList(node *Head, int vertices, int weight) {
	node *newNode, *temp;
	temp = Head;
	newNode = getNode();
	newNode->nextNode = NULL;
	newNode->vertices = vertices;
	newNode->weight = weight;

	while (temp->nextNode != NULL && 
		temp->nextNode->vertices < newNode->vertices)
		temp = temp->nextNode;

	if (temp->nextNode != NULL) {
		if (newNode->vertices == temp->nextNode->vertices) {
			//loop
			//�ִܰŸ��� �ʿ��ѵ� ���� weight���� ���� ��带 ������ �ʿ� ����
			if (newNode->weight < temp->nextNode->weight)
				temp->nextNode->weight = newNode->weight;
			free(newNode);
		}
		else {
			newNode->nextNode = temp->nextNode;
			temp->nextNode = newNode;
		}
	}
	else temp->nextNode = newNode;
}
