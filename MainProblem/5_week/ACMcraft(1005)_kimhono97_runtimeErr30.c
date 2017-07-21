#include <stdio.h>
#include <stdlib.h>

typedef int Bool;
enum BOOL{
	False, True
};

typedef int Status;
enum STATUS{
	READY, RUNNING, FINISHED
};

typedef int element;
typedef int delay;
typedef struct Node{
	element e;
	delay d;
	Status s;
	struct Node **pathes;
	int num_path;
}Node;
typedef Node* position;
typedef struct Graph{
	position nodes;
	int num;
}Graph;
#define NOT_DEFINED_INT -999999999
#define INF 999999999

typedef position elem_l;
typedef struct List{
	elem_l *buffer;
	int unit;
	int size;
	int capacity;
}List;
typedef struct MultiList{
	List *lists;
	int n;
}MultiList;
const int UNIT = 5;

#define ERR_NEE "Not Exist Element.\n"
#define ERR_FM "Failed malloc.\n"


Graph *init(Graph *G, int N){
	int i;
	position p;
	
	G->nodes = (position)malloc(N * sizeof(Node));
	if(G->nodes == NULL){
		printf(ERR_FM);
		return NULL;
	}
	G->num = N;
	
	for(i=0; i<G->num; i++){
		p = G->nodes + i;
		
		p->e = i+1;
		p->s = READY;
		p->d = NOT_DEFINED_INT;
		p->num_path = 0;
		p->pathes = NULL;
	}
	
	return G;
}
void destruct(Graph *G){
	int i;
	position p;
	
	if(G->nodes != NULL){
		for(i=0; i<G->num; i++){
			p = G->nodes + i;
			if(p->pathes != NULL)	free(p->pathes);
		}
		free(G->nodes);
	}
}
position getPos(Graph *G, element e){
	if(e < 1 || e > G->num)		return NULL;
	else						return G->nodes + (e-1);
}
int addPath(Graph *G, element u, element v){
	position pU, pV;
	int n;
	
	pU = getPos(G, u);
	pV = getPos(G, v);
	if(pU==NULL || pV==NULL){
		printf(ERR_NEE);
		return NOT_DEFINED_INT;
	}
	
	n = pU->num_path;
	if(n == 0){
		pU->pathes = (position *)malloc(1 * sizeof(position));
		if(pU->pathes == NULL){
			printf(ERR_FM);
			return NOT_DEFINED_INT;
		}
	}else{
		pU->pathes = (position *)realloc(pU->pathes, (n + 1) * sizeof(position));
		if(pU->pathes == NULL){
			printf(ERR_FM);
			return NOT_DEFINED_INT;
		}
	}
	pU->pathes[n] = pV;
	pU->num_path += 1;
	
	return n;
}
void print(Graph *G){ //monitering
	int i, j;
	position p, q;
	
	for(i=0; i<G->num; i++){
		p = G->nodes + i;
		
		printf("[%d] :", p->e);
		for(j=0; j<p->num_path; j++){
			q = p->pathes[j];
			printf(" %d", q->e);
		}
		printf("\n");
	}
}

List *init_l(List *L, int unit){
	int i;
	
	L->buffer = (elem_l *)malloc(unit * sizeof(elem_l));
	if(L->buffer == NULL){
		printf(ERR_FM);
		return NULL;
	}
	
	for(i=0; i<unit; i++){
		L->buffer[i] = NULL;
	}
	L->unit = unit;
	L->capacity = unit;
	L->size = 0;
	
	return L;
}
void destruct_l(List *L){
	if(L->buffer != NULL)	free(L->buffer);
}
Bool isEmpty_l(List *L){
	return L->size==0;
}
Bool isFull_l(List *L){
	return L->size==L->capacity;
}
int enqueue(List *L, elem_l e){
	int x;
	
	x = L->size;
	
	if(isFull_l(L)){
		L->buffer = (elem_l *)realloc(L->buffer, (L->unit + L->capacity)*sizeof(elem_l));
		if(L->buffer==NULL){
			printf(ERR_FM);
			return NOT_DEFINED_INT;
		}
	}
	
	L->buffer[x] = e;
	L->size += 1;
	
	return 0;
}

MultiList *init_ml(MultiList *ML, int unit){
	ML->lists = (List *)malloc(1 * sizeof(List));
	if(ML->lists == NULL){
		printf(ERR_FM);
		return NULL;
	}
	if(init_l(ML->lists+0, unit) == NULL)	return NULL;
	ML->n = 1;
	
	return ML;
}
void destruct_ml(MultiList *ML){
	int i;
	
	for(i=0; i<ML->n; i++){
		destruct_l(ML->lists + i);
	}
}
List *newList(MultiList *ML, int unit){
	int x;
	
	x = ML->n;
	ML->lists = (List *)realloc(ML->lists, (x+1) * sizeof(List));
	if(ML->lists == NULL){
		printf(ERR_FM);
		return NULL;
	}
	init_l(ML->lists + x, unit);
	ML->n = x + 1;
	
	return ML->lists + x;
}
void print_ml(MultiList *ML){//monitering
	int i, j;
	List *L;
	position p;
	
	for(i=0; i<ML->n; i++){
		printf("List %d : ", i);
		L = ML->lists + i;
		for(j=0; j<L->size; j++){
			p = L->buffer[j];
			printf("%d(d=%d, s=%c) -> ", p->e, p->d, p->s==READY?'R':'N');
		}
		printf("END\n");
	}
	printf("\n");
}

void rGetRoute(MultiList *ML, List *L, elem_l e){
	int i;
	
	enqueue(L, e);
	
	if(e->num_path == 0)	return;
	
	rGetRoute(ML, L, e->pathes[0]);
	for(i=1; i<e->num_path; i++){
		rGetRoute(ML, newList(ML, UNIT), e->pathes[i]);
	}
}
position getRoute(Graph *G, MultiList *ML, element W){
	position pW;
	
	pW = getPos(G, W);
	if(pW == NULL){
		printf(ERR_FM);
		return NULL;
	}
	
	rGetRoute(ML, ML->lists+0, pW);
	
	return pW;
}
delay calDelay(Graph *G, element W){
	MultiList R;
	delay sum;
	position pW, p;
	List *L;
	int i, j, cnt;
	
	if(init_ml(&R, UNIT) == NULL){
		destruct_ml(&R);
		return NOT_DEFINED_INT;
	}
	
	pW = getRoute(G, &R, W);
	if(pW == NULL){
		return NOT_DEFINED_INT;
	}
	
	sum = 0;
	while(pW->s != FINISHED){
		//print_ml(&R);//monitering
		for(i=0; i<R.n; i++){
			L = R.lists + i;
			
			if(isEmpty_l(L))		continue;
			
			p = L->buffer[L->size-1];
			
			switch(p->s){
			case FINISHED:
				L->size -= 1;
				if(isEmpty_l(L))	continue;
				p = L->buffer[L->size-1];
			case READY:
				cnt = 0;
				for(j=0; j<p->num_path; j++){
					if(p->pathes[j]->s != FINISHED) cnt++;
				}
				if(cnt > 0)			continue;
				else			p->s = RUNNING;
			}
		}
		for(i=0; i<G->num; i++){
			p = G->nodes + i;
			
			if(p->s == RUNNING){
				p->d -= 1;
				if(p->d <= 0){
					p->s = FINISHED;
				}
			}
		}
		sum++;
	}
	
	
	destruct_ml(&R);
	
	return sum;
}
int test(){
	Graph Z;
	int N, K, i;
	element X, Y, W;
	delay D;
	
	
	scanf("%d %d", &N, &K);
	if(init(&Z, N)==NULL)	return -1;
	
	for(i=0; i<Z.num; i++){
		scanf("%d", &D);
		Z.nodes[i].d = D;
	}
	
	for(i=0; i<K; i++){
		scanf("%d %d", &X, &Y);
		addPath(&Z, Y, X);
	}
	
	//print(&Z);//monitering
	
	scanf("%d", &W);
	
	printf("%d\n", calDelay(&Z, W));
	
	destruct(&Z);
	return 0;
}


int main(){
	int T;
	int i;
	
	scanf("%d", &T);
	for(i=0; i<T; i++){
		test();
	}
	
	return 0;
}
