#include <stdio.h>
#include <stdlib.h>
/* 데이크 스트라 알고리즘 */
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

	//정점, 간선 개수
	int nVertices, nEdges;
	//인접 배열, 값으로 가중치 가짐
	int **aryAdjacent;
	// index까지의 거리를 나타내는 배열
	int *aryDistance;
	// 노드의 방문 여부
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
	//인접 배열 초기화 가중치 초기화
	for (int i = 0; i < nEdges; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		//방향그래프이기 때문에 한번만 호출 하면 됨.
		nodeInsertIntoList(&graphArr[t1], t2, t3);
	}

	/*
	printf("======인접리스트 확인=====\n");
	for (int i = 1; i <= nVertices; i++) {
		node *temp = graphArr[i].nextNode;
		printf(" %d 번에 연결된 정점  \n",i);
		while (temp != NULL) {
			printf("정점 : %d, 가중치 : %d\n", temp->vertices, temp->weight);
			temp = temp->nextNode;
		}
	}*/
	//임의의 무한한 값으로 거리값 초기화
	for (int i = 0; i <= nVertices; i++) {
		aryDistance[i] = INFINITE;
		aryVisit[i] = 0; 
	}
	/*------------------------------------------*/

	/*--------------Start Dijkstra--------------*/

	//시작하는 노드는 거리를 0으로 초기화 한다.
	aryDistance[startPoint] = 0;
	for (int i = 0; i<nVertices; i++) {//정점의 수만큼 반복된다.    n
		int min = INFINITE + 1;	//min 값을 통한 
		targetIndex = -1;

		//최소 거리를 찾는 작업(가중치가 가장 적은 곳의 index값을 얻기 위함)
		for (int k = 1; k <= nVertices; k++) {

			//방문하지 않았으면서 dist배열의 값이 가장 최소인것
			if (aryVisit[k] == 0 && min > aryDistance[k]) {
				targetIndex = k;
				min = aryDistance[k];
			}
		}//n
		aryVisit[targetIndex] = 1;
		//값의 교체
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