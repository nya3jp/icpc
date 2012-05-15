#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int inv(int a, int p) {
    return ( a == 1 ? 1 : (1 - p*inv(p%a, a)) / a + p );
}

void phi_all(int N) {
    int a[N+1], b[N+1];
    REP(i, N+1)
        a[i] = b[i] = i;

    REP(k, N+1) {
        if (b[k] < 2)
            continue;
        for(int n = k; n <= N; n += k) {
            for(int m = k-1; b[n]%k == 0; m = k) {
                a[n] *= m;
                b[n] /= k;
            }
        }
    }
}

int* lcp(char* text, int* sa, int n) {
    int* height = new int[n];
    int* rank = new int[n];
    REP(i, n)
        rank[sa[i]] = i;
    int h = 0;
    height[0] = 0;
    REP(i, n) {
        if (rank[i] > 0) {
            int k = sa[rank[i]-1];
            while(text[i+h] == text[k+h])
                h++;
            height[rank[i]] = h;
            if (h > 0)
                h--;
        }
    }
    delete[] rank;
    return height;
}

int main() {

    int a, p;
    while(cin >> a >> p) {
        int b = inv(a, p);
        cout << b << endl;
        cout << a << "*" << b << "=" << a*b%p << endl;
    }

    return 0;
}

