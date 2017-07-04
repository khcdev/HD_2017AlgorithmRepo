#include <stdio.h>
#include <stdlib.h>

/* ----- DEFINITION ----- */
typedef int Bool;
enum BOOL{
	False, True
};

typedef int element;
typedef struct position{
	int x;
	int y;
}position;
typedef struct Graph{
	element **map;
	int row;
	int col;
}Graph;
enum STATUS{
	EMPTY, NOTCHECKED, CHECKED
};
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

typedef int elem_l;
typedef int pos_l;
typedef struct List{
	elem_l *buffer;
	int size;
	int unit;
	int capacity;
}List;
#define SIZE_UNIT 5


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
	Q->buffer = NULL;
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
		e.x = NOT_DEFINED_INT;
		e.y = NOT_DEFINED_INT;
		return e;
	}
	
	e = Q->buffer[Q->front];
	Q->front = nextPos_q(Q, Q->front);
	Q->size -= 1;
	
	return e;
}
pos_q findElem_q(Queue *Q, elem_q target){
	pos_q p;
	elem_q tmp;
	int i;
	
	p=Q->front;
	for(i=0; i<Q->size; i++){
		tmp = Q->buffer[p];
		if(tmp.x==target.x && tmp.y==target.y)	return p;
		
		p=nextPos_q(Q, p);
	}
	
	return NOT_DEFINED_INT;
}


/* ----- FUNCTION :: List ----- */
List *init_l(List *L, int unit){
	L->buffer = (elem_l *)malloc(unit * sizeof(elem_l));
	if(L->buffer == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	L->unit = unit;
	L->capacity = unit;
	L->size = 0;
	
	return L;
}
void destruct_l(List *L){
	if(L->buffer != NULL)	free(L->buffer);
	L->buffer = NULL;
	L->size = 0;
	L->unit = 0;
	L->capacity = 0;
}
Bool isFull(List *L){
	return L->size==L->capacity;
}
pos_l insert_l(List *L, elem_l e){
	pos_l p;
	
	if(isFull(L)){
		L->capacity += L->unit;
		L->buffer = (elem_l *)realloc(L->buffer, L->capacity * sizeof(elem_l));
		if(L->buffer == NULL){
			printf("Failed realloc.\n");
			return NOT_DEFINED_INT;
		}
	}
	p = L->size;
	L->buffer[p] = e;
	L->size += 1;
	
	return p;
}


/* ----- FUNCTION :: Graph ----- */
Graph *init(Graph *G, int row, int col){
	int i, j;
	
	G->map = (element **)malloc(row * sizeof(element *));
	if(G->map == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	
	for(i=0; i<row; i++){
		G->map[i] = (element *)malloc(col * sizeof(element));
		if(G->map[i] == NULL){
			printf("Failed malloc.\n");
			for(j=0; j<i; j++)	free(G->map[j]);
			free(G->map);
			return NULL;
		}
		
		for(j=0; j<col; j++){
			G->map[i][j] = NOT_DEFINED_INT;
		}
	}
	G->row = row;
	G->col = col;
	
	return G;
}
void destruct(Graph *G){
	int i;
	
	if(G->map != NULL){
		for(i=0; i<G->row; i++){
			if(G->map[i] != NULL)	free(G->map[i]);
		}
		free(G->map);
	}
	G->map = NULL;
	G->row = 0;
	G->col = 0;
}


/* ----- FUNCTION :: Other ----- */
void print(Graph *G){//monitering
	int i, j;
	char ch;
	
	printf("\n");
	for(i=0; i<G->row; i++){
		for(j=0; j<G->col; j++){
			switch(G->map[i][j]){
			case EMPTY:			ch='E'; break;
			case NOTCHECKED:	ch='N'; break;
			case CHECKED:		ch='C'; break;
			default:			ch='x'; break;
			}
			printf(" %c", ch);
		}
		printf("\n");
	}
}
position findNOTCHECKED(Graph *G){
	position p;
	int i, j;
	
	p.x = NOT_DEFINED_INT;
	p.y = NOT_DEFINED_INT;
	
	for(i=0; i<G->row; i++){
		for(j=0; j<G->col; j++){
			if(G->map[i][j] == NOTCHECKED){
				p.x = j;
				p.y = i;
				return p;
			}
		}
	}
	
	return p;
}
int cntHouse(Graph *G, position p){
	Queue X;
	position v, w;
	int cnt;
	Bool flag;
	
	if(!init_q(&X, G->col*G->row)){
		return NOT_DEFINED_INT;
	}
	
	cnt = 0;
	enqueue(&X, p);
	while(!isEmpty_q(&X)){
		//print(G);//monitering
		v = dequeue(&X);
		G->map[v.y][v.x] = CHECKED;
		cnt++;
		if(v.x != 0){			// enqueue LEFT
			w.x = v.x-1;
			w.y = v.y;
			flag = True;
			flag = flag && (G->map[w.y][w.x]==NOTCHECKED);
			flag = flag && (findElem_q(&X, w)==NOT_DEFINED_INT); 
			if(flag) enqueue(&X, w);
		}
		if(v.x != G->col-1){	// enqueue RIGHT
			w.x = v.x+1;
			w.y = v.y;
			flag = True;
			flag = flag && (G->map[w.y][w.x]==NOTCHECKED);
			flag = flag && (findElem_q(&X, w)==NOT_DEFINED_INT); 
			if(flag) enqueue(&X, w);
		}
		if(v.y != 0){			// enqueue UP
			w.x = v.x;
			w.y = v.y-1;
			flag = True;
			flag = flag && (G->map[w.y][w.x]==NOTCHECKED);
			flag = flag && (findElem_q(&X, w)==NOT_DEFINED_INT); 
			if(flag) enqueue(&X, w);
		}
		if(v.y != G->row-1){	// enqueue DOWN
			w.x = v.x;
			w.y = v.y+1;
			flag = True;
			flag = flag && (G->map[w.y][w.x]==NOTCHECKED);
			flag = flag && (findElem_q(&X, w)==NOT_DEFINED_INT);
			if(flag) enqueue(&X, w);
		}
	}
	
	destruct_q(&X);
	
	return cnt;
}
List *tagging(Graph *G){
	List *L;
	position p;
	
	L = (List *)malloc(1 * sizeof(List));
	if(L == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	if(!init_l(L, SIZE_UNIT))	return NULL;
	while(True){
		p = findNOTCHECKED(G);
		if(p.x==NOT_DEFINED_INT || p.y==NOT_DEFINED_INT)	break;
		insert_l(L, cntHouse(G, p));
	}
	
	return L;
}
void sort(List *L){
	int i, cnt;
	elem_l tmp;
	
	do{
		cnt = 0;
		for(i=1; i<L->size; i++){
			if(L->buffer[i-1] > L->buffer[i]){
				tmp = L->buffer[i-1];
				L->buffer[i-1] = L->buffer[i];
				L->buffer[i] = tmp;
				cnt++;
			}
		}
	}while(cnt);
}


/* ----- FUNCTION :: MAIN ----- */
int main(){
	Graph X;
	List *L;
	int N, i, j;
	
	scanf("%d", &N);
	getchar();		// remove '\n' from stdin buffer
	if(!init(&X, N, N))	return -1;
	
	for(i=0; i<X.row; i++){
		for(j=0; j<X.col; j++){
			X.map[i][j] = getchar()-'0';
		}
		getchar();	// remove '\n' from stdin buffer
	}
	
	
	L = tagging(&X);
	if(L != NULL){
		sort(L);
		printf("%d\n", L->size);
		for(i=0; i<L->size; i++){
			printf("%d\n", L->buffer[i]);
		}
		destruct_l(L);
		free(L);
	}
	
	destruct(&X);
	
	return 0;
}
