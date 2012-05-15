#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int integer;

#define N 20
#define D 500

integer mem[N][N];


int n;

integer f(int i, int j) {
    integer& m = mem[i][j];
    if (m < 0) {
        if (i >= j) {
            integer a = 0;
            for(int k = i+1; k <= n; k++)
                a = max(a, f(k, 1) + f(k, j));
            integer b = 0;
            for(int k = 1; k < j; k++)
                b = max(b, f(i, k) + f(n, k));
            m = a+b;
        }
        else {
            integer a = 0;
            for(int k = i; k < j; k++)
                a = max(a, f(i, k) + f(k+1, j));
            m = a;
        }
    }
    return m;
}

int main() {
    for(int s; cin >> n >> s; ) {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                mem[i][j] = -1;
        mem[n][1] = s;
        cout << f(1, n) << endl;
    }
    return 0;
}
