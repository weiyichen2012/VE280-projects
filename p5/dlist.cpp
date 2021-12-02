#include "dlist.h"
#include <iostream>
using namespace std;

int main(){
    Dlist<int> a;
    int c[5] = {1, 2, 3, 4, 5};
    a.insertFront(c + 0);
    a.insertFront(c + 1);
    a.insertBack(c + 2);
    a.insertBack(c + 3);
    Dlist<int> b(a);
    Dlist<int>cc, dd;
    cc = dd = b;
    while (!dd.isEmpty())
        cout << (*dd.removeBack()) << endl;
    cout << atoi("1kk");
}