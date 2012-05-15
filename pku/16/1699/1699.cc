#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

const int INF = numeric_limits<int>::max();


struct Solver {
    int n;
    vector< vector<int> > adj;

    void solve() {

        cin >> n;
        adj.assign(n, vector<int>(n));

        vector<string> vs(n);
        for(int i = 0; i < n; i++)
            cin >> vs[i];

        for(int i = 0; i < n; i++) {
            string& s1 = vs[i];
            int len1 = s1.size();
            for(int j = 0; j < n; j++) {
                string& s2 = vs[j];
                int len2 = s2.size();
                int& pref = adj[i][j];
                for(pref = 0; pref < len1; pref++) {
                    int len = min(len1-pref, len2);
                    if (s1.substr(pref) == s2.substr(0, len))
                        break;
                }
            }
        }

        vector<int> perm(n);
        for(int i = 0; i < n; i++)
            perm[i] = i;

        int best = INF;
        do {
            int sum = 0;
            for(int i = 1; i < n; i++) {
                sum += adj[perm[i-1]][perm[i]];
                if (sum > best) {
                    sort(perm.begin()+i+1, perm.end(), greater<int>());
                    break;
                }
            }
            sum += vs[perm[n-1]].size();
            if (sum < best)
                best = sum;
        } while(next_permutation(perm.begin(), perm.end()));

        cout << best << endl;

    }
};

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0) {
        Solver s;
        s.solve();
    }
    return 0;
}
