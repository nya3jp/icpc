#include <cstdio>
#include <algorithm>
#include <limits>

using namespace std;

#define N 100000

int v[N];
int left[N];
int right[N];

void solve(int n) {
    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    {
        int s = 0;
        for(int i = 0; i < n; i++) {
            s += v[i];
            left[i] = s;
            if (s < 0)
                s = 0;
        }
        for(int i = 1; i < n; i++) {
            left[i] = max(left[i], left[i-1]);
        }
    }
    {
        int s = 0;
        for(int i = n-1; i >= 0; i--) {
            s += v[i];
            right[i] = s;
            if (s < 0)
                s = 0;
        }
        for(int i = n-2; i >= 0; i--) {
            right[i] = max(right[i], right[i+1]);
        }
    }
    int r = numeric_limits<int>::min();
    for(int i = 0; i < n-1; i++) {
        r = max(r, left[i] + right[i+1]);
    }
    printf("%d\n", r);
}

int main() {
    int n;
    while(scanf("%d", &n), n > 0)
        solve(n);
    return 0;
}

