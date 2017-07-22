#include <stdio.h>
#include <stdlib.h>
/* ����ũ ��Ʈ�� �˰��� */
#define INFINITE 100000
typedef struct node {
	int vertices;
	int weight;
	struct node *nextNode;
}node;

node *graphArr;
node *getNode();
void nodeInsertIntoList(node *Head, int vertix,int weight);
int getAdjInform(int v1,int v2);

int main() {

	//����, ���� ����
	int nVertices, nEdges;
	//���� �迭, ������ ����ġ ����
	int **aryAdjacent;
	// index������ �Ÿ��� ��Ÿ���� �迭
	int *aryDistance;
	// ����� �湮 ����
	int *aryVisit;
	int startPoint;
	int targetIndex;

	/*----------Default Initialization----------*/
	scanf("%d%d", &nVertices, &nEdges);

	graphArr = (node*)malloc(sizeof(node)*nVertices+1);
	for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;

	aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));
	aryVisit = (int*)malloc(sizeof(int)*(nVertices + 1));

	scanf("%d", &startPoint);
	//���� �迭 �ʱ�ȭ ����ġ �ʱ�ȭ
	for (int i = 0; i < nEdges; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		//����׷����̱� ������ �ѹ��� ȣ�� �ϸ� ��.
		nodeInsertIntoList(&graphArr[t1], t2, t3);
	}

	/*
	printf("======��������Ʈ Ȯ��=====\n");
	for (int i = 1; i <= nVertices; i++) {
		node *temp = graphArr[i].nextNode;
		printf(" %d ���� ����� ����  \n",i);
		while (temp != NULL) {
			printf("���� : %d, ����ġ : %d\n", temp->vertices, temp->weight);
			temp = temp->nextNode;
		}
	}*/
	//������ ������ ������ �Ÿ��� �ʱ�ȭ
	for (int i = 0; i <= nVertices; i++) {
		aryDistance[i] = INFINITE;
		aryVisit[i] = 0; 
	}
	/*------------------------------------------*/

	/*--------------Start Dijkstra--------------*/

	//�����ϴ� ���� �Ÿ��� 0���� �ʱ�ȭ �Ѵ�.
	aryDistance[startPoint] = 0;
	for (int i = 0; i<nVertices; i++) {//������ ����ŭ �ݺ��ȴ�.    n
		int min = INFINITE + 1;	//min ���� ���� 
		targetIndex = -1;

		//�ּ� �Ÿ��� ã�� �۾�(����ġ�� ���� ���� ���� index���� ��� ����)
		for (int k = 1; k <= nVertices; k++) {

			//�湮���� �ʾ����鼭 dist�迭�� ���� ���� �ּ��ΰ�
			if (aryVisit[k] == 0 && min > aryDistance[k]) {
				targetIndex = k;
				min = aryDistance[k];
			}
		}//n
		aryVisit[targetIndex] = 1;
		//���� ��ü
		for (int k = 1; k <= nVertices; k++) {
			int adj = getAdjInform(targetIndex, k);
			if (adj > 0 && aryDistance[k] > aryDistance[targetIndex] + adj) {
				aryDistance[k] = aryDistance[targetIndex] + adj;
			}
		}
	}

	/*------------------Result------------------*/
	for (int i = 1; i <= nVertices; i++) {
		if (aryDistance[i] != INFINITE) printf("%d\n",aryDistance[i]);
		else printf("INF\n");
	}
	/*------------------------------------------*/
	return 0;
}

node *getNode() {
	node *newNode;
	newNode = (node*)malloc(sizeof(node));
	return newNode;
}

void nodeInsertIntoList(node *Head, int vertices, int weight) {
	node *newNode, *temp;
	temp = Head;
	newNode = getNode();
	newNode->nextNode = NULL;
	newNode->vertices = vertices;
	newNode->weight = weight;

	if (temp->nextNode == NULL) {
		temp->nextNode = newNode;
		return;
	}

	while (temp->nextNode != NULL && 
		temp->nextNode->vertices < newNode->vertices)
		temp = temp->nextNode;

	if (temp->nextNode != NULL) {
		if (newNode->vertices == temp->nextNode->vertices) {
			//loop
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

int getAdjInform(int v1, int v2) {
	node *temp = graphArr[v1].nextNode;
	while (temp != NULL) {
		if (temp->vertices == v2) return temp->weight;
		temp = temp->nextNode;
	}
	return -1;
}