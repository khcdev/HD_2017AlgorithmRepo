#include <stdio.h>

int main() {
	int T;
	int **tri,**cpy; //원본 배열과 캐시 배열

	//결과 출력
	int max = -1;

	scanf("%d", &T);
	tri = (int**)malloc(sizeof(int*)*T);
	cpy = (int**)malloc(sizeof(int*)*T);

	for (int i = 0; i < T; i++) {
		tri[i] = (int*)malloc(sizeof(int)*T);
		cpy[i] = (int*)malloc(sizeof(int)*T);
		for (int j = 0; j <= i; j++) {
			scanf("%d", &tri[i][j]);
			cpy[i][j] = -1;
		}
	}
	//캐시 배열의 첫번째 원소에 원본배열 첫번째 원소 삽입
	cpy[0][0] = tri[0][0];

	//반복되는 연산을 지워주기 위한 작업
	for (int i = 0; i < T-1; i++) {
		for (int j = 0; j <= i; j++) {
			if (cpy[i + 1][j] < cpy[i][j] + tri[i + 1][j])
				cpy[i + 1][j] = cpy[i][j] + tri[i + 1][j];
			if (cpy[i + 1][j + 1] < cpy[i][j] + tri[i + 1][j + 1])
				cpy[i + 1][j + 1] = cpy[i][j] + tri[i + 1][j + 1];
		}
	}

	for (int i = 0; i < T; i++) {
		if (max < cpy[T-1][i]) max = cpy[T-1][i];
	}

	printf("%d", max);
	return 0;
}