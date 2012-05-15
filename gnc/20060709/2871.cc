#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    double prev;
    cin >> prev;
    for(double cur; cin >> cur; ) {
        if (cur == 999)
            break;
        double diff = cur - prev;
        printf("%.2f\n", diff);
        prev = cur;
    }
    cout << "End of Output" << endl;
    return 0;
}
