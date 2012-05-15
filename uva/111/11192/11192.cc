#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


string periodic_reverse(string str, int nPeriods) {
    int period = str.size() / nPeriods;

    REP(i, nPeriods) {
        REP(j, period/2) {
            swap(str[i*period+j], str[i*period+period-1-j]);
        }
    }

    return str;
}

int main() {

    for(;;) {

        int nPeriods;
        string str;
        cin >> nPeriods >> str;

        if (nPeriods == 0)
            break;

        cout << periodic_reverse(str, nPeriods) << endl;

    }

    return 0;
}

