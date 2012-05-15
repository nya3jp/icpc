#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(), (c).end()

int main() {

    int n;
    while(cin >> n && n > 0) {
        vector<int> v(n);
        REP(i, n)
            cin >> v[i];

        {
            set<int> u(ALL(v));
            if (u.size() < n) {
                cout << "No solution" << endl;
                continue;
            }
        }

        vector<int> res;
        for(int m = 0; m < n; m++) {
            for(int i = n - 2; i >= m; i--) {
                if (v[i] > v[i+1]) {
                    swap(v[i], v[i+1]);
                    res.push_back(i+1);
                }
            }
        }

        cout << res.size();
        REP(i, res.size())
            cout << ' ' << res[i];
        cout << endl;

    }

    return 0;
}
