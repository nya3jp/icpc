#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)


typedef vector<string> Edges;
typedef map<string, Edges> Graph;

void dfs(Graph& g, string here, map<string,int>& counts, vector<string>& trace, int depth) {
    trace.push_back(here);
    int m = trace.size();
    if (m-1-depth >= 0)
        counts[trace[m-1-depth]]++;
    Edges& v = g[here];
    FOR(it, v)
        dfs(g, *it, counts, trace, depth);
    trace.pop_back();
}

void solve(Graph& g, int depth) {

    set<string> roots;
    FOR(it, g)
        roots.insert(it->first);
    FOR(it, g) FOR(jt, it->second)
        roots.erase(*jt);

    map<string, int> counts;

    FOR(it, roots) {
        string root = *it;
        vector<string> trace;
        dfs(g, root, counts, trace, depth);
    }

    vector< pair<int, string> > res;

    FOR(it, g) {
        string here = it->first;
        if (counts[here] > 0) {
            res.push_back(make_pair(-counts[here], here));
        }
    }

    sort(ALLOF(res));

    int last = -1;
    REP(i, res.size()) {
        string name = res[i].second;
        int c = counts[name];
        if (i < 3 || c == last) {
            cout << name << " " << c << endl;
            last = c;
        }
    }

}


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int n, depth;
        cin >> n >> depth;

        Graph g;

        REP(i, n) {
            string parent;
            int nEdges;
            cin >> parent >> nEdges;
            REP(j, nEdges) {
                string child;
                cin >> child;
                g[parent].push_back(child);
            }
        }

        if (iCase > 0)
            cout << endl;
        cout << "Tree " << (iCase+1) << ":" << endl;

        solve(g, depth);

    }

    return 0;
}




