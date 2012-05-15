#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int emit_pos = 0;
void emit_start() {
    emit_pos = 0;
}
inline void emit(int r, int c) {
    printf("%s[%d,%d]", (emit_pos == 0 ? "" : " "), r+1, c+1);
    emit_pos++;
    if (emit_pos == 8) {
        printf("\n");
        emit_pos = 0;
    }
}
void emit_end() {
    if (emit_pos > 0)
        printf("\n");
    emit_pos = 0;
}

void solve(int n, int r=0, int c=0) {
    if (n == 0)
        return;
    if (n%3 != 1) {
        emit(r, c);
        solve(n-2, r+2, c+1);
        return;
    }
    int k = n / 3;
    r += k;
    REP(i, k) {
        emit(r, c);
        emit(r+1, c+k+1);
        r += 2;
        c += 1;
    }
    emit(r, c);
}

int main() {
    int nCases;
    scanf("%d", &nCases);
    REP(iCase, nCases) {
        int n;
        scanf("%d", &n);
        int m = (2*n+1)/3;
        if (iCase > 0)
            printf("\n");
        printf("%d %d %d\n", iCase+1, n, m);
        emit_start();
        solve(n);
        emit_end();
    }
    return 0;
}
