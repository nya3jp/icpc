// encoded by UTF-8

/*
 *
 * 2002 Japan Regional in Kanazawa
 * Problem G - True Liars
 * by nya
 *
 * DFSによるグループわけ + グループをマージした集団の大きさに関するDP
 * 計算量は O(Q + n^2) (Q:質問数, n:合計人数)
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct Edge {
    int src, dest, type;
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

const vector<int> AMBIGUOUS(1, -1);

void dfs(Graph& g, int here, int type, vector<int>& types) {
    if (types[here] != 0)
        return;
    //cout << "dfs(" << here+1 << " = " << type << ")" << endl;
    types[here] = type;

    Edges& v = g[here];
    REP(i, v.size()) {
        Edge& e = v[i];
        dfs(g, e.dest, type*e.type, types);
    }
}

vector<int> solve(Graph& g, int nDivines) {

    int n = g.size();

    vector<int> types(n, 0);
    int nTypes = 0;
    REP(i, n)
        if (types[i] == 0)
            dfs(g, i, ++nTypes, types);

    vector< vector< vector<int> > > groups(nTypes, vector< vector<int> >(2));

    REP(i, n) {
        int type = types[i];
        int side = (type < 0 ? 1 : 0);
        if (type < 0)
            type = -type;
        type--;
        groups[type][side].push_back(i);
    }

    /*
    REP(i, nTypes) {
        REP(j, groups[i][0].size())
            cout << groups[i][0][j]+1 << " ";
        cout << "| ";
        REP(j, groups[i][1].size())
            cout << groups[i][1][j]+1 << " ";
        cout << endl;
    }
    //*/

    vector< vector<int> > dp(nTypes+1, vector<int>(nDivines+1, -1));

    dp[0][0] = 0;

    REP(type, nTypes) REP(i, nDivines+1) {
        if (dp[type][i] >= 0) {
            int n0 = groups[type][0].size();
            int n1 = groups[type][1].size();
            if (i+n0 <= nDivines) {
                if (dp[type][i] == 2 || dp[type+1][i+n0] >= 0)
                    dp[type+1][i+n0] = 2;
                else
                    dp[type+1][i+n0] = 0;
            }
            if (i+n1 <= nDivines) {
                if (dp[type][i] == 2 || dp[type+1][i+n1] >= 0)
                    dp[type+1][i+n1] = 2;
                else
                    dp[type+1][i+n1] = 1;
            }
        }
    }

    assert(dp[nTypes][nDivines] >= 0); // should be consistent

    if (dp[nTypes][nDivines] == 2)
        return AMBIGUOUS;

    vector<int> res;
    for(int type = nTypes-1, nRemain = nDivines; type >= 0; type--) {
        int side = dp[type+1][nRemain];
        vector<int>& g = groups[type][side];
        nRemain -= g.size();
        res.insert(res.end(), ALLOF(g));
    }

    sort(ALLOF(res));
    return res;
}

int main() {

    for(;;) {

        int nQuestions, nDivines, nDevils;
        cin >> nQuestions >> nDivines >> nDevils;

        if (nQuestions == 0 && nDivines == 0 && nDevils == 0)
            break;

        int n = nDivines + nDevils;

        Graph g(n);

        REP(i, nQuestions) {
            int a, b;
            string outcome;
            cin >> a >> b >> outcome;
            a--; b--;
            g[a].push_back((Edge){a, b, (outcome == "yes" ? 1 : -1)});
            g[b].push_back((Edge){b, a, (outcome == "yes" ? 1 : -1)});
        }

        vector<int> res = solve(g, nDivines);
        if (res == AMBIGUOUS) {
            cout << "no" << endl;
        }
        else {
            REP(i, res.size())
                cout << res[i]+1 << endl;
            cout << "end" << endl;
        }

    }

    return 0;
}

