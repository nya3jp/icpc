#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int n, l;
    //cin >> n >> l;
    scanf("%d%d", &n, &l);
    int* v = new int[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    sort(v, v+n);

    int q = 0;
    while(n > 0) {
        int h = v[--n];
        if (n > 0) {
            int r = l - h;
            int p = lower_bound(v, v+n, r) - v;
            if (p == n || v[p] > r)
                p--;
            if (v[p] <= r) {
                copy(v+p+1, v+n, v+p);
                n--;
            }
        }
        //cout << endl;
        q++;
    }

    printf("%d\n", q);

    return 0;
}
