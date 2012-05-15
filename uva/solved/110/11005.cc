#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)




void solve() {
    int costs[36];
    REP(i, 36)
        cin >> costs[i];
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int given;
        cin >> given;
        int evals[36+1] = {0x7fffffff, 0x7fffffff};
        for(int base = 2; base <= 36; base++) {
            int& e = evals[base];
            e = 0;
            int t = given;
            while(t > 0) {
                int d = t % base;
                e += costs[d];
                t /= base;
            }
        }
        int best = *min_element(evals, evals+36+1);
        cout << "Cheapest base(s) for number " << given << ":";
        REP(base, 36+1)
            if (evals[base] == best)
                cout << ' ' << base;
        cout << endl;
    }
}


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        if (iCase > 0)
            cout << endl;
        cout << "Case " << iCase+1 << ":" << endl;
        solve();
    }

    return 0;
}


