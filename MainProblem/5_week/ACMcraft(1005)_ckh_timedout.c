#include <stdio.h>
#include <stdlib.h>
/* 데이크 스트라 알고리즘 */
#define INFINITE -1
typedef struct node {
	int vertices;
	int weight;
	struct node *nextNode;
}node;

typedef struct priorityQueue {
	int vertices;
	int distance;
}priorityQueue;

priorityQueue *priority_Queue;
int pointing = 1;

node *graphArr;
node *getNode();

void nodeInsertIntoList(node *Head, int vertix, int weight);
void inqueue(int vertices, int distance);
priorityQueue dequeue();
void swap(priorityQueue *a, priorityQueue *b);
int compareChildIndex(int left, int right);
void printQueue();

int main() {
	int T;
	int sol;

	int nVertices, nEdges;
	// index까지의 거리를 나타내는 배열
	int *aryDistance;

	int startPoint;
	int targetIndex;

	priorityQueue data;

	scanf("%d", &T);
	//정점, 간선 개수
	for (int c = 0; c < T; c++) {
		
		/*----------Default Initialization----------*/
		scanf("%d%d", &nVertices, &nEdges);

		// sizeof(node)*nVertices+1 값과 , sizeof(node)*(nVertices+1) 차이 때문에 런타임 오류 발생
		graphArr = (node*)malloc(sizeof(node)*(nVertices + 1));
		for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;
		priority_Queue = (priorityQueue*)malloc(sizeof(priorityQueue) * 1000000);
		aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));
		for (int i = 1; i <= nVertices; i++) scanf("%d", &graphArr[i].weight);

		//인접 배열 초기화 가중치 초기화
		for (int i = 0; i < nEdges; i++) {
			int t1, t2;
			scanf("%d%d", &t1, &t2);
			//방향그래프이기 때문에 한번만 호출 하면 됨.
			nodeInsertIntoList(&graphArr[t1], t2, graphArr[t2].weight);
		}
		scanf("%d", &sol);
		for (int i = 0; i <= nVertices; i++) {
			aryDistance[i] = INFINITE;
		}
		/*------------------------------------------*/

		/*--------------Start Dijkstra--------------*/

		/*우선순위 큐 사용*/
		//시작할땐 자기 자신
		startPoint = 1;
		targetIndex = startPoint;
		aryDistance[startPoint] = graphArr[startPoint].weight;
		for (int i = 1; i <= nVertices; i++)
			inqueue(i, aryDistance[i]);

		data = dequeue();//5,0,-1
		while (data.vertices != -1) {
			//디큐 된 놈이 현재 거리보다 짧은지 긴지 검사
			if (aryDistance[data.vertices] <= data.distance) {
				aryDistance[data.vertices] = data.distance;

				node *temp = graphArr[data.vertices].nextNode;
				//인접 노드 검사
				while (temp != NULL) {
					if (aryDistance[temp->vertices] < aryDistance[data.vertices] + temp->weight) {
						aryDistance[temp->vertices] = aryDistance[data.vertices] + temp->weight;
						inqueue(temp->vertices, aryDistance[temp->vertices]);
					}
					temp = temp->nextNode;
				}
			}
			data = dequeue();
		}

		/*------------------Result------------------*/
		/*for (int i = 1; i <= nVertices; i++) {
			if (aryDistance[i] != INFINITE) printf("%d\n", aryDistance[i]);
			else printf("INF\n");
		}*/
		printf("%d\n", aryDistance[sol]);
		/*------------------------------------------*/
		free(aryDistance);
		free(priority_Queue);
		for (int i = 0; i <= nVertices; i++) {
			node *temp = graphArr[i].nextNode;
			while (temp != NULL) {
				node *delTarget = temp;
				temp = temp->nextNode;
				//printf("%d 노드에 인접한 삭제 확인 : %d", i,delTarget->vertices);
				free(delTarget);
			}
		}
		free(graphArr);
		//동적할당 해제
	}
	return 0;
}

void swap(priorityQueue *a, priorityQueue *b) {
	priorityQueue temp = *a;
	*a = *b;
	*b = temp;
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
		newNode->nextNode = temp->nextNode;
		temp->nextNode = newNode;
	}
	else temp->nextNode = newNode;
}

void inqueue(int vertices, int distance) {
	priorityQueue data;
	int temp;
	data.vertices = vertices;
	data.distance = distance;

	priority_Queue[pointing] = data;
	if (pointing == 1) {
		pointing++;
		return;
	}
	temp = pointing;
	while (temp / 2 != 0) {
		if (priority_Queue[temp].distance > priority_Queue[temp / 2].distance) {
			swap(&priority_Queue[temp], &priority_Queue[temp / 2]);
			temp = temp / 2;
		}
		else break;
	}
	pointing++;
	return;
}

priorityQueue dequeue() {
	priorityQueue deqData;
	int flag = 1;
	int temp;
	int target = -1;
	if (pointing == 1) {
		deqData.vertices = -1;
		return deqData;
	}
	deqData = priority_Queue[1];
	priority_Queue[1] = priority_Queue[pointing - 1];
	pointing--;
	temp = 1;
	while (flag) {
		int leftChild = -1, rightChild = -1;
		/*자손 노드 index가 정렬된 결과 참조하지 않기 위해, 즉 유효한 범위에 있도록*/
		if (2 * temp < pointing) leftChild = 2 * temp;
		if (2 * temp + 1 < pointing) rightChild = 2 * temp + 1;

		switch (compareChildIndex(leftChild, rightChild)) {
			//자식이 하나도 없는 경우
		case 0:
			flag = 0;
			break;
			//자식이 하나만 있는 경우
		case 1:
			if (priority_Queue[leftChild].distance > priority_Queue[temp].distance)
				swap(&priority_Queue[leftChild], &priority_Queue[temp]);
			flag = 0;
			break;
			//자식이 둘만 있는 경우
		case 2:
			if (priority_Queue[leftChild].distance < priority_Queue[rightChild].distance)
				target = rightChild;
			else target = leftChild;

			if (priority_Queue[target].distance > priority_Queue[temp].distance) {
				swap(&priority_Queue[target], &priority_Queue[temp]);
				temp = target;
			}
			else flag = 0;
			break;
		}
	}

	return deqData;

}

int compareChildIndex(int left, int right) {
	if (left == -1 && right == -1) return 0;
	if (left != -1 && right == -1) return 1;
	return 2;
}

void printQueue() {
int i;
printf("\n");
for (i = 1; i < pointing; i++) {
printf("%d ", priority_Queue[i].distance);
}
}