#include <iostream>

using namespace std;

typedef long long int integer;

int main() {

    integer Vtotal, V0;
    while(cin >> Vtotal >> V0 && !(Vtotal == 0 && V0 == 0)) {

        integer best = -1;
        integer res;

        for(integer n = 0; n*V0 <= Vtotal; n++) {

            integer eval = n * Vtotal - n * n * V0;
            if (eval > best) {
                best = eval;
                res = n;
            }
            else if (eval == best) {
                res = 0;
            }

        }

        cout << res << endl;

    }
    return 0;
}
