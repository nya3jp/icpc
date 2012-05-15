#include <cstdio>

#define for if(0);else for
typedef __int64 integer;
//typedef long long int integer;
//using namespace std;


int query(int pos, int n) {

    int len = 1;
    integer from = 0;
    integer to = n;
    integer p = n;
    while(!(from <= pos && pos < to)) {
        len++;
        p *= n;
        from = to;
        to += p * len;
    }

    int relpos = pos - from;

    int digit = relpos % len;
    int index = relpos / len;

    int result = index;
    for(int i = digit; i < len-1; i++)
        result /= n;
    result %= n;

    return result;
}

void solve() {
    int n, q;
    scanf("%d%d", &n, &q);
    if (n == 0 && q == 0)
        return;
    char names[26][1001];
    for(int i = 0; i < n; i++)
        scanf("%s", names[i]);
    for(int i = 0; i < q; i++) {
        int a;
        scanf("%d", &a);
        a--;
        printf("%s\n", names[query(a, n)]);
    }
    printf("\n");
    solve();
}

int main() {
    solve();
    return 0;
}
