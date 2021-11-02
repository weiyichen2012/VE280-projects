#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

int main() {
    list_t listA, listB, listEmpty;

    listA = list_make();
    listB = list_make();
    listEmpty = list_make();

    for(int i = 0; i < 5; i ++) {
        listA = list_make(5 - i, listA); // (1 2 3 4 5)
        listB = list_make(i + 1, listB); // (5 4 3 2 1)
    }

    cout << "A: ";
    list_print(listA);
    cout << '\n' << "B: ";
    list_print(listB);
    cout << "\n\n";

    cout << "size(A): " << size(listA) << '\n' << "size(E): " << size(listEmpty) << "\n\n";

    cout << "sum(A): " << sum(listA) << '\n' << "sum(E): " << sum(listEmpty) << "\n\n";

    cout << "product(A): " << product(listA) << '\n' << "product(E): " << product(listEmpty) << "\n\n";

    cout << "reverse(A): ";
    list_print(reverse(listA));
    cout << "\nreverse(E): ";
    list_print(reverse(listEmpty));
    cout << "\n\n";

    cout << "append(A, B): ";
    list_print(append(listA, listB));
    cout << "\nappend(A, E): ";
    list_print(append(listA, listEmpty));
    cout << "\nappend(E, A): ";
    list_print(append(listEmpty, listA));
    cout << "\nappend(E, E): ";
    list_print(append(listEmpty, listEmpty));
    cout << "\n\n";

    cout << "filter_odd(A): ";
    list_print(filter_odd(listA));
    cout << "\nfilter_odd(B): ";
    list_print(filter_odd(listB));
    cout << "\nfilter_odd(E): ";
    list_print(filter_odd(listEmpty));
    cout << "\n\n";

    cout << "filter_even(A): ";
    list_print(filter_even(listA));
    cout << "\nfilter_even(E): ";
    list_print(filter_even(listEmpty));
    cout << "\n\n";

    cout << "insert_list(A, B, 2): ";
    list_print(insert_list(listA, listB, 2));
    cout << "\ninsert_list(A, E, 2): ";
    list_print(insert_list(listA, listEmpty, 2));
    cout << "\ninsert_list(E, A, 0): ";
    list_print(insert_list(listEmpty, listA, 0));
    cout << "\ninsert_list(E, E, 0): ";
    list_print(insert_list(listEmpty, listEmpty, 0));
    cout << "\n\n";

    cout << "chop(A, 2): ";
    list_print(chop(listA, 2));
    cout << "\nchop(A, 5): ";
    list_print(chop(listA, 5));
    cout << "\nchop(E, 0): ";
    list_print(chop(listEmpty, 0));
    cout << "\n\n";


    return 0;
}
