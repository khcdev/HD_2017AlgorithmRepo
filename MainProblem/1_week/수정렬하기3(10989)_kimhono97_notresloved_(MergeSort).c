#include <stdio.h>
#include <stdlib.h>

typedef int element;

void swap(element *x, element *y){
	element tmp;
	
	tmp = *x;
	*x = *y;
	*y = tmp;
}

element *Merge(element *A, element *B, int N, int M){
	element *X;
	int i, j, k;
	int size;
	
	size = N + M;
	X = (element *)malloc(size	* sizeof(element));
	if(X == NULL){
		printf("Failed malloc.\n");
		return NULL;
	}
	
	i = j = 0;
	for(k=0; k<M+N; k++){
		if(i < N && j < M){
			if(A[i] <= B[j]){
				X[k] = A[i];
				i++;
			}else{
				X[k] = B[j];
				j++;
			}
		}else if(i < N){
			X[k] = A[i];
			i++;
		}else{	/* j < M */
			X[k] = B[j];
			j++;
		}
	}
	
	return X;
}

void copy(element *X, element *Y, int size){
	int i;
	
	for(i=0; i<size; i++){
		X[i] = Y[i];
	}
}

void sort(element *X, int size){
	element *A, *B, *R;
	int N, M;
	
	
	// Dividing
	if(size == 1)	return;
	
	N = size/2;
	M = size - N;	// size == N + M
	A = X;
	B = X + N;
	
	sort(A, N);
	sort(B, M);
	
	
	// Merging
	R = Merge(A, B, N, M);
	copy(X, R, size);
	free(R);
}

int main() {
	element *X;
	int size, i;
	
	scanf("%d", &size);
	X = (element *)malloc(size * sizeof(element));
	if(X == NULL){
		printf("Failed malloc.\n");
		return -1;
	}
	
	for(i=0; i<size; i++){
		scanf("%d", X+i);
	}
	
	sort(X, size);
	
	for(i=0; i<size; i++){
		printf("%d\n", X[i]);
	}
	
	return 0;
}