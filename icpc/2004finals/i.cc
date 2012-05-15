#include <cstdio>
#include <vector>
#include <algorithm>

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



struct TD {
    int x, y;
};

inline bool operator<(const TD& a, const TD& b) {
    return (a.x > b.x);
}

int main() {
    int iCase = 0;
    int n;
    while(scanf("%d", &n), n != 0) {
        vector<TD> a(n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].x, &a[i].y);
        }
        sort(a.begin(), a.end());
        int m;
        scanf("%d", &m);
        vector<TD> b(m);
        for(int i = 0; i < m; i++) {
            int hh, mm;
            scanf("%d%d:%d", &b[i].x, &hh, &mm);
            b[i].y = (hh-14)*60 + mm;
        }
        BipartiteGraph g(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (a[i].x <= b[j].x && a[i].y <= b[j].y)
                    g.insert_edge(i, j);
            }
        }
        g.match();
        int tn = 0;
        int tx = 0;
        for(int i = 0; i < n; i++) {
            if (g.matching_left[i] == UNMATCHED) {
                tn++;
                tx += a[i].x;
            }
        }
        if (iCase > 0)
            printf("\n");
        printf("Trial %d:  %d %d\n", ++iCase, tn, tx);
    }
    return 0;
}

