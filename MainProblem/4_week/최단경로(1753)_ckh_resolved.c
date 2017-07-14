#include <stdio.h>
#include <stdlib.h>
/* 汽戚滴 什闘虞 硝壱軒葬 */
#define INFINITE 100000
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

void nodeInsertIntoList(node *Head, int vertix,int weight);
void inqueue(int vertices, int distance);
priorityQueue dequeue();
void swap(priorityQueue *a, priorityQueue *b);
int compareChildIndex(int left, int right);
//void printQueue();

int main() {

	//舛繊, 娃識 鯵呪
	int nVertices, nEdges;
	// index猿走税 暗軒研 蟹展鎧澗 壕伸
	int *aryDistance;

	int startPoint;
	int targetIndex;

	priorityQueue data;
	/*----------Default Initialization----------*/
	scanf("%d%d", &nVertices, &nEdges);

	//せせせせせせせせせせせせせせせせせせせせせせせせせ
	// sizeof(node)*nVertices+1 葵引 , sizeof(node)*(nVertices+1) 託戚 凶庚拭 訓展績 神嫌 降持
	graphArr = (node*)malloc(sizeof(node)*(nVertices+1));
	for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;
	priority_Queue = (priorityQueue*)malloc(sizeof(priorityQueue) * 1000000);
	aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));
	/*
	inqueue(1, 2, 3);
	printQueue();
	inqueue(1, 4, 3);
	printQueue();
	inqueue(1, 1, 3);
	printQueue();
	inqueue(1, 3, 3);
	printQueue();
	inqueue(1, 7, 3);
	printQueue();
	inqueue(1, 6, 3);
	printQueue();
	inqueue(1, 5, 3);
	printQueue();
	inqueue(1, 9, 3);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("dequeue 衣引 : %d\n", dequeue().distance);
	printQueue();
	printf("\n 泥 砺什闘 魁\n");
	system("pause");*/
	//
	scanf("%d", &startPoint);
	//昔羨 壕伸 段奄鉢 亜掻帖 段奄鉢
	for (int i = 0; i < nEdges; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		//号狽益掘覗戚奄 凶庚拭 廃腰幻 硲窒 馬檎 喫.
		nodeInsertIntoList(&graphArr[t1], t2, t3);
	}

	for (int i = 0; i <= nVertices; i++) {
		aryDistance[i] = INFINITE;
	}
	/*------------------------------------------*/

	/*--------------Start Dijkstra--------------*/

	/*酔識授是 泥 紫遂*/
	//獣拙拝匡 切奄 切重
	targetIndex = startPoint;
	aryDistance[startPoint] = 0;
	for (int i = 1; i <= nVertices; i++) 
		inqueue(i, aryDistance[i]);
	
	data = dequeue();//5,0,-1
	while (data.vertices != -1) {
		//巨泥 吉 叶戚 薄仙 暗軒左陥 捉精走 延走 伊紫
		if (aryDistance[data.vertices] >= data.distance) {
			aryDistance[data.vertices] = data.distance;

			node *temp = graphArr[data.vertices].nextNode;
			//昔羨 葛球 伊紫
			while (temp!=NULL) {
				if (aryDistance[temp->vertices] > aryDistance[data.vertices] + temp->weight) {
					aryDistance[temp->vertices] = aryDistance[data.vertices] + temp->weight;
					inqueue(temp->vertices, aryDistance[temp->vertices]);
				}
				temp = temp->nextNode;
			}
		}
		data = dequeue();
	}

	/*------------------Result------------------*/
	for (int i = 1; i <= nVertices; i++) {
		if (aryDistance[i] != INFINITE) printf("%d\n",aryDistance[i]);
		else printf("INF\n");
	}
	/*------------------------------------------*/
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

	/*if (temp->nextNode == NULL) {
		temp->nextNode = newNode;
		return;
	}*/

	while (temp->nextNode != NULL && 
		temp->nextNode->vertices < newNode->vertices)
		temp = temp->nextNode;

	if (temp->nextNode != NULL) {
		if (newNode->vertices == temp->nextNode->vertices) {
			//loop
			//置舘暗軒幻 琶推廃汽 瓜戚 weight葵戚 株精 葛球研 諮脊拝 琶推 蒸製
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
		if (priority_Queue[temp].distance < priority_Queue[temp / 2].distance) {
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
		/*切謝 葛球 index亜 舛慶吉 衣引 凧繕馬走 省奄 是背, 聡 政反廃 骨是拭 赤亀系*/
		if (2 * temp < pointing) leftChild = 2 * temp;
		if (2 * temp + 1 < pointing) rightChild = 2 * temp + 1;

		switch (compareChildIndex(leftChild, rightChild)) {
		//切縦戚 馬蟹亀 蒸澗 井酔
		case 0:
			flag = 0;
			break;
		//切縦戚 馬蟹幻 赤澗 井酔
		case 1:
			if (priority_Queue[leftChild].distance < priority_Queue[temp].distance)
				swap(&priority_Queue[leftChild], &priority_Queue[temp]);
			flag = 0;
			break;
		//切縦戚 却幻 赤澗 井酔
		case 2:
			if (priority_Queue[leftChild].distance <= priority_Queue[rightChild].distance)
				target = leftChild;
			else target = rightChild;

			if (priority_Queue[target].distance < priority_Queue[temp].distance) {
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
/*
void printQueue() {
	int i;
	printf("\n");
	for (i = 1; i < pointing; i++) {
		printf("%d ", priority_Queue[i].distance);
	}
}*/