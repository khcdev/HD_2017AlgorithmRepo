#include <stdio.h>
#include <stdlib.h>
/* ����ũ ��Ʈ�� �˰��� */
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

int main() {

	//����, ���� ����
	int nVertices, nEdges;
	// index������ �Ÿ��� ��Ÿ���� �迭
	int *aryDistance;

	int startPoint;
	int targetIndex;

	priorityQueue data;
	/*----------Default Initialization----------*/
	scanf("%d%d", &nVertices, &nEdges);

	//��������������������������������������������������
	// sizeof(node)*nVertices+1 ���� , sizeof(node)*(nVertices+1) ���� ������ ��Ÿ�� ���� �߻�
	graphArr = (node*)malloc(sizeof(node)*(nVertices+1));
	for (int i = 0; i <= nVertices; i++) graphArr[i].nextNode = NULL;
	priority_Queue = (priorityQueue*)malloc(sizeof(priorityQueue) * 1000000);
	aryDistance = (int*)malloc(sizeof(int)*(nVertices + 1));

	scanf("%d", &startPoint);
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

	/*--------------Start Dijkstra--------------*/

	/*�켱���� ť ���*/
	//�����Ҷ� �ڱ� �ڽ�
	targetIndex = startPoint;
	aryDistance[startPoint] = 0;
	for (int i = 1; i <= nVertices; i++) 
		inqueue(i, aryDistance[i]);
	
	data = dequeue();//5,0
	while (data.vertices != -1) {
		//��ť �� ���� ���� �Ÿ����� ª���� ���� �˻�
		if (aryDistance[data.vertices] >= data.distance) {
			aryDistance[data.vertices] = data.distance;

			node *temp = graphArr[data.vertices].nextNode;
			//���� ��� �˻�
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
		/*�ڼ� ��� index�� ���ĵ� ��� �������� �ʱ� ����, �� ��ȿ�� ������ �ֵ���*/
		if (2 * temp < pointing) leftChild = 2 * temp;
		if (2 * temp + 1 < pointing) rightChild = 2 * temp + 1;

		switch (compareChildIndex(leftChild, rightChild)) {
		//�ڽ��� �ϳ��� ���� ���
		case 0:
			flag = 0;
			break;
		//�ڽ��� �ϳ��� �ִ� ���
		case 1:
			if (priority_Queue[leftChild].distance < priority_Queue[temp].distance)
				swap(&priority_Queue[leftChild], &priority_Queue[temp]);
			flag = 0;
			break;
		//�ڽ��� �Ѹ� �ִ� ���
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
