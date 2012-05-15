#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main() {
    srand(time(0));

    for(int i = 0; i < 100; i++) {
        int a = rand()&0xffff;
        int b = rand()&0xffff;
        int c = rand()&0xffff;
        int d = 16;
        cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
    }

    cout << "0 0 0 0" << endl;

    return 0;
}


