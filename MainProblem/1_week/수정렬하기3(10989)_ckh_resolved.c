#include <stdio.h>
#include <stdlib.h>

#define Max_range 10001

int main() {
	int Testcase,tmp;
	int a[Max_range] = { 0, };
	int arraymax=0;
	int i,j;
	scanf("%d", &Testcase);

	for (i = 0; i < Testcase; i++) {
		scanf("%d", &tmp);
		a[tmp]++;
		if (tmp > arraymax) arraymax = tmp;
	}
	for (i = 0; i < arraymax+1; i++) {
		if (a[i] != 0) {
			for (j = 0; j < a[i]; j++) printf("%d\n", i);
		}
	}

	return 0;
}
