#include <cstdio>
#include <map>

using namespace std;

int f(int base, int n, int limit, int mod) {
    // returns 0 ~ limit-1, limit ~ limit+mod-1
    if (n == 0)
        return 1;
    printf("f(n=%d, period=(%d,%d)):\n", n, limit, mod);
    int limit1, mod1;
    {
        map<int, int> m;
        int t = 1, lg = 0;
        while(true) {
            if (m.find(t) != m.end()) {
                limit1= m[t];
                mod1 = lg - limit1;
                break;
            }
            m[t] = lg;
            t = t * base % mod;
            lg++;
        }
    }
    printf("  period -> (%d,%d)\n", limit1, mod1);
    int f0 = f(base, n-1, limit1, mod1);
    int x = 1;
    bool limitover = false;
    for(int i = 0; i < f0; i++) {
        x = x * base;
        if (x >= limit) {
            limitover = true;
        }
        if (limitover && x >= mod) {
            x %= mod;
        }
    }
    if (limitover) {
        x -= limit;
        while(x < 0)
            x += mod;
        x += limit;
    }
    printf("f(n=%d, period=(%d,%d)) = %d\n", n, limit, mod, x);
    return x;
}

int main() {
    while(true) {
        int base, n, digits;
        scanf("%d%d%d", &base, &n, &digits);
        if (base == 0)
            break;
        int pow10n = 1;
        for(int i = 0; i < digits; i++)
            pow10n *= 10;
        char format[16];
        sprintf(format, "%%0%dd\n", digits);
        printf(format, f(base, n, 0, pow10n));
    }
    return 0;
}

