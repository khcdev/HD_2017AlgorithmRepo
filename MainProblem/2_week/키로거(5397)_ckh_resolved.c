/* create by ckh 2017-05-10*/
/*
BOJ 5397 키로거
더블 링크드 리스트를 사용하여 문제 해결
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char a;
	struct node *NextNode;
	struct node *PrevNode;
}node;

//meaning List Head, Tail
node *Head = NULL;
node *Tail = NULL;
//meaning Cursor
node *pointing = NULL;

void insert( char inputdata);
void _remove();
void initlist();
void moveLeft();
void moveRight();
void printList();

int main() {
	int i, j, testcase;
	char **str;

	scanf("%d", &testcase);
	getchar();
	str = (char**)malloc(sizeof(char*)*testcase);
	for (i = 0; i < testcase; i++) {
		str[i] = (char*)malloc(sizeof(char) * 1000000);
		scanf("%s", str[i]);
	}

	for (i = 0; i < testcase; i++) {
		j = 0;
		initlist();
		while (str[i][j] != '\0') {
            switch(str[i][j]){
                case '<' :
                    moveLeft();
                    break;
                case '>' :
                    moveRight();
                    break;
                case '-' :
                    _remove();
                    break;
                default :
                    insert(str[i][j]);
            }
            j++;
		}
		printList();
		printf("\n");
	}
	// free memory
	for (i = 0; i < testcase; i++) {
		free(str[i]);
	}
	free(str);
	/*
	initlist();
	insert('a');
	moveLeft();
	insert('b');
	moveLeft();
	insert('c');
	moveLeft();
	insert('d');
	moveLeft();
	insert('e');
	initlist();*/
	return 0;
}

void insert( char inputdata) {
	node *newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->a = inputdata;
	newNode->NextNode = pointing->NextNode;
	pointing->NextNode->PrevNode = newNode;
	newNode->PrevNode = pointing;
	pointing->NextNode = newNode;
	pointing = pointing->NextNode;
	return;
}

void _remove() {
	node *tmp;
	if (pointing == Head) return;

	pointing->PrevNode->NextNode = pointing->NextNode;
	pointing->NextNode->PrevNode = pointing->PrevNode;
	tmp = pointing;
	pointing = pointing->PrevNode;
	free(tmp);
	return;
}

void initlist() {
	node *tmp;
	while (Head != NULL) {
		tmp = Head;
		Head = Head->NextNode;
		free(tmp);
	}

	Head = (node*)malloc(sizeof(node));
	Tail = (node*)malloc(sizeof(node));

	Head->PrevNode = NULL;
	Head->NextNode = Tail;
	Tail->PrevNode = Head;
	Tail->NextNode = NULL;

	pointing = Head;
	return;

}
void moveLeft() {
	if (pointing->PrevNode == NULL) return;
	pointing = pointing->PrevNode;
}
void moveRight() {
	if (pointing->NextNode == Tail) return;
	pointing = pointing->NextNode;
}

void printList() {
	node *pVisited;
	pVisited = Head->NextNode;
	while (pVisited != Tail) {
		printf("%c", pVisited->a);
		pVisited = pVisited->NextNode;
	}
}
