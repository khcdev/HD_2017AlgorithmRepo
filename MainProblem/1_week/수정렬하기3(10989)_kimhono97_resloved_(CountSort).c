#include <stdio.h>
#define MAX_NUM 10000

int main() {
	int N, i, j, num;
	int cnts[MAX_NUM] = {0};
	
	scanf("%d", &N);
	for(i=0; i<N; i++){
		scanf("%d", &num);
		cnts[num-1]++;
	}
	for(i=0; i<MAX_NUM; i++){
		for(j=0; j<cnts[i]; j++){
			printf("%d\n", i+1);
		}
	}
	return 0;
}