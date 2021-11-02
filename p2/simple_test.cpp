#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

int add(int a, int b){
    return a + b;
}

bool ifFour(int a){
    return (a % 4 == 0);
}

int main()
{
    int i;
    list_t listA, listA_answer;
    list_t listB, listB_answer;
    list_t listC;

    listA = list_make();
    listB = list_make();
    listC = list_make();
    listA_answer = list_make();
    listB_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listA_answer = list_make(6-i, listA_answer);
        listB = list_make(i+10, listB);
        listB_answer = list_make(i+10, listB_answer);
    }

    for(i = 5; i>0; i--)
    {
        listB_answer = list_make(i, listB_answer);
    }

    list_print(listA);
    list_print(listB);
    cout << endl;

    cout << size(listA) << endl;
    cout << size(listC) << endl;

    cout << sum(listA) << endl;
    cout << sum(listC) << endl;

    cout << product(listA) << endl;
    cout << product(listC) << endl;

    cout << accumulate(listA, add, 0) << endl;
    cout << accumulate(listC, add, 1) << endl;

    list_print(reverse(listA));
    list_print(reverse(listC));

    list_print(append(listA, listB));
    list_print(append(listA, listC));

    list_print(filter_odd(listA));

    list_print(filter_even(listA));

    list_print(filter(listA, ifFour));

    list_print(insert_list(listA, listA, 2));

    list_print(chop(listA, 2));

    list_print(listB);
    cout << endl;

    listB = append(listA, listB);
    listA = reverse(listA);
    list_print(listA);
    cout << endl;
    list_print(listB);
    cout << endl;

    if(list_equal(listA, listA_answer) 
        && list_equal(listB, listB_answer))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
    // return 0;
}
