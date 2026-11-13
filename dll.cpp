#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    int data ;
    node *next;
    node *prev;
    node(int val){
        data = val;
        next = prev= NULL;
    }
};
class Node{
    public:
    int data;
    Node *next;
    Node *prev;
    
    Node(int val){
        data=val;
        next=prev=NULL;
    }
};
Node *head=NULL;
Node *tail=NULL;
void createDLL(){
    int n;
    cout<<"Enter the number of node in your list:";
    cin>>n;
    for(int i=0;i<n;i++){
        cout<<"Enter the value of "<<i+1<<" position:";
        int val;
        cin>>val;
        Node *newNode=new Node(val);
        if(head==NULL){
            head=tail=newNode;
        }else{
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
    }
}

void Display(){
    Node *temp=head;
    if(head==NULL){
        cout<<"The list is empty:"<<endl;
        return;
    }
    cout<<"The node of the linked list:";
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
void insertAtTail(int val){
    Node *newNode=new Node(val);
    if(head==NULL){
        head=tail=newNode;
    }else{
        newNode->prev=tail;
        tail->next=newNode;
        tail=newNode;
    }
}

void deleteAtHead(){
    Node *temp=head;
    if(head==NULL){
        cout<<"The list is already empty"<<endl;
        return;
    }else if(head->next==NULL){
        head=tail=NULL;
    }else{
        head=head->next;
        head->prev=NULL;
    }
    delete temp;
}
int main(){
    createDLL();
    Display();
    insertAtTail(40);
    Display();
    // deleteAtHead();
    cout<<"DLL after deletion:";
    for(int i=0;i<5;i++){
        deleteAtHead();
        Display();
    }
}