#include "dlist.h"
#include <iostream>
using namespace std;
class _calc{
    Dlist<int> dlist;
    void processPlus(){

    }

    void processMinus(){

    }

    void processMultiply(){

    }

    void processDivid(){

    }

    void processNegate(){

    }

    void processDuplicate(){

    }

    void processReverse(){

    }

    void processPrint(){

    }

    void processClear(){

    }

    void processPrintAll(){

    }
public:
    _calc(){

    }
    void process(string input){
        if (input.length() == 1){
            if ('0' < input[0] && input[0] < '9'){
                int num = input[0] - '0';
                dlist.insertFront(&num);
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
            int num = 0;
            for (int i = 0; i < input.length(); ++i){
                if ('0' < input[i] && input[i] < '9')
                    num = num * 10 + input[i] - '0';
                else{
                    cout << "Bad input\n";
                    return;
                }
            }
            dlist.insertFront(&num);
        }
    }
}calc;

int main(){

}