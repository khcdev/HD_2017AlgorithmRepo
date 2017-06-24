#include <stdio.h>

#define QMAXDATANUM 1000000

//노드의 상태, 토마토가 익은 날짜 등의 데이터를 갖는 구조체
typedef struct node {
	int state;
	int date;
}node;
//queue에 넣기 위한 node의 위치를 저장하는 구조체
typedef struct loc {
	int x;
	int y;
}loc;

//토마토 상태 저장하는 배열
node arrTomato[1001][1001];
int max_X, max_Y;
//익지 않은 토마토가 몇개있는지 판단하기 위한 변수
int numZero = 0;
//Queue ADT
loc queue[QMAXDATANUM];
int inqQindex = 0;
int deqQindex = 0;
int inqueue(loc data);
loc dequeue();

//최소 일수
int numberOfDay = 0;
// 그래프 입력부
void initGraphArr();

//BFS 탐색 알고리즘
void BFS();

//노드 유효성 검사
int validNode(int x, int y);

//인접 노드 방문
void visitNextDay(int prevDate, loc indxeNode);
int main() {
	int i;
	//Queue init
	for (i = 0; i < QMAXDATANUM; i++) {
		queue[i].x = -1;
		queue[i].y = -1;
	}

	initGraphArr();
	//더이상 익을 것이 없는경우
	if (numZero == 0) {
		printf("0");
		return 0;
	}
	BFS();

	//익을수 없는것이 있는 경우
	if (numZero > 0) printf("-1");
	// 정답
	else printf("%d", numberOfDay);
	return 0;
}

void initGraphArr() {
	int i, j;
	int state;
	scanf("%d%d", &max_X, &max_Y);
	//state
	for (i = 0; i < max_Y; i++) {
		for (j = 0; j < max_X; j++) {
			scanf("%d", &state);
			if (state == 0) numZero++;
			arrTomato[i][j].state = state;
			arrTomato[i][j].date = 0;
		}
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

int validNode(int y, int x) {
	//노드의 위치가 유효한 범위에 있는지 그리고 그것의 상태가 0인지(익지 않았는지) 판단
	if ((x > -1 && x < max_X) && (y > -1 && y < max_Y)) {
		if (arrTomato[y][x].state == 0) return 1;
	}
	return 0;
}

void BFS() {
	int i, j;
	loc data;
    //데이터 입력시에 익은 토마토(1)을 찾아 q에 집어 넣는다. 이미 익은 토마토 들 이기 때문에 state 변경은 일어나지 않는다.
	for (i = 0; i < max_Y; i++) {
		for (j = 0; j < max_X; j++) {
			if (arrTomato[i][j].state == 1) {
				data.x = j;
				data.y = i;
				inqueue(data);
			}
		}
	}
	data = dequeue();
	while (data.x != -1) {
		//printf("deq data confirm : %d %d\n", data.y, data.x)
        //다음날에 익게 될 토마토들을 찾아 inqueue 하는 함수, dequeue된 노드의 날짜를 전해준다.
		visitNextDay(arrTomato[data.y][data.x].date, data);
		data = dequeue();
	}
}


void visitNextDay(int prevDate, loc indexNode) {
	loc data;
	int i = indexNode.y;
	int j = indexNode.x;
	if (validNode(i - 1, j)) {
		arrTomato[i - 1][j].state = 1;
		arrTomato[i - 1][j].date = prevDate + 1;
		if (numberOfDay < prevDate + 1) numberOfDay = prevDate + 1;
		data.y = i - 1;
		data.x = j;
		numZero--;
		//printf("방문 : %d,%d\n", data.y, data.x);
		inqueue(data);
	}
	if (validNode(i, j + 1)) {
		arrTomato[i][j + 1].state = 1;
		arrTomato[i][j + 1].date = prevDate + 1;
		if (numberOfDay < prevDate + 1) numberOfDay = prevDate + 1;
		data.y = i;
		data.x = j + 1;
		numZero--;
		//printf("방문 : %d,%d\n", data.y, data.x);
		inqueue(data);
	}
	if (validNode(i + 1, j)) {
		arrTomato[i + 1][j].state = 1;
		arrTomato[i + 1][j].date = prevDate + 1;
		if (numberOfDay < prevDate + 1) numberOfDay = prevDate + 1;
		data.y = i + 1;
		data.x = j;
		numZero--;
		//printf("방문 : %d,%d\n", data.y, data.x);
		inqueue(data);
	}
	if (validNode(i, j - 1)) {
		arrTomato[i][j - 1].state = 1;
		arrTomato[i][j - 1].date = prevDate + 1;
		if (numberOfDay < prevDate + 1) numberOfDay = prevDate + 1;
		data.y = i;
		data.x = j - 1;
		numZero--;
		//printf("방문 : %d,%d\n", data.y, data.x);
		inqueue(data);
	}
}
