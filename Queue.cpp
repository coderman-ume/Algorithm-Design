#include <stdio.h>
#include <stdlib.h>

typedef int Ele;

struct Node {
	Ele data;
	struct Node* Next;
};

typedef struct Node* LinkedList;

struct Queue {
	LinkedList head;
	LinkedList tail;
};

typedef struct Queue QueueList;

void init(QueueList* q) {
	q->head = q->tail = (LinkedList)malloc(sizeof(struct Node));
	if (q->head == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}
	q->head->Next = NULL;
}

void push(QueueList* q, Ele e) {
	LinkedList p;
	p = (LinkedList)malloc(sizeof(struct Node));
	if (p == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}
	p->Next = NULL;
	p->data = e;
	q->tail->Next = p;
	q->tail = p;
}

void pop(QueueList* q, Ele* e) {
	LinkedList p;
	if (q->head == q->tail) {
		printf("Queue is empty");
		exit(1);
	}
	p = q->head->Next;
	q->head->Next = p->Next;
	*e = p->data;
	if (q->tail == p) {
		q->tail = q->head;
	}
	free(p);
}

void release(QueueList* q) {
	LinkedList p;
	p = q->head;
	while (p) {
		q->head = q->head->Next;
		free(p);
		p = q->head;
	}
}

int main() {
	QueueList q;
	int num, i;
	Ele e;
	init(&q);
	printf("Enter number of elements: ");
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		scanf("%d", &e);
		push(&q, e);
	}
	for (i = 0; i < num; i++) {
		pop(&q, &e);
		printf("%d\n", e);
	}
	return 0;
}