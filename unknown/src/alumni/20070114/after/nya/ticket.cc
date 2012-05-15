#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

map<string,int> ids;
int ID(const string& name) {
    if (ids.count(name) == 0)
        ids.insert(make_pair(name, ids.size()));
    return ids[name];
}


#define N 30
#define INF 876543210

int adj[N][N];
int pairs[8];
int n, m;

typedef vector<int> Tree;
typedef vector<Tree> Forest;

int mst(const Tree& exteriors, const Tree& interiors) {
    //cerr << "mst()" << endl;
    Tree nodes;
    nodes.insert(nodes.end(), ALLOF(exteriors));
    nodes.insert(nodes.end(), ALLOF(interiors));

    int res = 0;
    vector<bool> seen(nodes.size(), false);
    vector<int> costs(nodes.size(), INF);
    costs[0] = 0;

    REP(a, nodes.size()) {
        int next = -1;
        REP(i, nodes.size())
            if (!seen[i] && (next < 0 || costs[i] < costs[next]))
                next = i;

        seen[next] = true;
        res += costs[next];
        REP(i, nodes.size())
            costs[i] <?= adj[nodes[next]][nodes[i]];
    }

    return res;
}

int make_interiors(const Tree& exteriors, Tree& interiors, int next) {
    //cerr << "make_interiors()" << endl;
    if (n-next < (int)((exteriors.size()-2)-interiors.size()))
        return INF;
    if (next == n) {
        return mst(exteriors, interiors);
    }
    else {
        int res;
        res = INF;
        if (interiors.size() < exteriors.size()-2 && count(ALLOF(exteriors), next) == 0) {
            interiors.push_back(next);
            res <?= make_interiors(exteriors, interiors, next+1);
            interiors.pop_back();
        }
        res <?= make_interiors(exteriors, interiors, next+1);
        return res;
    }
}

int steiner_tree(const Tree& exteriors) {
    //cerr << "steiner_tree()" << endl;
    Tree interiors;
    return make_interiors(exteriors, interiors, 0);
}

int make_forest(Forest& forest, int next) {
    //cerr << "make_forest()" << endl;
    int res;
    if (next == 8) {
        res = 0;
        cerr << "{" << endl;
        REP(i, forest.size()) {
            REP(j, forest[i].size())
                cerr << forest[i][j] << " ";
            cerr << endl;
        }
        cerr << "}" << endl;
        REP(i, forest.size())
            res += steiner_tree(forest[i]);
    }
    else {
        res = INF;
        REP(i, forest.size()) {
            forest[i].push_back(next);
            forest[i].push_back(next+1);
            res <?= make_forest(forest, next+2);
            forest[i].pop_back();
            forest[i].pop_back();
        }
        Tree tree(2);
        tree[0] = next;
        tree[1] = next+1;
        forest.push_back(tree);
        res <?= make_forest(forest, next+2);
        forest.pop_back();
    }
    return res;
}

int solve() {
    //cerr << "solve()" << endl;
    REP(j, n) REP(i, n) REP(k, n)
        adj[i][k] <?= adj[i][j] + adj[j][k];

    Forest forest;
    return make_forest(forest, 0);
}


int main() {

    for(;;) {

        cin >> n >> m;

        if (n == 0 && m == 0)
            break;

        REP(i, n) REP(j, n)
            adj[i][j] = INF;
        REP(i, n)
            adj[i][i] = 0;

        ids.clear();
        REP(i, n) {
            string s;
            cin >> s;
            ID(s);
        }

        REP(i, m) {
            string s1, s2;
            int w;
            cin >> s1 >> s2 >> w;
            int a = ID(s1), b = ID(s2);
            adj[a][b] <?= w;
            adj[b][a] <?= w;
        }

        REP(i, 8) {
            string s;
            cin >> s;
            pairs[i] = ID(s);
        }

        cout << solve() << endl;
        cout << "nya-" << endl;

    }

    return 0;
}


