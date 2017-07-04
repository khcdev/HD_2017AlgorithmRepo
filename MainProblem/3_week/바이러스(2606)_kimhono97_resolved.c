#include <stdio.h>
#include <stdlib.h>

/* ----- DEFINITION ----- */
typedef int Bool;
enum BOOL{
	False, True
};

typedef int element;
typedef struct Node{
	element e;
	struct Node **links;
	int num_links;
	Bool isChecked;
}Node;
typedef Node* position;
typedef struct Graph{
	position *Nodes;
	int num;
}Graph;
#define NOT_DEFINED_INT -1

typedef position elem_q;
typedef int pos_q;
typedef struct Queue{
	elem_q *buffer;
	pos_q front;
	pos_q rear;
	int size;
	int capacity;
}Queue;


/* ----- FUNCTION :: Graph ----- */
position getNode(){
	position p;
	
	p = (position)malloc(1 * sizeof(Node));
	if(p == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	
	p->e = NOT_DEFINED_INT;
	p->links = NULL;
	p->num_links = 0;
	p->isChecked = False;
	
	return p;
}
void putNode(position p){
	if(p != NULL)	free(p);
}
void linkNode(position p, position q){
	p->links[q->e] = q;
	q->links[p->e] = p;
}
Graph *init(Graph *G, int N){
	int i, j;
	position p;
	
	G->num = N;
	G->Nodes = (position *)malloc(N * sizeof(position));
	if(G->Nodes == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	
	for(i=0; i<N; i++){
		p = getNode();
		if(p == NULL)			return NULL;
		
		p->e = i;
		p->links = (position *)malloc(N * sizeof(position));
		if(p->links == NULL)	return NULL;
		for(j=0; j<N; j++)		p->links[j] = NULL;
		p->num_links = N;
		
		G->Nodes[i] = p;
	}
	
	return G;
}
void destruct(Graph *G){
	int i, j;
	position p;
	
	if(G->Nodes != NULL){
		for(i=0; i<G->num; i++){
			p = G->Nodes[i];
			if(p != NULL){
				if(p->links != NULL){
					free(p->links);
				}
			}
			putNode(p);
		}
		free(G->Nodes);
	}
	G->num = 0;
}
void print(Graph *G){//monitering
	int i, j;
	position p;
	
	for(i=0; i<G->num; i++){
		p = G->Nodes[i];
		printf("_%d :", p->e + 1);
		for(j=0; j<p->num_links; j++){
			if(p->links[j] != NULL)	printf(" %d", p->links[j]->e+1);
			else					printf(" x");
		}
		printf("\n");
	}
}


/* ----- FUNCTION :: Queue ----- */
Queue *init_q(Queue *Q, int N){
	Q->buffer = (elem_q *)malloc(N * sizeof(elem_q));
	if(Q->buffer == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	Q->capacity = N;
	Q->size = 0;
	Q->front = 0;
	Q->rear = 0;
	
	return Q;
}
void destruct_q(Queue *Q){
	if(Q->buffer != NULL)	free(Q->buffer);
	Q->capacity = 0;
	Q->size = 0;
	Q->front = 0;
	Q->rear = 0;
}
Bool isEmpty_q(Queue *Q){
	return Q->size == 0;
}
Bool isFull_q(Queue *Q){
	return Q->size == Q->capacity;
}
pos_q nextPos_q(Queue *Q, pos_q p){
	return (p + 1)%Q->capacity;
}
pos_q enqueue(Queue *Q, elem_q e){
	pos_q p;
	
	if(isFull_q(Q)){
		printf("Queue is already full.\n");
		return NOT_DEFINED_INT;
	}
	
	p = Q->rear;
	Q->buffer[p] = e;
	Q->rear = nextPos_q(Q, p);
	Q->size += 1;
	
	return p;
}
elem_q dequeue(Queue *Q){
	elem_q e;
	
	if(isEmpty_q(Q)){
		printf("Queue is already empty.\n");
		return NULL;
	}
	
	e = Q->buffer[Q->front];
	Q->front = nextPos_q(Q, Q->front);
	Q->size -= 1;
	
	return e;
}
pos_q findElem_q(Queue *Q, elem_q target){
	pos_q p;
	
	for(p=Q->front; p<=Q->rear; p=nextPos_q(Q, p)){
		if(Q->buffer[p] == target)	return p;
	}
	
	return NOT_DEFINED_INT;
}


/* ----- FUNCTION :: Others ----- */
int infection_worm(Graph *PC){
	Queue X;
	position v, w;
	int cnt, i;
	
	/* ----- Queue 생성 및 초기화  ----- */
	if(PC->num == 0)				return;
	if(init_q(&X, PC->num) == NULL)	return;
	
	/* ----- Computer#1 부터 전파 ----- */
	enqueue(&X, PC->Nodes[0]);
	cnt = 0;
	while(!isEmpty_q(&X)){
		v = dequeue(&X);
		v->isChecked = True;
		cnt++;
		for(i=0; i<v->num_links; i++){
			w = v->links[i];
			if(w!=NULL && !w->isChecked && findElem_q(&X, w)==NOT_DEFINED_INT){
				enqueue(&X, w);
			}
		}
	}
	
	/* ----- Queue 소멸 ----- */
	destruct_q(&X);
	
	/* ----- Worm감염 PC 개수 반환  ----- */
	return cnt;
}


/* ----- FUNCTION :: MAIN ----- */
int main(){
	Graph X;
	int num_nodes, num_links;
	int i;
	element x, y;
	Bool flag;
	
	/* ----- Graph 생성 및 초기화 ----- */
	scanf("%d", &num_nodes);
	if(init(&X, num_nodes))		flag = True;
	else						flag = False;
	
	if(flag){
		/* ----- 입력 및 Graph 설정  ----- */
		scanf("%d", &num_links);
		for(i=0; i<num_links; i++){
			scanf("%d %d", &x, &y);
			linkNode(X.Nodes[x-1], X.Nodes[y-1]);
		}
		
		//print(&X);//mornitering
		
		/* ----- worm전파테스트 및 결과출력 ----- */
		printf("%d\n", infection_worm(&X)-1);	// except Computer#1 (Source of Worm)
	}
	
	/* ----- Graph 소멸 ----- */
	destruct(&X);
	
	return 0;
}
