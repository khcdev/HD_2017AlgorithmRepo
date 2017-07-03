#include <stdio.h>

enum Toward{
	RIGHT, LEFT
};
void swap(int *X, int *Y){
	int tmp;
	tmp = *X;
	*X = *Y;
	*Y = tmp;
}
void sortArrayFast2(int *A, int N){
	// Quick Sort
	// O ( n * log n )
	
	int i, j, mode;
	
	// BASE CASE
	if(N == 1)	return;
	if(N == 2){
		if(A[0] > A[1])	swap(A+0, A+1);
		return;
	}
	
	i = 0; j = N-1;
	mode = RIGHT;
	while(1){
		switch(mode){
		case RIGHT:
			while(A[i] < A[j]){ j--; }
			break;
		case LEFT:
			while(A[i] > A[j]){ j++; }
			break;
		}
		if(i == j)	break;
		swap(A+i, A+j);
		swap(&i, &j);
		mode ? j-- : j++;
		mode = (mode+1)%2;
	}
	
	// RECURSION
	if(i != 0)		sortArrayFast2(A, i);
	if(i != N-1)	sortArrayFast2(A+i+1, N-1-i);
}
int main(){
	const int MAX_SIZE = 1000000;
	int data[MAX_SIZE];
	int N, i;
	
	scanf("%d", &N);
	for(i=0; i<N; i++){
		scanf("%d", data+i);
	}
	
	sortArrayFast2(data, N);
	
	for(i=0; i<N; i++){
		printf("%d\n", data[i]);
	}
    
    return 0;
}