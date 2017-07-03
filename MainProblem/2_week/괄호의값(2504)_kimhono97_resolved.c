#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30
#define NOT_DEFINED -1
typedef int element;
typedef int position;
typedef struct Stack{
	element buffer[MAX_SIZE];
	position top;
	int size;
	int capacity;
}Stack;
typedef int Bool;
enum BOOL{ False, True };

void init(Stack *S){
	S->top = NOT_DEFINED;
	S->size = 0;
	S->capacity = MAX_SIZE;
}
Bool isEmpty(Stack *S){
	return (S->size == 0);
}
Bool isFull(Stack *S){
	return (S->size == S->capacity);
}
void push(Stack *S, element e){
	if(isFull(S)){
		printf("Stack is already Full.\n");
		return;
	}
	
	S->top += 1;
	S->buffer[S->top] = e;
	S->size += 1;
}
element pop(Stack *S){
	element e;
	
	if(isEmpty(S)){
		printf("Stack is already Empty.\n");
		return NOT_DEFINED;
	}
	
	e = S->buffer[S->top];
	S->top -= 1;
	S->size -= 1;
	
	return e;
}
element top(Stack *S){
	if(isEmpty(S)){
		printf("Stack is Empty.\n");
		return NOT_DEFINED;
	}
	
	return S->buffer[S->top];
}


int main(){
	element ch, sum;
	Bool loop;
	Stack X;
	
	init(&X);
	loop = True;
	while(loop && (ch = getchar()) != EOF){
		switch(ch){
		case '\n':
			loop = False;
			break;
		case '(': case '[':
			push(&X, ch);
			break;
		case ')':
			sum = 0;
			while(top(&X) != '('){
				if(top(&X) == '['){
					printf("0\n");
					return 1;
				}
				sum += pop(&X);
			}
			pop(&X);
			push(&X, ((!sum)+sum)*2);
			break;
		case ']':
			sum = 0;
			while(top(&X) != '['){
				if(top(&X) == '('){
					printf("0\n");
					return 1;
				}
				sum += pop(&X);
			}
			pop(&X);
			push(&X, ((!sum)+sum)*3);
			break;
		}
	}
	
	sum = 0;
	while(!isEmpty(&X)){
		ch = pop(&X);
		if(ch == '[' || ch == '('){
			printf("0\n");
			return 1;
		}
		sum += ch;
	}
	printf("%d\n", sum);
	return 0;
}