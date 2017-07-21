#include <stdio.h>

unsigned long long kkongFib(int a);
unsigned long long cache[70] = {0,};
int main() {
	int Testcase,n;
	cache[0] = 1;
	cache[1] = 1;
	cache[2] = 2;
	cache[3] = 4;
	scanf("%d", &Testcase);
	for (int i = 0; i < Testcase; i++) {
		scanf("%d", &n);
		printf("%lld\n", kkongFib(n));
	};
	
	return 0;
}

unsigned long long kkongFib(int a) {
	long long int t1 = cache[a - 1], t2 = cache[a - 2], t3 = cache[a - 3], t4 = cache[a - 4];

	if (a < 2) return 1;
	if (a == 2) return 2;
	if (a == 3)return 4;
	
	if (t1 == 0) {
		t1 = kkongFib(a - 1);
		cache[a - 1] = t1;
	}
	if (t2 == 0) {
		t2 = kkongFib(a - 2);
		cache[a - 2] = t2;
	}
	if (t3 == 0) {
		t3 = kkongFib(a - 3);
		cache[a - 3] = t3;
	}
	if (t4 == 0) {
		t4 = kkongFib(a - 4);
		cache[a - 4] = t4;
	}
	cache[a] = t1 + t2 + t3 + t4;
	return cache[a];

}

