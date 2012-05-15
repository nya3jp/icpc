#include <iostream>
using namespace std;
int main() {
    int m = -1;
    for(int t; cin >> t && t > 0; m = max(m, t));
    cout << m << endl;
    return 0;
}

