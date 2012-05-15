#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 1000

int phi(int n) {
    int res = n;
    for(int p = 2; n > 1; p++) {
        if (n%p == 0) {
            do n /= p; while(n%p == 0);
            res = res / p * (p-1);
        }
    }
    return res;
}

int solve(int n) {
    static int mem[N+1];
    static bool init = false;
    if (!init) {
        mem[1] = 3;
        for(int i = 2; i <= N; i++)
            mem[i] = mem[i-1] + 2*phi(i);
        init = true;
    }
    return mem[n];
}

int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int n;
        cin >> n;
        cout << iCase+1 << ' ' << n << ' ' << solve(n) << endl;
    }
    return 0;
}
