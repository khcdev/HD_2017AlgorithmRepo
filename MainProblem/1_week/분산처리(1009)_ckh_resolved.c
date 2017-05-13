#include <stdio.h>

int main()
{
	int t, i,k,j, A[10000] = { 0, }, B[10000]={0,};
	scanf("%d", &t);
	for (i = 0; i < t; i++)
	{
		scanf("%d%d", &A[i], &B[i]); //a,b값 저장
	}
	for (i = 0; i < t; i++)
	{
		k = A[i];
		for (j = 1; j < B[i]; j++)
		{
			A[i] = A[i] * k % 10;
		}
		if (A[i] == 0) printf("10\n");
		else printf("%d\n", A[i]);
	}
	return 0;
}
