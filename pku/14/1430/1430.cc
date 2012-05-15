#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int n, m;
        cin >> n >> m;
        n--; m--;
        cout << !((n-m)&(m>>1)) << endl;
    }
    return 0;
}
