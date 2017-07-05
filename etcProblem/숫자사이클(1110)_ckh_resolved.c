#include <stdio.h>
/*
ex) 26 = 2+6=8 
next Number: 68 => 6+8 = 14
next Number: 84 ...

규칙 찾기
*/
int main() {
	int Data, result=0;
	int firstNumber, cnt = 0;
	int i = 1;
	scanf("%d", &firstNumber);
	Data = firstNumber;
	while (1) {
		result += Data / 10;
		result += Data % 10;
		if (result < 10) {
			Data = (Data % 10 * 10) + result;
		}
		else {
			Data=(Data % 10 * 10)+(result % 10);
		}
		cnt++;
		if (firstNumber == Data) break;
		result = 0;
	}
	printf("%d", cnt);
	return 0;

}
