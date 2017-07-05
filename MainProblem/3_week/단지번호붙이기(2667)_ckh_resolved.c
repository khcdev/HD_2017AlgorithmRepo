#include <stdio.h>

#define QMAXDATANUM 625
// 집의 위치를 다루기 위한 loc구조체
typedef struct loc {
	int x;
	int y;
}loc;

/* Circular Queue */
loc queue[QMAXDATANUM];
int inqQindex = 0;
int deqQindex = 0;
int inqueue(loc data);
loc dequeue();

int arrSize;
short int apartArr[26][26];
// 결과 배열, point-1는 최대 단지 수를 의미함
int result[625] = { 0, };
int point = 0;

void initGraphArr();
void search();

//BFS 탐색 알고리즘 사용
void BFS(loc startLocation);

// 대상이 되는 아파트를 방문 했으며, 위,오른쪽,아래,왼쪽 탐색하여 방문
void visitApart(loc indexNode);

//void printGraph();

void swap(int *a, int *b);
int main() {
	int i, j;

	//queue 초기화
	for (i = 0; i < QMAXDATANUM; i++) {
		queue[i].x = -1;
		queue[i].y = -1;
	}
	scanf("%d", &arrSize);

	initGraphArr();
	search();

	return 0;
}
/* for test
void printGraph() {
	int i, j;
	for (i = 0; i < arrSize; i++) {
		for (j = 0; j < arrSize; j++)printf("%d", apartArr[i][j]);
		printf("\n");
	}
}
*/
void initGraphArr() {
	int state,i,j;
	
	//state
	for (i = 0; i < arrSize; i++) {
		for (j = 0; j < arrSize; j++) {
			scanf("%1d", &state);
			apartArr[i][j] = state;
		}
	}
	
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void search() {
	int i, j;
	int apartBlock=0;
	loc startlocation;

	for (i = 0; i < arrSize; i++) {
		for (j = 0; j < arrSize; j++)
			if (apartArr[i][j] == 1) {
				apartBlock++;
				startlocation.y = i;
				startlocation.x = j;
				BFS(startlocation);
				point++;
			}
	}
	printf("%d\n", point);

	for (i = point; i >-1; i--) {
		for (j = 1; j < i; j++) {
			if (result[j - 1] > result[j]) swap(&result[j - 1], &result[j]);
		}
	}
	for (i = 0; i < point; i++) printf("%d\n", result[i]);
}

void BFS(loc Location) {
	int i, j;
	apartArr[Location.y][Location.x] = 0;
	inqueue(Location);
	result[point]++;
	Location = dequeue();
	while (Location.x != -1) {
		visitApart(Location);
		Location = dequeue();
	}
	
}

int validNode(int y, int x) {
	if ((x > -1 && x < arrSize) && (y > -1 && y < arrSize)) {
		if (apartArr[y][x] == 1) return 1;
	}
	return 0;
}

void visitApart(loc indexNode) {
	loc data;
	int i = indexNode.y;
	int j = indexNode.x;
	if (validNode(i - 1, j)) {
		apartArr[i - 1][j] = 0;
		data.y = i - 1;
		data.x = j;
		result[point]++;
		inqueue(data);
	}
	if (validNode(i, j + 1)) {
		apartArr[i][j + 1] = 0;
		data.y = i;
		data.x = j + 1;
		result[point]++;
		inqueue(data);
	}
	if (validNode(i + 1, j)) {
		apartArr[i + 1][j] = 0;
		data.y = i + 1;
		data.x = j;
		result[point]++;
		inqueue(data);
	}
	if (validNode(i, j - 1)) {
		apartArr[i][j - 1] = 0;
		data.y = i;
		data.x = j - 1;
		result[point]++;
		inqueue(data);
	}
}

int inqueue(loc data) {
	if (queue[inqQindex].x == -1) {
		queue[inqQindex] = data;
		inqQindex++;
		if (inqQindex == QMAXDATANUM) inqQindex = inqQindex - QMAXDATANUM;
		return 1;
	}
	else return -1;
}

loc dequeue() {
	loc data;
	if (queue[deqQindex].x != -1) {
		data = queue[deqQindex];
		queue[deqQindex].x = -1;
		queue[deqQindex].y = -1;
		deqQindex++;
		if (deqQindex == QMAXDATANUM) deqQindex = deqQindex - QMAXDATANUM;
		return data;
	}
	else { // empty queue
		data.x = -1;
		data.y = -1;
		return data;
	}
}