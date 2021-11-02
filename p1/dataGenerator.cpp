#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <sstream>
using namespace std;
int main(){
    freopen("input", "w", stdout);
    struct timeb t1;
    ftime(&t1);
    srand((unsigned)(time(NULL) * 1000 + t1.millitm));
    // cout <<"!"<< endl;
    int number = -1, integer = -1;
    if (rand()%10 == 0){
        cout << rand() % 100 + 1 << " " << rand() % 4 + 1 << endl;
        return 0;
    }
    while (!(0 < number && number < 5 && 0 < integer && integer <(int)(1e7))){
        number = rand() % 10 - 5;
        integer = rand() % ((int)(4 *1e7)) - (int)(1e7);
        cout << integer << " " << number << endl;
    }
    return 0;
}