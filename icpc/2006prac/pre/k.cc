#include <iostream>

using namespace std;

int main() {
    int k;
    while(cin >> k && k != 0) {
        cout << (k*k + 2*k - 5) << endl;
    }
    return 0;
}

