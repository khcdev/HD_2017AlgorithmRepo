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
typedef struct Node_l{
	elem_l e;
	struct Node_l *next;
	struct Node_l *prev;
}Node_l;
typedef Node_l* pos_l;
typedef struct List{
	pos_l Header;
	int num;
}List;

#define ERR_NEE "Not Exist Element.\n"
#define ERR_FM "Failed malloc.\n"

//#define DEBUG


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
		
		printf("[%d(d=%d)] :", p->e, p->d);
		for(j=0; j<p->num_path; j++){
			q = p->pathes[j];
			printf(" %d", q->e);
		}
		printf("\n");
	}
}

pos_l getNode_l(){
	pos_l p;
	
	p = (pos_l)malloc(1 * sizeof(Node_l));
	if(p == NULL){
		printf(ERR_FM);
		return NULL;
	}
	
	p->e = NULL;
	p->next = NULL;
	p->prev = NULL;
	
	return p;
}
void putNode_l(pos_l p){
	if(p != NULL)	free(p);
}
void linkNode_l(pos_l p, pos_l q){
	if(p != NULL)	p->next = q;
	if(q != NULL)	q->prev = p;
}
List *init_l(List *L){
	L->Header = getNode_l();
	if(L->Header == NULL)	return NULL;
	
	L->num = 0;
	
	return L;
}
void clear_l(List *L){
	pos_l p, next;
	
	if(L->Header == NULL)	return;
	
	p = L->Header->next;
	while(p){
		next = p->next;
		putNode_l(p);
		p = next;
	}
	
	linkNode_l(L->Header, NULL);
	L->num = 0;
}
void destruct_l(List *L){
	clear_l(L);
	putNode_l(L->Header);
}
Bool isEmpty_l(List *L){
	return (L->num == 0);
}
pos_l append_l(List *L, elem_l e){
	pos_l p;
	
	p = getNode_l();
	if(p==NULL)	return NULL;
	
	p->e = e;
	linkNode_l(p, L->Header->next);
	linkNode_l(L->Header, p);
	L->num += 1;
	
	return p;
}
elem_l remove_l(List *L, pos_l p){
	elem_l e;
	
	if(p==NULL){
		printf(ERR_NEE);
		return NULL;
	}
	
	e = p->e;
	linkNode_l(p->prev, p->next);
	L->num -= 1;
	
	return e;
}
pos_l getPos_l(List *L, elem_l e){
	pos_l p;
	
	if(L->Header==NULL)	return NULL;
	
	p = L->Header->next;
	while(p){
		if(p->e == e)	return p;
		p = p->next;
	}
	
	return NULL;
}
void print_l(List *L){
	pos_l p;
	
	if(L->Header==NULL){
		printf("None\n");
		return;
	}
	
	p = L->Header->next;
	printf("H -> ");
	while(p){
		printf("%d -> ", p->e->e);
		p = p->next;
	}
	printf("NULL\n");
}


delay calDelay(Graph *G, element W){
	List targets;
	delay t, min;
	position p, pW;
	pos_l lp;
	Bool loop;
	int *dep;
	int i, j;
	
	pW = getPos(G, W);
	if(pW == NULL){
		printf(ERR_NEE);
		return NOT_DEFINED_INT;
	}
	
	init_l(&targets);
	t = 0;
	dep = (int *)malloc(G->num * sizeof(int));
	if(dep == NULL){
		printf(ERR_FM);
		destruct_l(&targets);
		return NOT_DEFINED_INT;
	}
	
	loop = True;
	while(loop){		
		for(i=0; i<G->num; i++){
			switch(G->nodes[i].s){
			case READY:		dep[i] = 0; break;
			case RUNNING:	dep[i] = -1; break;
			case FINISHED:	dep[i] = -2; break;
			}
		}
		for(i=0; i<G->num; i++){
			p = G->nodes + i;
			if(p->s == FINISHED)	continue;
			for(j=0; j<p->num_path; j++){
				dep[p->pathes[j]->e - 1] ++;
			}
		}
		for(i=0; i<G->num; i++){
			p = G->nodes + i;
			if(dep[i]==0){
				append_l(&targets, p);
				p->s = RUNNING;
			}
		}

#ifdef DEBUG
		printf("\nt=%d\n", t);//monitering
		print(G);//monitering
		for(i=0; i<G->num; i++){//monitering
			printf("dep(%d) : %d\n", i+1, dep[i]);
		}
		print_l(&targets);//monitering
		
		if(isEmpty_l(&targets)){
			return -1;
		}
#endif		
		
		min = INF;
		lp = targets.Header->next;
		while(lp){
			p = lp->e;
			if(min > p->d)	min = p->d;
			lp = lp->next;
		}
		t += min;
		
		lp = targets.Header->next;
		while(lp){
			p = lp->e;
			p->d -= min;
			if(p->d <= 0){
				remove_l(&targets, lp);
				p->s = FINISHED;
				if(p == pW){
					clear_l(&targets);
					loop = False;
					break;
				}
			}
			lp = lp->next;
		}
	}
	
	destruct_l(&targets);
	
	return t;
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
		addPath(&Z, X, Y);
	}

#ifdef DEBUG	
	print(&Z);//monitering
#endif
	
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
