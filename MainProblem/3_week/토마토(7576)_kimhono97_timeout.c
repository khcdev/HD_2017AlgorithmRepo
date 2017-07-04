#include <stdio.h>
#include <stdlib.h>

typedef int Bool;
enum BOOL{
	False, True
};

typedef struct Status{
	int now;
	Bool isNext;
}Status;
enum STATUS{
	EMPTY = -1,
	UNRIPE = 0, 
	RIPE = 1
};


Status **setting(int M, int N, int *cntUNRIPE){
	Status **T;
	int i, j;
	
	T = (Status **)malloc(N * sizeof(Status *));
	if(T == NULL)		return NULL;
	
	*cntUNRIPE = 0;
	for(i=0; i<N; i++){
		T[i] = (Status *)malloc(M * sizeof(Status));
		if(T[i] == NULL){
			for(j=0; j<i; j++)	free(T[j]);
			free(T);
			return NULL;
		}
		
		for(j=0; j<M; j++){
			scanf("%d", &T[i][j].now);
			T[i][j].isNext = False;
			if(T[i][j].now == UNRIPE)	(*cntUNRIPE)++;
		}
	}
	
	return T;
}

int check(Status **T, int M, int N){
	int cntCHANGE;
	int i, j;
	Bool tmp;
	
	cntCHANGE = 0;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			if(T[i][j].now == UNRIPE){
				tmp = False;
				tmp = tmp || ( i!=0 && T[i-1][j].now==RIPE );
				tmp = tmp || ( i!=N-1 && T[i+1][j].now==RIPE );
				tmp = tmp || ( j!=0 && T[i][j-1].now==RIPE );
				tmp = tmp || ( j!=M-1 && T[i][j+1].now==RIPE );
				if(tmp)	cntCHANGE++;
				T[i][j].isNext = tmp;
			}
		}
	}
	
	return cntCHANGE;
} 

void apply(Status **T, int M, int N, int *cntUNRIPE){
	int i, j;
	
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			if(T[i][j].isNext){
				T[i][j].now = RIPE;
				(*cntUNRIPE)--;
				T[i][j].isNext = False;
			}
		}
	}
}

/*
void print(Status **T, int M, int N, int cntUNRIPE){//monitering
	int i, j, all;
	char ch;
	
	all = M*N;
	printf("\n====================\n");
	printf("- UNRIPE: %d/%d\n\n", cntUNRIPE, all);
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			switch(T[i][j].now){
				case EMPTY:		ch = 'E'; break;
				case UNRIPE:	ch = 'U'; break;
				case RIPE:		ch = 'R'; break;
				default:		ch = 'x';
			}
			printf(" %c", ch);
		}
		printf("\n");
	}
	printf("\n====================\n");
}
*/

int main() {
	Status **Tomatos;
	int M, N;
	int i, j, day, cntUNRIPE;
	Bool flag;
	
	
	/* ----- 1. 초기화 및 입력 ----- */
	scanf("%d %d", &M, &N);
	Tomatos = setting(M, N, &cntUNRIPE);
	if(Tomatos == NULL){
		printf("Failed malloc.\n");
		return -1;
	}
	
	
	/* ----- 2. 시뮬레이션 ----- */  
	day = 0;
	flag = True;
	while(cntUNRIPE && flag){
		if(check(Tomatos, M, N) == 0)	flag = False;
		if(flag)						apply(Tomatos, M, N, &cntUNRIPE);
		//print(Tomatos, M, N, cntUNRIPE);//monitering
		day++;
	}
	
	/* ----- 3. 결과출력 ----- */
	printf("%d\n", cntUNRIPE ? -1 : day);
	
	
	/* ----- 4. 마무으리 ----- */
	for(i=0; i<N; i++)	free(Tomatos[i]);
	free(Tomatos);
	
	return 0;
}
