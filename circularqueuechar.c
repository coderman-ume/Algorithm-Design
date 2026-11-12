#include <stdio.h>

#define MAX 5

char queue[MAX];
int front = 0;
int rear = -1;
int count = 0;

int isFull(void)
{
    return count == MAX;
}

int isEmpty(void)
{
    return count == 0;
}

void insertElement(char item)
{
    rear = (rear + 1) % MAX;
    queue[rear] = item;
    count++;
}

char deleteElement(void)
{
    char item = queue[front];
    front = (front + 1) % MAX;
    count--;
    return item;
}

void handleInsert(void)
{
    char item;

    if (isFull()) {
        printf("Queue overflow: the queue is full.\n");
        return;
    }

    printf("Enter a character to insert: ");
    if (scanf(" %c", &item) != 1) {
        fprintf(stderr, "Error: could not read a character.\n");
        return;
    }

    insertElement(item);
    printf("Inserted '%c'.\n", item);
}

void handleDelete(void)
{
    char item;

    if (isEmpty()) {
        printf("Queue underflow: the queue is empty.\n");
        return;
    }

    item = deleteElement();
    printf("Deleted '%c'.\n", item);
}

int main(void)
{
    int choice;

    while (1) {
        printf("\n1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Error: invalid input. Exiting.\n");
            return 1;
        }

        switch (choice) {
        case 1:
            handleInsert();
            break;
        case 2:
            handleDelete();
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice. Please enter 1, 2 or 3.\n");
            break;
        }
    }
}
