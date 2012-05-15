#include <cstdio>
#include <limits>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 100000

int n;
int m, k;
int riders[N];

bool go(int t) {
    long long int boosts = 0;
    REP(i, n) {
        int l = max(0, (riders[i] - t + (k - 1 - 1)) / (k - 1));
        if (l > t)
            return false;
        boosts += l;
    }
    return (boosts <= (long long int)t * m);
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        scanf("%d", &n);

        REP(i, n)
            scanf("%d", &riders[i]);

        scanf("%d%d", &m, &k);

        int lower = 0, upper = *max_element(riders, riders+n);

        if ( k == 1)
            lower = upper;

        while(lower < upper) {
            int middle = (lower+upper)/2;
            if (go(middle)) {
                upper = middle;
            }
            else {
                lower = middle+1;
            }
        }

        printf("%d\n", lower);

    }

    return 0;
}
