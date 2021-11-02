#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <sstream>
using namespace std;
struct tree{
    int 
}
int main(){
    freopen("input", "w", stdout);
    struct timeb t1;
    ftime(&t1);
    srand((unsigned)(time(NULL) * 1000 + t1.millitm));
    int n = 10;

    fclose(stdout);
}