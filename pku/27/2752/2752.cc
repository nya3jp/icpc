#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

char buf[400000+1024];

void solve(const char* s) {
    int n = strlen(s);

    int* kmp = new int[n+1];

    int q = kmp[0] = -1;
    for(int p = 1; p <= n; p++) {
        while(q >= 0 && s[q] != s[p-1])
            q = kmp[q];
        kmp[p] = ++q;
    }

    vector<int> res;
    for(int p = n; p > 0; p = kmp[p])
        res.push_back(p);

    reverse(res.begin(), res.end());

    cout << res[0];
    for(int i = 1; i < (int)res.size(); i++)
        cout << " " << res[i];
    cout << endl;

    delete[] kmp;
}

int main() {

    while(gets(buf))
        solve(buf);

    return 0;
}
