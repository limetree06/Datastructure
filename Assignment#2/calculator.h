#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h"
#include <math.h>
using namespace std;

int orderpriority(char a){
    switch(a){
        case '(': return 0;
        case ')': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
    }
    return -1;
}

void inpost(char* infix, char *postfix){
    Stack<char> s;
    int wow = 0;
    int number =0;

    while(*infix != '\0'){
        if(*infix == '('){
            s.Push(*infix++);}


        else if( *infix == ')'){
            while(s.Top() != '('){
                    postfix[number++] = s.Top();
                    postfix[number++] = ' ';
                    s.Pop();}
                 *infix++;
                 s.Pop();
        }

        else if(*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/' ){
            if (wow == 0){
                postfix[number++] = *infix++;}


            else{
             wow = 0;
            while (!s.IsEmpty() && orderpriority(*infix) <= orderpriority(s.Top())){
                postfix[number++] = s.Top();
                postfix[number++] = ' ';
                s.Pop();
            }
            s.Push(*infix++);
        }}


        else if(*infix >= '0' && *infix <='9'){
                wow++;
                postfix[number++] = *infix++;
            while((*infix >= '0' && *infix <='9')|| *infix == '.'){
                postfix[number++] = *infix++;
            }
            postfix[number++] = ' ';
        }

        else *infix++;



            }

    while(!s.IsEmpty()){
        postfix[number++] = s.Top();
        postfix[number++] = ' ';
        s.Pop();
    }

    postfix[number] = '\0';
    }



double calculate(char* postfix){
    int i=0, j=1;;
    double val=0;
    double a, b;
    Stack<double> s;

    while(postfix[i] != '\0'){
        if (postfix[i] >= '0' && postfix[i]<= '9'){
        val = 0;
            do{ val = val * 10 + postfix[i] - '0';
                i++;
            } while (postfix[i] >= '0' && postfix[i] <= '9');

            if(postfix[i] == '.'&& postfix[i+1] >= '0' && postfix[i+1]<= '9'){
                i++; j=1;
                do { val = val + (postfix[i] - '0')/(double)pow(10,j);
                j++; i++;
                } while (postfix[i] >= '0' && postfix[i] <= '9');}

        s.Push(val);
        }


        else if (postfix[i] == '+'){
            a = s.Top();
            s.Pop();
            b = s.Top();
            s.Pop();
            s.Push(a+b);
            i++;}


        else if (postfix[i] == '*'){
            a = s.Top();
            s.Pop();
            b = s.Top();
            s.Pop();
            s.Push(a*b);
            i++;}


        else if (postfix[i] == '-'){
            if (postfix[i+1] >= '0' && postfix[i+1]<= '9'){
            i++; val = 0;
            do{ val = val * 10 + (postfix[i] - '0');
                i++;
            } while (postfix[i] >= '0' && postfix[i] <= '9');

                if(postfix[i] == '.'&& postfix[i+1] >= '0' && postfix[i+1]<= '9'){
                    j=1; i++;
                    do{
                    val = val + (postfix[i] - '0')/(double)pow(10,j);
                    j++; i++;
                    } while (postfix[i] >= '0' && postfix[i] <= '9');}
            s.Push(val*(-1));
            }

            else{
                a = s.Top();
                s.Pop();
                b = s.Top();
                s.Pop();
                s.Push(b-a);
                i++;}
        }

        else if (postfix[i] == '/'){
            a = s.Top();
            s.Pop();
            b = s.Top();
            s.Pop();
            s.Push(b/a);
            i++;
        }

        else i++;
}

    return s.Top();
    }

int buffersize(char* str){
    int i=0;
    while (str[i] != '\0'){ i++; }
    return 2*(i+1);
}

double Eval(char* str){
    char postfix[buffersize(str)];
    inpost(str, postfix);
    return calculate(postfix);
}




#endif
