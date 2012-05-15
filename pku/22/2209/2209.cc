#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int p;
    cin >> p;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int t = 1;
        for(int j = 0; j < p; j++)
            t *= a;
        if (t > 0)
            res += t;
    }
    cout << res << endl;
    return 0;
}
