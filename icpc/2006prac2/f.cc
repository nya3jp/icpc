#include <iostream>
#include <fstream>
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

#define REP(i,n) for(int i = 0 ; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

#define N 2000
char s[N];
int v[N][N];

int main() {
    ifstream cin("F.txt");

    string ss;
    while(cin >> ss) {
        int n = ss.size();
        copy(ss.begin(), ss.end(), s);
        REP(i, n)
            v[i][0] = 0;
        REP(i, n)
            v[i][1] = 1;
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i+len <= n; i++) {
                if (s[i] == s[i+len-1])
                    v[i][len] = v[i+1][len-2] + 2;
                else
                    v[i][len] = (v[i][len-1] >? v[i+1][len-1]);
                //cout << string(s+i, s+i+len) << ": " << v[i][len] << endl;
            }
        }
        int i = 0;
        int len = n;
        vector<char> left, right;
        while(len > 0) {
            //cout << string(s+i, s+i+len) << endl;
            if (v[i][len] == v[i+1][len-1]) {
                i++;
                len--;
            }
            else if (v[i][len] == v[i][len-1]) {
                len--;
            }
            else {
                if (len == 1) {
                    left.push_back(s[i]);
                }
                else {
                    left.push_back(s[i]);
                    right.push_back(s[i]);
                }
                i++;
                len-=2;
            }
        }
        cout << string(left.begin(), left.end()) + string(right.rbegin(), right.rend()) << endl;
    }

    return 0;
}

// Powered by Fate Testarossa
