#include <stdio.h>

int main() {
    //5kg짜리 봉지를 가장 많이 사용 하는것이, 가장 봉지를 적게 사용하는 방법이다.
	int num=0;
	int sugar;
	int i;
	scanf("%d",&sugar);

	//case : 설탕이 5의 배수 kg만큼 입력된 경우
    //맨처음 작성시에 작성한 코드이지만 이 부분을 뺀다고 해서
    //실행속도의 차이가 많이 나는것이 아니기 때문에 제외함
	/*if (sugar % 5 == 0) {
		printf("%d", sugar / 5);
		return 0;
	}*/
	//5kg짜리를 최대한 많이 가져가면 된다.
	i = sugar / 5;
	while(1) {

		//5키로짜리가 들어갈 수 없더라도 처리가 가능함
		if ((sugar - (5 * i)) % 3 == 0) {
			num += i;
			num += ((sugar - (5 * i)) / 3);
			break;
		}
		//-1이 출력하는 경우를 처리해 줘야함
		i--;
		if (i < 0) {
			num = -1;
			break;
		}

	}
	printf("%d", num);

	return 0;
}
