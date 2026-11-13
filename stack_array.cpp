#include <iostream>
using namespace std;

constexpr int MAX_SIZE = 5;
int stackArray[MAX_SIZE];
int top = -1;

void push(int value) {
    if (top == MAX_SIZE - 1) {
        cout << "Stack overflow" << endl;
        return;
    }

    stackArray[++top] = value;
}

void pop() {
    if (top == -1) {
        cout << "Stack underflow" << endl;
        return;
    }

    --top;
}

int peek() {
    return top == -1 ? -1 : stackArray[top];
}

void display() {
    if (top == -1) {
        cout << "Stack is empty" << endl;
        return;
    }
    for (int i = top; i >= 0; i--) {
        cout << stackArray[i] << " ";
    }
    cout << endl;
}

int main() {
    push(10);
    push(20);
    push(30);
    display();
    pop();
    display();
    return 0;
}
