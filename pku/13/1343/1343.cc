#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

map< vector<int>, int > mem;

int getmem(vector<int>& comp) {
    if (mem.count(comp) == 0)
        mem.insert(make_pair(comp, mem.size()));
    return mem[comp];
}

int parse(vector< vector<int> >& g, int root) {
    vector<int> comp;
    REP(i, g[root].size())
        comp.push_back(parse(g, g[root][i]));
    sort(comp.begin(), comp.end());
    return getmem(comp);
}

int toint(vector< vector<int> >& g) {
    int n = g.size();
    vector<bool> isroot(n, true);
    REP(i, n) REP(j, g[i].size())
        isroot[g[i][j]] = false;
    int root = find(isroot.begin(), isroot.end(), true) - isroot.begin();
    return parse(g, root);
}

int main() {

    int nTrees, n;
    cin >> nTrees >> n;

    vector<int> trees(nTrees);
    REP(iTree, nTrees) {
        vector< vector<int> > g(n);
        REP(i, n-1) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a].push_back(b);
        }
        trees[iTree] = toint(g);
    }

    vector<bool> printed(nTrees, false);
    REP(i, nTrees) {
        if (!printed[i]) {
            vector<int> iso(1, i);
            printed[i] = true;
            REP(j, nTrees) {
                if (!printed[j] && trees[i] == trees[j]) {
                    iso.push_back(j);
                    printed[j] = true;
                }
            }
            REP(j, iso.size()-1)
                cout << iso[j]+1 << " = ";
            cout << iso.back()+1 << " ;" << endl;
        }
    }

    return 0;
}
