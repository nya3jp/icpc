//#define NYA_DEBUG

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

const int PRIMES[10] = {2,3,5,7,11,13,17,19,23,29};

unsigned long long int n;
unsigned long long int positives[1<<10];
unsigned long long int negatives[1<<10];
unsigned long long int zeros;
#ifdef NYA_DEBUG
unsigned long long int givens[100];
#endif

int decompose(long long int m) {
    assert(m > 0);
    int res = 0;
    REP(i, 10) {
        int p = PRIMES[i];
        int b = 1<<i;
        while(m%p == 0) {
            m /= p;
            res ^= b;
        }
    }
    assert(m == 1);
    return res;
}

#ifdef NYA_DEBUG
bool is_square(long long int m) {
    if (m == 0)
        return true;
    if (m < 0)
        return false;
    return (decompose(m) == 0);
}
#endif

unsigned long long int solve2() {
    unsigned long long int res = 0;

    res += zeros * (n-zeros) + zeros * (zeros-1) / 2;

    REP(i, 1<<10) {
        res += positives[i] * (positives[i]-1) / 2;
        res += negatives[i] * (negatives[i]-1) / 2;
    }

    return res;
}

unsigned long long int solve3() {
    unsigned long long int res = 0;

    res += zeros * (n-zeros) * (n-zeros-1) / 2 + zeros * (zeros-1) * (n-zeros) / 2 + zeros * (zeros-1) * (zeros-2) / 6;

    res += positives[0] * (positives[0]-1) * (positives[0]-2) / 6;
    res += positives[0] * negatives[0] * (negatives[0]-1) / 2;
    for(int j = 1; j < (1<<10); j++) {
        res += positives[0] * positives[j] * (positives[j]-1) / 2;
        res += positives[0] * negatives[j] * (negatives[j]-1) / 2;
        res += negatives[0] * positives[j] * negatives[j];
    }
    for(int i = 1; i < (1<<10); i++) {
        for(int j = i+1; j < (1<<10); j++) {
            int k = i ^ j;
            if (j < k) {
                res += positives[i] * positives[j] * positives[k];
                res += positives[i] * negatives[j] * negatives[k];
                res += negatives[i] * positives[j] * negatives[k];
                res += negatives[i] * negatives[j] * positives[k];
            }
        }
    }

    return res;
}

int main() {

    int nCases;
#ifdef NYA_DEBUG
    nCases = 100000;
#else
    cin >> nCases;
#endif

    REP(iCase, nCases) {

        REP(i, 1<<10)
            positives[i] = negatives[i] = 0;
        zeros = 0;

#ifdef NYA_DEBUG
        n = 60;
#else
        cin >> n;
#endif

        REP(i, n) {
            long long int a;
#ifdef NYA_DEBUG
            a = rand()%25-12;
            givens[i] = a;
#else
            cin >> a;
#endif

            if (a == 0) {
                zeros++;
            }
            else if (a > 0) {
                positives[decompose(a)]++;
            }
            else if (a < 0) {
                negatives[decompose(-a)]++;
            }
            else {
                assert(false);
            }

        }

#ifdef NYA_DEBUG
        REP(i, n) {
            printf("%d ", (int)givens[i]);
        }
        printf("\n");
#endif

        unsigned long long int res2 = solve2();
        unsigned long long int res3 = solve3();
        cout << res2 << " " << res3 << endl;

#ifdef NYA_DEBUG
        {
            int res2a = 0;
            REP(i, n) REP(j, n) if (i < j) {
                if (is_square(givens[i]*givens[j]))
                    res2a++;
            }
            int res3a = 0;
            REP(i, n) REP(j, n) REP(k, n) if (i < j && j < k) {
                if (is_square(givens[i]*givens[j]*givens[k]))
                    res3a++;
            }
            if (res2 != res2a || res3 != res3a) {
                break;
            }
        }
#endif

    }

    return 0;
}

