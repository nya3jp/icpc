#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int next_combination(int p) {
    int lsb = p&-p;
    int rem = p+lsb;
    int rit = rem&~p;
    return rem|(((rit/lsb)>>1)-1);
}

bool isConnected(int p) {
    int cur = p&-p;
    for(;;) {
        int next = cur;
        next |= (cur&0x1EF7BDE) >> 1;
        next |= (cur&0xF7BDEF) << 1;
        next |= (cur&0xFFFFF) << 5;
        next |= (cur&0x1FFFFE0) >> 5;
        next &= p;
        if (next == p)
            return true;
        if (next == cur)
            return false;
        cur = next;
    }
}

int main() {

    int field = 0;
    REP(i, 5) {
        string s;
        cin >> s;
        REP(j, 5)
            if (s[j] == 'J')
                field |= 1<<(i*5+j);
    }

    int res = 0;

    for(int p = (1<<7)-1; p < (1<<25); p = next_combination(p)) {
        if (isConnected(p)) {
            int value = 0;
            REP(i, 25)
                if ((p&(1<<i)) != 0 && (field&(1<<i)) != 0)
                    value++;
            if (value >= 4)
                res++;
        }
    }

    cout << res << endl;

    return 0;
}
