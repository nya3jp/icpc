#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

int solve() {
    int n, k;
    scanf("%d%d", &n, &k);

    vector<int> v[100+1+1];

    for(int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        int s = min(a, b);
        int t = max(a, b)+1;
        v[s].push_back(s);
        v[t].push_back(-1);
    }
    for(int i = 0; i <= 100; i++) {
        sort(v[i].begin(), v[i].end(), greater<int>());
    }

    int ans = 0;
    vector<int> q;
    for(int i = 0; i <= 100; i++) {
        int dels = 0;
        for(int j = 0; j < (int)v[i].size(); j++) {
            int c = v[i][j];
            if (c < 0)
                dels++;
            else
                q.push_back(c);
        }
        sort(q.begin(), q.end(), greater<int>());
        q.resize((int)q.size() - dels);
        reverse(q.begin(), q.end());
        if ((int)q.size() > k) {
            int pops = (int)q.size() - k;
            for(int j = 0; j < pops; j++) {
                int t = q[k+j];
                v[t].pop_back();
            }
            q.resize((int)q.size() - pops);
            ans += pops;
        }
    }

    return ans;
}

int main() {
    int nCases;
    scanf("%d", &nCases);

    for(int iCase = 0; iCase < nCases; iCase++) {

        printf("%d\n", solve());

    }

    return 0;
}
