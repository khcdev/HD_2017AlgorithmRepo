#include <stdio.h>
#include <stdlib.h>

typedef struct status{
	int prev;
	int now;
	int next;
}Status;
enum STATUS{
	RIPE = 1,
	UNRIPE = 0,
	EMPTY = -1
};
typedef int Bool;
enum BOOL{ False, True };

Bool infection(Status **boxes, int N, int M){
	int i, j;
	Bool flag;
	
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			boxes[i][j].next = boxes[i][j].now;
		}
	}
	
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(boxes[i][j].now == RIPE){
				//printf("%d %d\n", i, j);//monitering
				if(i > 0 && boxes[i-1][j].now == UNRIPE)	{ boxes[i-1][j].next = RIPE; /*printf("U\n");*/ }
				if(i < M-1 && boxes[i+1][j].now == UNRIPE)	{ boxes[i+1][j].next = RIPE; /*printf("D\n");*/ }
				if(j > 0 && boxes[i][j-1].now == UNRIPE)	{ boxes[i][j-1].next = RIPE; /*printf("L\n");*/ }
				if(j < N-1 && boxes[i][j+1].now == UNRIPE)	{ boxes[i][j+1].next = RIPE; /*printf("R\n");*/ }
			}
		}
	}
	
	flag = False;
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			boxes[i][j].prev = boxes[i][j].now;
			boxes[i][j].now = boxes[i][j].next;
			if(boxes[i][j].prev != boxes[i][j].now)	flag = True;
		}
	}
	
	return flag;
}

Bool isThereUnripe(Status **boxes, int N, int M){
	int i, j;
	
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			if(boxes[i][j].now == UNRIPE)	return True;
		}
	}
	
	return False;
}

void printStatus(Status **boxes, int N, int M){//monitering
	int i, j;
	
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			printf(" %d", boxes[i][j].now);
		}
		printf("\n");
	}
}

int main(){
	int N, M, i, j, x, day, cnt_Unripe;
	Status **boxes;
	Status X;
	Bool isChanged;
	
	
	cnt_Unripe = 0;
	
	scanf("%d %d", &N, &M);
	boxes = (Status **)malloc(M * sizeof(Status *));
	for(i=0; i<M; i++){
		boxes[i] = (Status *)malloc(N * sizeof(Status));
		for(j=0; j<N; j++){
			scanf("%d", &x);
			boxes[i][j].now = x;
			if(x == UNRIPE)		cnt_Unripe++;
		}
	}
	
	day = 0;
	while(cnt_Unripe){
		isChanged = infection(boxes, N, M);
		if(!isChanged)	break;
		day++;
		//printf("\nDay %d : \n", day);//monitering
		//printStatus(boxes, N, M);//monitering
	}
	
	if(isThereUnripe(boxes, N, M))	printf("-1\n");
	else							printf("%d\n", day);
	
	for(i=0; i<M; i++){
		if(boxes[i] != NULL)	free(boxes[i]);
	}
	free(boxes);
	return 0;
}