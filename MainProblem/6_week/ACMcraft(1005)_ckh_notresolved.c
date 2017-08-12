#include <stdio.h>
#define MAXQUEUE 10000

typedef struct node {
	int num;
	int in;
	int time;
	struct node *nextNode;
}node;

typedef struct queue {
	int nodeNum;
	struct queue *nextNode;
}queue;

int nV, nE;
int targetStructure;
node *Graph;
queue *Queue;
void inqueue();
queue *dequeue();

void init();
void deinit();
void printGraph();
int TopologicalSort();
void nodeInsert(int s, int e);

int main() {
	int testCase=1;
	node *temp;
	printf("inq deq 테스트 \n");
	

	//scanf("%d", &testCase)
	for (int i = 0; i < testCase; i++) {
		init();
		scanf("%d", &targetStructure);
		printGraph();
		//printf("%d", TopologicalSort());
		deinit();
	}
	return 0;
}

void init() {
	int s, e;
	
	scanf("%d%d", &nV,&nE);
	Graph = (node*)malloc(sizeof(node)*(nV + 1));
	Queue = (queue*)malloc(sizeof(queue));
	Queue->nodeNum = -1;
	Queue->nextNode = NULL;
	for (int i = 1; i <= nV; i++) {
		Graph[i].num = i;
		Graph[i].in = 0;
		Graph[i].nextNode = NULL;
		scanf("%d", &Graph[i].time);
	}

	for (int i = 0; i < nE; i++) {
		scanf("%d%d", &s, &e);
		Graph[e].in++;
		nodeInsert(s, e);
	}

}
void deinit() {
	node *temp;
	for (int i = 1; i <= sizeof(Graph) / sizeof(node); i++) {
		temp = Graph[i].nextNode;
		while (temp != NULL) {
			Graph[i].nextNode = Graph[i].nextNode->nextNode;
			free(temp);
		}
	}
	temp;
	while (temp != NULL) {
		node *target;
		target = temp;
		temp = temp->nextNode;
		free(target);
	}

}
void inqueue() {
	if (Queue->nextNode == NULL) Queue->nextNode;
}
queue *dequeue() {

}

void printGraph() {
	for (int i = 1; i <= nV; i++) {
		node *temp = Graph[i].nextNode;
		printf("graph in : %d", Graph[i].in);
		while (temp!=NULL) {
			printf("  sub : %d ", temp->num);
			temp = temp->nextNode;
		}
		printf("\n");
	}
}

void nodeInsert(int s, int e) {
	node *newNode,*temp;
	newNode = (node*)malloc(sizeof(node));
	newNode->in = -1;
	newNode->num = Graph[e].num;
	newNode->time = Graph[e].time;
	newNode->nextNode = NULL;
	//newNode->in++;
	
	if (Graph[s].nextNode == NULL) Graph[s].nextNode = newNode;
	else {
		temp = Graph[s].nextNode;
		Graph[s].nextNode = newNode;
		newNode->nextNode = temp;
	}
}

int TopologicalSort() {
	node *temp;

	// in이 0인 노드를 찾아 inqueue
	for (int i = 1; i <= nV; i++) {
		if (Graph[i].in == 0) inqueue(retrieveQueue,&Graph[i]);
	}
	//dequeue 하면서 순회 시작
	temp = dequeue(retrieveQueue);
	printf("%d", temp->num, temp->in);
	while (temp != NULL) {
		printf("몇번 들어와");
		node *retrieveNode = Graph[temp->num].nextNode;
		while (retrieveNode != NULL) {
			if (Graph[retrieveNode->num].time + temp->time > Graph[retrieveNode->num].time)
				Graph[retrieveNode->num].time += temp->time;
			Graph[retrieveNode->num].in--;
			if(Graph[retrieveNode->num].in ==0)inqueue(retrieveQueue, &Graph[retrieveNode->num]);
			retrieveNode = retrieveNode->nextNode;
		}
		
		free(temp);
		temp = dequeue(retrieveQueue);
	}
	return Graph[targetStructure].time;
}