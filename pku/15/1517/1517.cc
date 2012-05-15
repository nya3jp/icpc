#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    cout << "n e" << endl << "- -----------" << endl;
    double e = 0, f = 1;
    for(int i = 0; i < 10; i++) {
        e += f;
        f /= i+1;
        cout << i << " " << setprecision(10) << e << endl;
    }
    return 0;
}
