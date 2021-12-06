#include "dlist.h"
#include <iostream>
using namespace std;
class _calc{
    Dlist<int> dlist;

    bool ifOperand(int n){
        Dlist<int> tmp(this->dlist);
        for (int i = 0; i < n - 1; ++i)
            tmp.removeFront();
        if (tmp.isEmpty()){
            cout << "Not enough operands\n";
            return false;
        }
        else
            return true;

    }

    void processMath(char op){
        if (!ifOperand(2))
            return;
        int* a = dlist.removeFront(), *b = dlist.removeFront(), *c = new int;
        switch (op){
            case '+':
                *c = *a + *b;
                break;
            
            case '-':
                *c = *a - *b;
                break;

            case '*':
                *c = *a * *b;
                break;

            case '/':
                *c = *a / *b;
                break;
        }
        delete a;
        delete b;
        dlist.insertFront(c);
    }

    void processPlus(){
        processMath('+');
    }

    void processMinus(){
        processMath('-');
    }

    void processMultiply(){
        processMath('*');
    }

    void processDivid(){
        processMath('/');
    }

    void processNegate(){
        if (!ifOperand(1))
            return;
        int* a = dlist.removeFront(), *c = new int(-*a);
        delete a;
        dlist.insertFront(c);
    }

    void processDuplicate(){
        if (!ifOperand(1))
            return;
        int* a = dlist.removeFront(), *c1 = new int(*a), *c2 = new int (*a);
        delete a;
        dlist.insertFront(c1);
        dlist.insertFront(c2);
    }

    void processReverse(){
        if (!ifOperand(2))
            return;
        int* a = dlist.removeFront(), *b = dlist.removeFront();
        dlist.insertFront(a);
        dlist.insertFront(b);
    }

    void processPrint(){
        if (!ifOperand(1))
            return;
        int* a= dlist.removeFront();
        cout << *a << endl;
        dlist.insertFront(a);
    }

    void processClear(){
        while (!dlist.isEmpty()){
            int* tmp = dlist.removeFront();
            delete tmp;
        }
    }

    void processPrintAll(){
        Dlist<int> tmp(this->dlist);
        while (!tmp.isEmpty()){
            cout << (*tmp.removeFront()) << ' ';
        }
        cout << endl;
    }
public:
    _calc(){

    }

    ~_calc(){
        while (!dlist.isEmpty()){
            int* tmp = dlist.removeFront();
            delete tmp;
        }
    }

    void process(string input){
        if (input.length() == 1){
            if ('0' <= input[0] && input[0] <= '9'){
                int* num = new int(input[0] - '0');
                dlist.insertFront(num);
            }
            else{
                switch(input[0]){
                    case '+':
                        processPlus();
                        break;
                    
                    case '-':
                        processMinus();
                        break;
                    
                    case '*':
                        processMultiply();
                        break;
                    
                    case '/':
                        processDivid();
                        break;

                    case 'n':
                        processNegate();
                        break;
                    
                    case 'd':
                        processDuplicate();
                        break;
                    
                    case 'r':
                        processReverse();
                        break;
                    
                    case 'p':
                        processPrint();
                        break;
                    
                    case 'c':
                        processClear();
                        break;

                    case 'a':
                        processPrintAll();
                        break;

                    default:
                        cout << "Bad input\n";
                        break;
                }
            }
        }
        else{
            int* num = new int(0);
            for (int i = 0; i < input.length(); ++i){
                if ('0' <= input[i] && input[i] <= '9')
                    *num = *num * 10 + input[i] - '0';
                else{
                    cout << "Bad input\n";
                    return;
                }
            }
            dlist.insertFront(num);
        }
    }
};

int main(){
    string input;
    _calc calc;
    while (cin >> input){
        if (input == "q")
            break;
        calc.process(input);
    }
}