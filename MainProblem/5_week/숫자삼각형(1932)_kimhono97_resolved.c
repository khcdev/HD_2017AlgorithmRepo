#include <stdio.h>
#include <stdlib.h>

#define NOT_DEFINED_INT -999999

#define ERR_FM "Failed malloc.\n"

int getMax(int x, int y){
	return x>y ? x : y;
}
int main(){
	int N, i, j;
	int **arr;
	
	scanf("%d", &N);
	arr = (int **)malloc(N * sizeof(int *));
	if(arr == NULL){
		printf(ERR_FM);
		return -1;
	}
	for(i=0; i<N; i++){
		arr[i] = (int *)malloc(N * sizeof(int));
		if(arr[i]==NULL){
			printf(ERR_FM);
			for(j=0; j<i; j++){
				free(arr[j]);
			}
			free(arr);
			return -1;
		}
		for(j=0; j<i+1; j++){
			scanf("%d", &arr[i][j]);
		}
		for(; j<N; j++){
			arr[i][j] = NOT_DEFINED_INT;
		}
	}
	
	for(i=N-1; i>0; i--){
		for(j=0; j<i; j++){
			arr[i][j] = getMax(arr[i][j], arr[i][j+1]);
		}
		for(j=0; j<i; j++){
			arr[i-1][j] += arr[i][j];
		}
	}
	
	printf("%d\n", arr[0][0]);
	
	for(i=0; i<N; i++)	free(arr[i]);
	free(arr);
	return 0;
}
