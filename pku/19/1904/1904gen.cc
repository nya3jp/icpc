/**
 * @file
 * グラフ:二部グラフの最大マッチング
 *
 * @version
 * rev.01
 */

#include <vector>

using namespace std;


enum BipartiteGraphMatchingConst { UNMATCHED = -1 };

struct BipartiteGraph {
    int lefts, rights;
    vector< vector<int> > toleft;
    vector< vector<int> > toright;

    vector<int> matching_left;
    vector<int> matching_right;

    vector<bool> visited;

    BipartiteGraph(int lefts, int rights)
        : lefts(lefts), rights(rights), toleft(lefts), toright(rights) {
    }

    void insert_edge(int left, int right) {
        toright[left].push_back(right);
        toleft[right].push_back(left);
    }

    bool augment(int left) {
        if (left == UNMATCHED)
            return true;
        const vector<int>& edges = toright[left];
        for(int i = 0; i < (int)edges.size(); i++) {
            int right = edges[i];
            if (!visited[right]) {
                visited[right] = true;
                if (augment(matching_right[right])) {
                    matching_left[left] = right;
                    matching_right[right] = left;
                    return true;
                }
            }
        }
        return false;
    }

    int match() {
        matching_left.assign(lefts, UNMATCHED);
        matching_right.assign(rights, UNMATCHED);

        int matches = 0;
        for(int left = 0; left < lefts; left++) {
            visited.assign(rights, false);
            if (augment(left))
                matches++;
        }
        return matches;
    }
};




using namespace std;


#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>


int main() {

    srand(283);

    int n = 2000;

    BipartiteGraph g(n, n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (rand()&0x10000) {
                g.insert_edge(i, j);
            }
        }
    }

    cerr << "matching..." << endl;

    assert(g.match() == n);

    cerr << "done." << endl;

    cout << n << endl;
    for(int i = 0; i < n; i++) {
        cout << (int)g.toright[i].size();
        for(int j = 0; j < (int)g.toright[i].size(); j++) {
            cout << ' ' << g.toright[i][j];
        }
        cout << endl;
    }
    for(int i = 0; i < n; i++) {
        cout << g.matching_left[i] << ' ';
    }
    cout << endl;

    return 0;
}









