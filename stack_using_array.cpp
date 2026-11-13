#include<bits/stdc++.h>
using namespace std;

#define MAX 5
int top=-1;
int ARR[MAX];

void push(int val){
    if(top==MAX-1){
        cout<<"Stack overflow"<<endl;
        return;
    }
    top++;
    ARR[top]=val;
}
void pop(){
    if(top==-1){
        cout<<"Stack Underflow"<<endl;
        return;
    }
    cout<<"Popped Element: "<<ARR[top]<<endl;
    top--;
}

void peek(){
    if(top==-1){
        cout<<"Stack is empty"<<endl;
        return;
    }
    cout<<"Top element: "<<ARR[top];
}
int main(){
    int i;
    for(int i=0;i<6;i++){
        push(i);
    }
    // for(int i=0;i<6;i++){
    //     pop();
    // }
    for (int i = 0; i < 6; i++)
    {
        peek();
        pop();
    }
}