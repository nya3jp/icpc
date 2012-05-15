#include <cstdio>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 40000

typedef float decimal;

typedef complex<decimal> P;
struct C {
    P c;
    decimal r;
    int id;
};

int n;
C cones[N+1];
bool dominated[N];
int distance_root;

inline bool by_radius_cone(const C& a, const C& b) {
    return (a.r < b.r);
}

inline bool by_reverse_radius(int a, int b) {
    return (cones[a].r > cones[b].r);
}

inline bool by_distance(int a, int b) {
    return (abs(cones[a].c - cones[distance_root].c) < abs(cones[b].c - cones[distance_root].c));
}

void go(int root, const int* cands_given, int nCands_given) {

    if (nCands_given == 0)
        return;
    if (nCands_given == 1) {
        if (cands_given[0] != root && abs(cones[cands_given[0]].c - cones[root].c) < cones[root].r)
            dominated[cands_given[0]] = true;
        return;
    }

    int* cands = new int[nCands_given];
    int nCands = 0;
    REP(i, nCands_given)
        if (cands_given[i] > root)
            cands[nCands++] = cands_given[i];

    if (nCands == 0)
        return;
    if (nCands == 1) {
        if (cands[0] != root && abs(cones[cands[0]].c - cones[root].c) < cones[root].r)
            dominated[cands[0]] = true;
        return;
    }

    /*
    printf("%d :", root);
    REP(i, nCands)
        printf(" %d", cands[i]);
    printf("\n");
    */

    distance_root = root;
    stable_sort(cands, cands+nCands, by_distance);

    cones[n].c = cones[root].c + P(cones[root].r, 0);
    int nInside = lower_bound(cands, cands+nCands, n, by_distance) - cands;
    REP(i, nInside) {
        dominated[cands[i]] = true;
        //printf("%d ", cands[i]);
    }
    /*
    if (nInside == 0)
        printf("No cone ");
    printf("inside of %d.\n", root);
    */

    int* cands2 = new int[nCands];
    REP(i, nCands)
        cands2[i] = cands[i];
    stable_sort(cands2, cands2+nCands, by_reverse_radius);
    //reverse(cands2, cands2+nCands);

    REP(i, nCands) {
        int next = cands2[i];
        if (!dominated[next]) {
            distance_root = root;
            decimal inf = abs(cones[next].c - cones[root].c) - cones[next].r;
            decimal sup = abs(cones[next].c - cones[root].c) + cones[next].r;
            if (inf < 0)
                inf = 0;
            cones[n].c = cones[root].c + P(inf, 0);
            int from = lower_bound(cands, cands+nCands, n, by_distance) - cands;
            cones[n].c = cones[root].c + P(sup, 0);
            int to   = lower_bound(cands, cands+nCands, n, by_distance) - cands;
            go(next, cands+from, to-from);
        }
    }

    delete[] cands;
    delete[] cands2;
}

int main() {

    scanf("%d", &n);

    REP(i, n) {
        double x, y, r;
        scanf("%lf%lf%lf", &r, &x, &y);
        cones[i].c = P((decimal)x, (decimal)y);
        cones[i].r = r;
        cones[i].id = i+1;
    }

    REP(i, n)
        dominated[i] = false;

    stable_sort(cones, cones+n, by_radius_cone);
    reverse(cones, cones+n);

    /*
    REP(i, n) {
        printf("cone %d: (%.1f,%.1f) %.1f\n", i, cones[i].c.real(), cones[i].c.imag(), cones[i].r);
    }
    */

    int* cands = new int[n];
    REP(i, n)
        cands[i] = i;
    go(0, cands, n);
    delete[] cands;

    int nDominants = count(dominated, dominated+n, false);
    printf("%d\n", nDominants);
    int* dominants = new int[nDominants];

    for(int p = 0, i = 0; i < n; i++)
        if (!dominated[i])
            dominants[p++] = cones[i].id;
    stable_sort(dominants, dominants+nDominants);

    REP(i, nDominants) {
        printf("%d%s", dominants[i], (i < nDominants-1 ? " " : "\n"));
    }

    return 0;
}

