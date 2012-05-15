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
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int n;
        cin >> n;

        int a = n/2;
        int b = n-a;

        int res = a*(a-1)/2 + b*(b-1)/2;
        cout << res << endl;
    }

    return 0;
}

