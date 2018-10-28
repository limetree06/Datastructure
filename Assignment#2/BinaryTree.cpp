#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <math.h>
using namespace std;


class Node {
public:
    int data;
    Node *LeftChild, *RightChild;
};

int valsearch(int arr[], int first, int last, int val){
    int i;
    for (i = first; i <= last; i++) {
        if (arr[i] == val) break;}
    return i;
}

Node* newNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->LeftChild = node->RightChild = NULL;
    return node;
}


Node* buildUtil(int in[], int post[], int first, int last, int* index){

    if (first > last) return NULL;

    Node* node = newNode(post[*index]);
    (*index)--;

    if (first == last) return node;

    int wowindex = valsearch(in, first, last, node->data);

    node->RightChild = buildUtil(in, post, wowindex + 1, last, index);
    node->LeftChild = buildUtil(in, post, first, wowindex - 1, index);

    return node;
}


Node* Visit(Node* node){
    return node ;
}

void LevelOrder(Node* root, int a, int size1){
    int level[a];
    int i=0, wow=0;
    queue<Node*> q;
    Node *CurrentNode = root;
    level[i++] = root -> data;

    while(CurrentNode) {
        Visit(CurrentNode);
            if (CurrentNode->LeftChild){
                q.push(CurrentNode->LeftChild);
                 level[i++] = CurrentNode->LeftChild->data;}

            else level[i++] = NULL;

            if (CurrentNode->RightChild){
                q.push(CurrentNode->RightChild);
                level[i++] = CurrentNode->RightChild->data;}

            else level[i++] = NULL;

            if(q.empty()) break;

            CurrentNode = q.front();
            q.pop(); }

            cout << "[" ;
            for(int i=0; i < a; i++){
                if(level[i] == NULL) cout << "null";
                else {cout << level[i]; wow++;}

                if (wow == size1) break;
                else cout <<",";
            }
            cout << "]";
            }



int main()
{
    string str1, str2;
    int size1, i=0;

    cin >> str1;
    cin >> str2;

    size1=str1.length();

    int in[size1], post[size1];

    char *inarr = new char[size1 + 1];
    strcpy(inarr, str1.c_str());

    char *posarr = new char[size1 + 1];
    strcpy(posarr, str2.c_str());

    while ( *inarr != '\0'){
        if( *inarr == '-' ){
                *inarr++;
                in[i] = (-1)*(*inarr - '0');
                inarr++;
            while (*inarr >= '0' && *inarr <='9'){
                in[i] = in[i]*10 - (*inarr - '0');
                *inarr++;}}

        else if (*inarr>= '0' && *inarr<='9'){
            in[i] = *inarr - '0';
            *inarr++;
            while (*inarr>= '0' && *inarr<='9'){
                in[i] = in[i]*10 + (*inarr - '0');
                *inarr++;}
             }

        else {i++; *inarr++;}
            }
    i=0;

    while ( *posarr != '\0'){
        if( *posarr == '-' ){
                *posarr++;
                post[i] = (-1)*(*posarr - '0');
                *posarr++;
            while (*posarr >= '0' && *posarr <='9'){
                post[i] = post[i]*10 - (*posarr - '0');
                *posarr++;}}

        else if (*posarr>= '0' && *posarr<='9'){
            post[i] = *posarr - '0';
            *posarr++;
            while (*posarr>= '0' && *posarr<='9'){
                post[i] = post[i]*10 + (*posarr - '0');
                *posarr++;} }

        else {i++; *posarr++;}}

    size1 = i+1;
    int index = size1 - 1;
    int num = size1;
    int a = 0;
    while (num > 1){
        num= num/2;
        a++;}
    a=pow(2,a+1);

    Node* root = buildUtil(in, post, 0, size1 - 1 , &index);

    LevelOrder(root,a, size1);

  return 0;
}




