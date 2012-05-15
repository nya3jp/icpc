#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int search(int ipos, int iv, vector<int>& pos, vector<int>& v) {
    int n = pos.size(), m = v.size();
    if (ipos == n) {
        do {
            REP(i, n-1)
                pos[i+1] += pos[i];
            /*
            printf("{ ");
            REP(i, n)
                printf("%d,", pos[i]);
            printf(" }\n");
            */
            vector<int> u;
            u.reserve(m);
            REP(j, n) REP(i, j)
                u.push_back(pos[j]-pos[i]);
            sort(ALLOF(u));
            if (u == v) {
                int res = 1;
                REP(i, n-1)
                    res *= pos[i+1] - pos[i];
                return res;
            }
            REP(i, n-1)
                pos[n-1-i] -= pos[n-2-i];
        } while(next_permutation(ALLOF(pos)));
        return -1;
    }
    while(iv < m) {
        pos[ipos] = v[iv];
        int res = search(ipos+1, iv+1, pos, v);
        if (res >= 0)
            return res;
        iv++;
    }
    return -1;
}

int solve(vector<int>& v, int n) {
    vector<int> pos(n, 0);
    return search(1, 0, pos, v);
}

int main() {

    for(;;) {

        int m;
        cin >> m;
        if (!cin)
            break;

        vector<int> v(m);
        REP(i, m)
            scanf("%d", &v[i]);

        int n = 0;
        while((n+1)*n/2 <= m)
            n++;

        int res;
        if (n*(n-1)/2 != m) {
            res = -1;
        }
        else {
            res = solve(v, n);
        }

        if (res < 0)
            printf("No solution\n");
        else
            printf("%d\n", res);

    }

    /*
    int n = 10;
    int m = 4;

    vector<int> choice(n);
    REP(i, n)
        choice[i] = i;

    map< vector<int>, vector<int> > mem;

    for(;;) {
        REP(i, n) {
            int j = i + rand()%(n-i);
            swap(choice[i], choice[j]);
        }
        vector<int> a(choice.begin(), choice.begin()+m);
        sort(ALLOF(a));
        { int k = a[0]; REP(i, m) a[i] -= k; }
        vector<int> b;
        REP(i, m) REP(j, i)
            b.push_back(a[i]-a[j]);
        sort(ALLOF(b));
        if (mem.count(a) == 0) {
            mem[a] = b;
        }
        else {
            if (mem[a] != b) {
                printf("not unique\n");
                REP(i, b.size())
                    printf("%d ", b[i]);
                printf("\n--> ");
                REP(i, a.size())
                    printf("%d ", a[i]);
                printf("\n");
                REP(i, b.size())
                    printf("%d ", mem[a][i]);
                printf("\n--> ");
                REP(i, a.size())
                    printf("%d ", a[i]);
                printf("\n");
                return 1;
            }
        }
        vector<int> c = solve(b);
        if (a != c) {
            printf("wrong answer\n");
            REP(i, b.size())
                printf("%d ", b[i]);
            printf("\n--> ");
            REP(i, a.size())
                printf("%d ", a[i]);
            printf("\n");
            REP(i, b.size())
                printf("%d ", b[i]);
            printf("\n--> ");
            REP(i, c.size())
                printf("%d ", c[i]);
            printf("\n");
        }
    }
    */

    return 0;
}

