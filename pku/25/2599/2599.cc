#include <iostream>
#include <vector>

using namespace std;


int solve(vector< vector<int> >& g, int cur, int prev) {

    vector<int>& v = g[cur];
    for(int i = 0; i < (int)v.size(); i++) {
        int next = v[i];
        if (next != prev) {
            if (solve(g, next, cur) < 0)
                return next;
        }
    }

    return -1;
}


int main() {
    int n, s;
    cin >> n >> s;
    s--;
    vector< vector<int> > g(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    int res = solve(g, s, -1);
    if (res < 0) {
        cout << "First player loses" << endl;
    }
    else {
        cout << "First player wins flying to airport " << res+1 << endl;
    }

    return 0;
}
