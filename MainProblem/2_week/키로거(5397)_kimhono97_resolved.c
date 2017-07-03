#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct Node{
	struct Node *prev;
	struct Node *next;
	element e;
}Node;
typedef Node* position;
typedef struct List{
	position Header;
	position Cursor;
	position Trailer;
	int n;
}List;
typedef int Bool;
enum BOOL{ False, True };

position getNode(){
	position p;
	
	p = (position)malloc(1 * sizeof(Node));
	if(p == NULL){
		printf("Falied malloc.\n");
		return NULL;
	}
	
	return p;
}
void putNode(position p){
	if(p != NULL)	free(p);
}
void linkNode(position p, position q){
	if(p != NULL)	p->next = q;
	if(q != NULL)	q->prev = p;
}
List *init(List *L){
	L->Header = getNode();
	if(L->Header == NULL)	return NULL;
	
	L->Trailer = getNode();
	if(L->Trailer == NULL)	return NULL;
	
	linkNode(L->Header, L->Trailer);
	linkNode(NULL, L->Header);
	linkNode(L->Trailer, NULL);
	L->Cursor = L->Trailer;
	L->n = 0;
	
	return L;
}
void destruct(List *L){
	position p, next;
	
	p = L->Header;
	while(p){
		next = p->next;
		putNode(p);
		p = next;
	}
	
	L->n = 0;
}
Bool isEmpty(List *L){
	return (L->n == 0);
}
position insertBefore(List *L, position p, element e){
	position node;
	
	node = getNode();
	if(node == NULL)	return NULL;
	
	node->e = e;
	
	linkNode(p->prev, node);
	linkNode(node, p);
	
	L->n += 1;
	
	return node;
}
element removeNode(List *L, position p){
	element e;
	
	linkNode(p->prev, p->next);
	e = p->e;
	putNode(p);
	
	L->n -= 1;
	
	return e;
}

void keylogger(List *L){
	char ch;
	Bool loop;
	
	loop = True;
	while(loop){
		ch = getchar();
		switch(ch){
		case '\n':
			loop = False;
			break;
		case '<':
			if(L->Cursor->prev != L->Header){
				L->Cursor = L->Cursor->prev;
			}
			break;
		case '>':
			if(L->Cursor != L->Trailer){
				L->Cursor = L->Cursor->next;
			}
			break;
		case '-':
			if(L->Cursor->prev != L->Header){
				removeNode(L, L->Cursor->prev);
			}
			break;
		default:
			insertBefore(L, L->Cursor, ch);
			break;
		}
	}
}
void print(List *L){
	position p;
	
	p = L->Header->next;
	while(p != L->Trailer){
		printf("%c", p->e);
		p = p->next;
	}
	printf("\n");
}

int main() {
	List X;
	int N, i;
	
	scanf("%d", &N);
	getchar();
	for(i=0; i<N; i++){
		init(&X);
		keylogger(&X);
		print(&X);
		destruct(&X);
	}
	
	return 0;
}