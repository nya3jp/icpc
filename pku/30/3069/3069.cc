#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int main() {
    int r, n;
    while(scanf("%d%d", &r, &n) == 2 && r >= 0) {
        vector<int> v(n);
        REP(i, n)
            scanf("%d", &v[i]);
        sort(ALLOF(v));
        v.push_back(10000);
        n++;

        int res = 0;
        int left = v[0];
        REP(i, n) {
            if (left < v[i]-r) {
                //printf("place at %d\n", v[i-1]);
                res++;
                left = *upper_bound(ALLOF(v), v[i-1]+r);
            }
        }

        printf("%d\n", res);

    }
    return 0;
}
