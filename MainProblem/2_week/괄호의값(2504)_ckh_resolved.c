/* create by ckh 2017-05-10*/
/*
BOJ 2504 괄호의 값
스택 ADT가 엄밀하지 않고, 코드가 지저분하여 수정 예정
*/

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
	int num;
	char data;
	struct node *nextNode;
}node;

void ch_push(node *Head, char data);
void int_push(node *Head, int num);
node *pop(node *Head);
int size(node *Head);
int isEmpty(node *Head);
void clear(node *Head);
char top(node *Head);
int isMatched(char a, char b);

int main() {
	int i = 0;
	int depth=0;
	int a, b;
	char ch;
	char str[33];
	char popdata;
	int bFlag = 1;
	node *n_tmp;
	node *strStack = NULL;
	node *exprStack = NULL;

	scanf("%s", str);

	if (str[0] == ']' || str[0] == ')') {
		printf("0");
		clear(strStack);
		return 0;
	}
	strStack = (node*)malloc(sizeof(node));
	strStack->nextNode = NULL;
	exprStack = (node*)malloc(sizeof(node));
	exprStack->nextNode = NULL;

	while (str[i] != '\0') {
		// 열린 괄호의 경우
		if (str[i] == '(' || str[i] == '[') {
			//닫혔다가 열린경우 -> +연산자
			if (i > 0 && (str[i - 1] == ']' || str[i - 1] == ')')) {
				depth--;
				ch_push(exprStack, '+');
			}
			ch_push(strStack, str[i]);
			depth++;		//depth 유지
			if (str[i] == '(') int_push(exprStack, 2);
			if (str[i] == '[') int_push(exprStack, 3);
			ch_push(exprStack, '*');
		}
		// 닫힌 괄호의 경우
		else {
			//이전 문자가 열린 문자인 경우 -> 정수만들기
			if (str[i - 1] == '(' || str[i - 1] == '[') {
				// 열린문자와 닫히는 문자 매칭이 안되는 경우
				if (isMatched(top(strStack), str[i]) == FALSE) {
					printf("0");
					clear(strStack);
					clear(exprStack);
					return 0;
				}
				free(pop(strStack));
				free(pop(exprStack));


			}
			// 이전 문자가 닫힌 문자인 경우
			else if (str[i - 1] == ')' || str[i - 1] == ']') {
				if (isMatched(top(strStack), str[i]) == FALSE) {
					printf("0");
					clear(strStack);
					clear(exprStack);
					return 0;
				}
				free(pop(strStack));
				if (depth > 0) {
					while (bFlag) {
						n_tmp = pop(exprStack);
						a = n_tmp->num;
						free(n_tmp);
						n_tmp = pop(exprStack);
						ch = n_tmp->data;
						free(n_tmp);
						n_tmp = pop(exprStack);
						b = n_tmp->num;
						free(n_tmp);

						switch (ch) {
						case '*':
							int_push(exprStack, a*b);
							depth--;
							bFlag = 0;
							break;
						case '+':
							int_push(exprStack, a + b);
							break;
						}
					}
					bFlag = 1;
				}
				else {	//depth ==0인 경우
					while (size(exprStack) > 2) {
						n_tmp = pop(exprStack);
						a = n_tmp->num;
						free(n_tmp);
						n_tmp = pop(exprStack);
						ch = n_tmp->data;
						free(n_tmp);
						n_tmp = pop(exprStack);
						b = n_tmp->num;
						free(n_tmp);

						switch (ch) {
						case '*':
							int_push(exprStack, a*b);
							break;
						case '+':
							int_push(exprStack, a + b);
							break;
						}
					}
				}
			}
		}
		i++;
	}
	if (size(strStack) > 0) {
		clear(strStack);
		clear(exprStack);
		printf("0");
		return 0;
	}
	while (size(exprStack) > 2) {
		n_tmp = pop(exprStack);
		a = n_tmp->num;
		free(n_tmp);
		n_tmp = pop(exprStack);
		ch = n_tmp->data;
		free(n_tmp);
		n_tmp = pop(exprStack);
		b = n_tmp->num;
		free(n_tmp);

		switch (ch) {
		case '*':
			int_push(exprStack, a*b);
			break;
		case '+':
			int_push(exprStack, a + b);
			break;
		}
	}
	printf("%d\n", pop(exprStack)->num);
	clear(strStack);
	clear(exprStack);
	return 0;
}


void ch_push(node *Head, char data) {

	node *newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	newNode->nextNode = Head->nextNode;
	Head->nextNode = newNode;
}
void int_push(node *Head, int num) {

	node *newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->num = num;
	newNode->nextNode = Head->nextNode;
	Head->nextNode = newNode;
}
node *pop(node *Head) {
	if (Head->nextNode == NULL) return (node*)malloc(sizeof(node));

	char data = Head->nextNode->data;
	node *delNode = Head->nextNode;
	Head->nextNode = Head->nextNode->nextNode;
	delNode->nextNode = NULL;
	return delNode;
}
int size(node *Head) {
	int numNode = 0;
	node *temp = Head;
	while (temp->nextNode != NULL) {
		numNode++;
		temp = temp->nextNode;
	}
	return numNode;
}
int isEmpty(node *Head) {
	if (top(Head) != 'n') return 0;
	else return 1;
}
void clear(node *Head) {
	node *temp;
	while (Head != NULL) {
		temp = Head;
		Head = Head->nextNode;
		free(temp);
	}
}
char top(node *Head) {
	if (Head->nextNode == NULL) return 'n';
	return Head->nextNode->data;
}
int isMatched(char a, char b) {
	if (a + 1 == b || a + 2 == b) return TRUE;
	else return FALSE;
}
