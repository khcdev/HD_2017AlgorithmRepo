#include <stdio.h>
#include <stdlib.h>


typedef int Bool;
enum BOOL{
	False, True
};

typedef int element;
typedef struct Node{
	element e;
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
		
		p->e = 0;
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
int addPath(Graph *G, position pU, position pV){
	int n;
	
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
	
	printf("\n");
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


position getPos(Graph *G, int i, int j){
	int n;
	
	if(i<0 || j<0 || j>i)		return NULL;
	
	n = i*(i+1)/2 + j;
	
	if(n >= G->num)		return NULL;
	
	return G->nodes + n;
}
int rGetMax(position p){
	int i, max, tmp;
	
	max = 0;
	for(i=0; i<p->num_path; i++){
		tmp = rGetMax(p->pathes[i]);
		if(max<tmp)	max = tmp;
	}
	
	//printf("%d : %d\n", p->e, max);//monitering
	
	return p->e + max;
}
int getMax(Graph *G){
	if(G->num <= 0)	return NOT_DEFINED_INT;
	else			return rGetMax(G->nodes + 0);
}
int main(){
	Graph X;
	int N, i, j;
	position p, pL, pR;
	
	scanf("%d", &N);
	if(init(&X, N*(N+1)/2)==NULL)	return -1;
	
	for(i=0; i<N; i++){
		for(j=0; j<i+1; j++){
			p = getPos(&X, i, j);
			pL = getPos(&X, i-1, j-1);
			pR = getPos(&X, i-1, j);
			
			scanf("%d", &(p->e));
			if(pL != NULL)	addPath(&X, pL, p);
			if(pR != NULL)	addPath(&X, pR, p);
			
			//print(&X);//monitering
		}
	}
	
	printf("%d", getMax(&X));
	
	return 0;
}
