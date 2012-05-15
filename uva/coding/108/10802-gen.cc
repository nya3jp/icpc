#include <iostream>

using namespace std;

int main() {
    int n = 100;
    cout << 1 << endl;
    cout << n << ' ' << n*(n+1)/2 << ' ' << 0 << endl;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            cout << i << ' ' << j << endl;
        }
    }
    return 0;
}
