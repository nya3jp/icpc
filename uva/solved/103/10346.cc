#include <iostream>

using namespace std;

int main() {
    int n, k;
    while(cin >> n >> k) {
        int s = 0;
        int r = 0;
        while(n > 0) {
            s += n;
            r += n;
            n = r/k;
            r -= n*k;
        }
        cout << s << endl;
    }
    return 0;
}
