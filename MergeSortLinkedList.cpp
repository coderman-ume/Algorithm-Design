#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

Node *merge(Node *left, Node *right) {
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;

    Node *result = nullptr;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

void splitList(Node *head, Node **left, Node **right) {
    if (head == nullptr || head->next == nullptr) {
        *left = head;
        *right = nullptr;
        return;
    }

    Node *slow = head;
    Node *fast = head->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

void mergeSortTopDown(Node **headRef) {
    Node *head = *headRef;
    Node *left;
    Node *right;

    if (head == nullptr || head->next == nullptr)
        return;

    splitList(head, &left, &right);

    mergeSortTopDown(&left);
    mergeSortTopDown(&right);

    *headRef = merge(left, right);
}

Node *mergeSortBottomUp(Node *head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    int listSize = 0;
    Node *current = head;

    while (current != nullptr) {
        listSize++;
        current = current->next;
    }

    Node *dummy = new Node(0);
    dummy->next = head;

    for (int blockSize = 1; blockSize < listSize; blockSize *= 2) {
        Node *prev = dummy;
        current = dummy->next;

        while (current != nullptr) {
            Node *left = current;
            Node *right;
            for (int i = 1; i < blockSize && current->next != nullptr; i++) {
                current = current->next;
            }
            right = current->next;
            current->next = nullptr;
            current = right;

            for (int i = 1; i < blockSize && current != nullptr && current->next != nullptr; i++) {
                current = current->next;
            }
            if (current != nullptr) {
                Node *temp = current->next;
                current->next = nullptr;
                current = temp;
            }

            prev->next = merge(left, right);
            while (prev->next != nullptr)
                prev = prev->next;
        }
    }

    head = dummy->next;
    delete dummy;

    return head;
}

void insertNode(Node **headRef, int value) {
    Node *newNode = new Node(value);
    newNode->next = *headRef;
    *headRef = newNode;
}

void printList(Node *head) {
    Node *current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node *headTopDown = nullptr;
    Node *headBottomUp = nullptr;

    insertNode(&headTopDown, 5);
    insertNode(&headTopDown, 2);
    insertNode(&headTopDown, 8);
    insertNode(&headTopDown, 1);
    insertNode(&headTopDown, 9);

    insertNode(&headBottomUp, 5);
    insertNode(&headBottomUp, 2);
    insertNode(&headBottomUp, 8);
    insertNode(&headBottomUp, 1);
    insertNode(&headBottomUp, 9);

    cout << "Original: ";
    printList(headTopDown);

    mergeSortTopDown(&headTopDown);
    cout << "Sorted (top-down): ";
    printList(headTopDown);

    headBottomUp = mergeSortBottomUp(headBottomUp);
    cout << "Sorted (bottom-up): ";
    printList(headBottomUp);

    return 0;
}