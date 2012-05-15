#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

vector<pair<int, int> > tree;
vector<vector<int> > queries;
vector<int> targets;
unsigned long long int ret_count;

void
solve()
{
    vector<int> q;
    q.push_back(0);

    while(!q.empty()) {
        int cur = q.back();
        q.pop_back();
        if (cur >= 0) {
            ret_count += targets[cur];

            REP(i, queries[cur].size()) {
                targets[queries[cur][i]]++;
            }

            q.push_back(~cur);
            if (cur < tree.size()) {
                int firstChild = tree[cur].first;
                int lastChild = firstChild + tree[cur].second;

                for (int iChild = firstChild; iChild < lastChild; iChild++) {
                    q.push_back(iChild);
                }
            }
        } else {
            cur = ~cur;
            REP(i, queries[cur].size()) {
                targets[queries[cur][i]]--;
            }
        }        
    }
    cout << ret_count << endl;
}

int main(void)
{
    freopen("cells.in", "r", stdin);
    
    int nCases;
    cin >> nCases;
    while (nCases--) {
        tree.clear();
        queries.clear();
        targets.clear();
        ret_count = 0;
        
        int id = 1;
        int num;
        cin >> num;
        REP(i, num) {
            int n;
            cin >> n;
            tree.push_back(make_pair(id, n));
            id += n;
        }

        queries.resize(id);
        targets.assign(id, 0);
        int nQueries;
        cin >> nQueries;
        while (nQueries--) {
            int parent, child;
            cin >> parent >> child;
            queries[parent].push_back(child);
        }
        solve();
    }
}
