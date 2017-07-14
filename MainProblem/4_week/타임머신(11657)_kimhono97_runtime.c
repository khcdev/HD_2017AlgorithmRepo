#include <stdio.h>
#include <stdlib.h>

typedef int Bool;
enum BOOL{
	False, True
};

typedef int element;
typedef int wage;
typedef struct Path{
		void *pos;	// stores Node's position
		wage w;
}Path;
typedef struct Node{
	element e;
	Path *pathes;
	int num_path;
}Node;
typedef Node* position;
typedef struct Graph{
	position nodes;
	int num;
}Graph;
#define NOT_DEFINED_INT -999999999
#define INF 999999999

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
int addPath(Graph *G, element u, element v, wage w){
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
		pU->pathes = (Path *)malloc(1 * sizeof(Path));
		if(pU->pathes == NULL){
			printf(ERR_FM);
			return NOT_DEFINED_INT;
		}
	}else{
		pU->pathes = (Path *)realloc(pU->pathes, (n + 1) * sizeof(Path));
		if(pU->pathes == NULL){
			printf(ERR_FM);
			return NOT_DEFINED_INT;
		}
	}
	pU->pathes[n].pos = pV;
	pU->pathes[n].w = w;
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
			q = p->pathes[j].pos;
			printf(" %d(w=%d)", q->e, p->pathes[j].w);
		}
		printf("\n");
	}
}
int rRoute(Graph *G, element src, element des){
	position pS, pD, pO, p;
	Path *path;
	int i, min;
	wage r;
	
	if(src == des)			return 0;
	
	pS = getPos(G, src);
	pD = getPos(G, des);
	if(pS==NULL || pD==NULL){
		printf(ERR_NEE);
		return NOT_DEFINED_INT;
	}
	
	if(pS->num_path == 0)	return INF;	
	
	min = NOT_DEFINED_INT;
	for(i=0; i<pS->num_path; i++){
		path = pS->pathes + i;
		p = path->pos;
		
		if(p == pD){
			r = path->w;
			
			if(min == NOT_DEFINED_INT){
				min = r;
			}else{
				if(min > r)	min = r;
			}
		}
	}
	if(min != NOT_DEFINED_INT)	return min;
	
	for(i=0; i<pS->num_path; i++){
		path = pS->pathes + i;
		p = path->pos;
		
		r = rRoute(G, p->e, des);
		if(r != INF){
			r += path->w;
			if(min == NOT_DEFINED_INT){
				min = r;
			}else{
				if(min > r)	min = r;
			}
		}
	}
	
	return min==NOT_DEFINED_INT ? INF : min;
}
int route(Graph *G, element src, element des){
	int s2d, d2s;
	
	s2d = rRoute(G, src, des);
	if(s2d==INF || s2d==NOT_DEFINED_INT)	return s2d;
	
	d2s = rRoute(G, des, src);
	
	return s2d+d2s<0 ? INF : s2d;  
}


int main() {
	Graph X;
	int V, E, i;
	element u, v, src, des;
	wage w;
	
	scanf("%d %d", &V, &E);
	src = 1;
	if(init(&X, V) != NULL){
		for(i=0; i<E; i++){
			scanf("%d %d %d", &u, &v, &w);
			addPath(&X, u, v, w);
		}
		
		//print(&X);	//monitering
		
		for(i=1; i<V; i++){
			w = route(&X, src, i+1);
			if(w == INF){
				printf("-1\n");
				break;
			}
			else	printf("%d\n", w);
		}
	}
	
	destruct(&X);
	
	return 0;
}
