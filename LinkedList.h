#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include <iostream>
using namespace std;

class Node{
private:
    Node* next;
    int data;
    template<class Type> friend class LinkedList;

    };

template <class Type>
class LinkedList{
        private:
            int length;
            Node* first;

        public:
            LinkedList(){
                this->length = 0;
                this->first = NULL; }

            Type Get(const int index);
            void AddAtHead(const Type& val);
            void AddAtIndex(const int index, const Type& val);
            void DeleteAtIndex(const int index);
            void DeleteValue(const Type& val);
            void MoveToHead(const Type& val);
            void Rotate(const int steps);
            void Reduce();
            void Swap();
            int Size();
            void CleanUp();
            void Print();
            ~LinkedList(){CleanUp();}
};

template <class Type>
Type LinkedList<Type>::Get(const int index){
    int counter=0;
    Node* p = first;
    if(this->length != 0){
    if(index == 0){return first -> data;}
    else if( index <0 || index >= this-> length){return -1;}
    else {
        while(index != (counter)){
            counter++;
            p = p -> next;
        }
        return p->data;
    }}
}


template <class Type>
void LinkedList<Type>::AddAtHead(const Type& val){
    Node* node = new Node();
    node -> data = val;
    node -> next = this -> first;
    first = node;
    this -> length++;
}


template <class Type>
void LinkedList<Type>::AddAtIndex(const int index, const Type& val){
    int counter=1;
    Node* node = new Node();
    Node* help =first;
    if(index==0) { AddAtHead(val);}
    else if(index > 0 && index <= this-> length) {
        this->length++;
        while(index != counter){
            counter++;
            help = help -> next;}
            node -> next = help->next;
            help -> next = node;
            node -> data = val;}
    else{while(1) break;}}


template <class Type>
void LinkedList<Type>::DeleteAtIndex(const int index){
    Node* x = first;
    Node *y = first;
    if(index==0){
        this -> length--;
        first = x -> next;
        delete x;}
    else if(index > 0 && index < this-> length){
        this -> length--;
        for(int i=1; i < index; i++) {y = y -> next;}
            y -> next =  y -> next -> next;
            delete y;}
   else{while(1) break; }
}


template <class Type>
void LinkedList<Type>::DeleteValue(const Type& val){
    int number = this -> length;
    for(int i=0; i < number; i++){
        if (Get(i) == val){
            DeleteAtIndex(i);
            break;}
}}


template <class Type>
void LinkedList<Type>::MoveToHead(const Type& val){
    if ( this-> length > 0 ){
        DeleteValue(val);
        AddAtHead(val);}

    else{while(1) break;}
}



template <class Type>
void LinkedList<Type>::Rotate(const int steps){
     if ( this-> length > 0 ){
        if(steps <0 ){while(1) break;}
        else{
            for(int i=0; i< steps; i++){
                int vaule = Get(this->length-1);
                DeleteAtIndex(this->length-1);
                AddAtHead(vaule);
    }}}}


template <class Type>
void LinkedList<Type>::Reduce(){
    int check;
    for(int i=0; i< this->length; i++){
            check = Get(i);
            for(int j=i+1; j< this->length; j++){
                if(check == Get(j)){DeleteAtIndex(j);}
            }
}}



template <class Type>
void LinkedList<Type>::Swap(){
    int swwap;
    int number = this -> length;
        for(int i=0; i <(number/2); i++){
            swwap = Get(2*i);
            DeleteAtIndex(2*i);
            AddAtIndex(2*i+1 ,swwap);
        }
    }


template <class Type>
int LinkedList<Type>::Size(){ return this->length; }

template <class Type>
void LinkedList<Type>::CleanUp(){
        int number = this -> length;
        for (int i=0; i < number; i++){DeleteAtIndex(0);}
}


template <class Type>
void LinkedList<Type>::Print(){
    int number = this -> length;
    if(this -> length == 0) { cout << "()" << endl; }
    else {cout <<"(";
        for (int i=0; i < (number-1); i++){
            cout << Get(i) <<",";}
            cout << Get(number-1);
            cout << ")"<<endl;;
}}

#endif // LINKLIST_H_INCLUDED
