#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int n;
int m;
int v[100000];

bool go(int dist) {
    int c = 0;
    int last = -dist-1;
    REP(i, n) {
        int here = v[i];
        if (here-last >= dist) {
            last = here;
            c++;
        }
    }
    return (c >= m);
}

int main() {

    scanf("%d%d", &n, &m);

    REP(i, n)
        scanf("%d", &v[i]);
    sort(v, v+n);

    int lower = 1, upper = v[n-1]; // inclusive

    while(upper-lower > 0) {
        int middle = (lower+upper+1)/2;
        if (go(middle)) {
            lower = middle;
        }
        else {
            upper = middle-1;
        }
    }

    printf("%d\n", lower);

    return 0;
}
