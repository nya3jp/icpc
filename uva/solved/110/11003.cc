#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define INF 0x10000000

int main() {
    int n;
    cin >> n;
    if (n == 0)
        return 0;

    vector<int> weights(n), capacities(n);
    REP(i, n)
        cin >> weights[i] >> capacities[i];
    reverse(ALLOF(weights));
    reverse(ALLOF(capacities));

    vector< vector<int> > best(n+1, vector<int>(n+1, INF));
    best[0][0] = 0;
    for(int nSubset = 1; nSubset <= n; nSubset++) {
        int iBox = nSubset - 1;
        for(int nUses = 0; nUses <= n; nUses++) {
            int use_case = (nUses-1 >= 0 ? best[nSubset-1][nUses-1] : INF);
            if (use_case > capacities[iBox])
                use_case = INF;
            int dispose_case = best[nSubset-1][nUses];
            best[nSubset][nUses] = min(use_case+weights[iBox], dispose_case);
        }
    }

    int res = n;
    while(best[n][res] >= INF)
        res--;

    cout << res << endl;

    return main();
}
