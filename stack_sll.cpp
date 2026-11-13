#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(int val){
        data=val;
        next=NULL;
    }
};

Node *top=NULL;

void push(int value){
    Node *newNode=new Node(value);
    if(top==NULL){
        top=newNode;
        return;
    }
    newNode->next=top;
    top=newNode;
}

void pop(){
    if(top==NULL){
        cout<<"Stack underflow"<<endl;
        return;
    }
    Node *temp=top;
    cout<<"Popped element: "<<temp->data<<endl; 
    top=top->next;
    delete temp;
}

void peek(){
    if(top==NULL){
        cout<<"Stack is empty"<<endl;
        return;
    }
    cout<<"Top Element:"<<top->data<<endl;
}

int main()
{
    int i;
    for (int i = 0; i < 100; i++)
    {
        push(i);
    }
    for(int i=0;i<101;i++){
        pop();
    }
    // for (int i = 0; i < 6; i++)
    // {
    //     peek();
    //     pop();
    // }
}