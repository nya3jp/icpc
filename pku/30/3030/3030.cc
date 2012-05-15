#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    while(n-- > 0) {
        int r, e, c;
        cin >> r >> e >> c;
        int s = e - c;
        cout << (r == s ? "does not matter" : s > r ? "advertise" : "do not advertise") << endl;
    }
    return 0;
}
