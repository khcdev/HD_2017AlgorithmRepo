#include <stdio.h>
#include <stdlib.h>
/* 벨만 포드 알고리즘 */
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

	//정점, 간선 개수
	int nVertices, nEdges;
	// index까지의 거리를 나타내는 배열
	int *aryDistance;

	int startPoint=1;
	int targetIndex;
	int minusCycle = 0;

	/*----------Default Initialization----------*/
	scanf("%d%d", &nVertices, &nEdges);


	graphArr = (node*)malloc(sizeof(node)*(nVertices+1));
	for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;
	aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));
	
	//인접 배열 초기화 가중치 초기화
	for (int i = 0; i < nEdges; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		//방향그래프이기 때문에 한번만 호출 하면 됨.
		nodeInsertIntoList(&graphArr[t1], t2, t3);
	}

	for (int i = 0; i <= nVertices; i++) {
		aryDistance[i] = INFINITE;
	}
	/*------------------------------------------*/


	/*--------------Start Bellman-Ford--------------*/
	// (v-1)에서 dist 배열이 완성 되어야 하고 v loop에서 값의 변경이 일어난다면 음수 사이클이 존재한다는 의미이다.
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
			//최단거리만 필요한데 굳이 weight값이 높은 노드를 삽입할 필요 없음
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
