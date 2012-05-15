#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> before(n);
    REP(i, n)
        cin >> before[i];
    vector<string> after(n);
    REP(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        after[b] = before[a];
        before[a].clear();
    }

    REP(i, n) {
        if (!before[i].empty()) {
            REP(j, n) {
                if (after[j].empty()) {
                    after[j] = before[i];
                    break;
                }
            }
        }
    }
    cout << after[0];
    for(int i = 1; i < n; i++)
        cout << ' ' << after[i];
    cout << endl;
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
