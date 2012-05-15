#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define DBG 0

int amsize;
int am[120][26];
int amac[120];
long long int memo[26][120][1<<10];

long long int search(int len, int s, int rem) {
    if (len == 0)
        return (rem == 0 ? 1 : 0);
    long long int& res = memo[len][s][rem];
    if (res < 0) {
        res = 0;
        REP(a, 26) {
            int t = am[s][a];
            res += search(len-1, t, rem&~amac[t]);
        }
    }
    return res;
}

void display(int len, int s, int rem, string& str) {
    if (search(len, s, rem) == 0)
        return;
    if (len == 0) {
        cout << str << endl;
    }
    else {
        REP(a, 26) {
            int t = am[s][a];
            str.push_back((char)('a' + a));
            display(len-1, t, rem&~amac[t], str);
            str.erase(str.size()-1);
        }
    }
}

int main() {

    FILE* fp = freopen("password.in", "r", stdin);
    assert(fp);

    int iCase = 0;
    for(;;) {

        int len, n;
        cin >> len >> n;
        if (len == 0)
            break;

        printf("Case %d: ", ++iCase);

        vector<string> words(n);
        REP(i, n)
            cin >> words[i];

        map<string,int> ammap;
        vector<string> amstr;
        ammap[""] = 0;
        amstr.push_back("");
        REP(i, n) {
            string w = words[i];
            int k = w.size();
            for(int i = 1; i <= k; i++) {
                string s = w.substr(0, i);
                if (ammap.count(s) == 0) {
                    ammap.insert(make_pair(s, ammap.size()));
                    amstr.push_back(s);
                }
            }
        }
        amsize = ammap.size();
        memset(am, 0, sizeof(am));
        memset(amac, 0, sizeof(amac));
        REP(i, amsize) {
            string s = amstr[i];
            REP(j, n) {
                string w = words[j];
                if (s.size() >= w.size() && s.substr(s.size()-w.size()) == w)
                    amac[i] |= 1 << j;
            }
            REP(a, 26) {
                string t = s + string(1, 'a'+a);
                while(ammap.count(t) == 0)
                    t.erase(t.begin());
                am[i][a] = ammap[t];
            }
        }

        memset(memo, -1, sizeof(memo));
        long long int res = search(len, 0, (1<<n)-1);
        printf("%lld suspects\n", res);
        if (res <= 42) {
            string str;
            display(len, 0, (1<<n)-1, str);
        }

    }

    return 0;
}
