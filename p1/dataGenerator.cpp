#include <iostream>
using namespace std;
int main(){
    freopen("input", "w", stdout);
    int number = 2, integer;
    if (rand()%10 == 0){
        cout << rand() % 100 + 1 << " " << 2 << endl;
        return 0;
    }
    while (!(0 < number && number < 5 && 0 < integer && integer <(int)(1e7))){
        // number = rand() % 20;
        integer = rand() % ((int)(4 *1e7)) - (int)(1e7);
        cout << integer << " " << number << endl;
    }
    return 0;
}