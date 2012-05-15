#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    for(int c = 0; c < n; c++) {
        int m;
        cin >> m;
        int r = 1;
        for(int i = 0; i < m; i++) {
            int t;
            cin >> t;
            r += (t-1);
        }
        cout << r << endl;
    }
    return 0;
}
