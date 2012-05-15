#include <cstdio>
#include <vector>

using namespace std;

#define MAX_PRIME 431

//vector<int> primes;
int primes[83];
int nPrimes;
bool isprime[MAX_PRIME+1];

int factors[83];

void factorize(int n) {
    for(int p = 0; p < nPrimes; p++) {
        if (n < primes[p])
            break;
        while(n%primes[p] == 0) {
            n /= primes[p];
            factors[p]++;
        }
    }
}
void factorize_fact(int n) {
    while(n > 1)
        factorize(n--);
}
void factorize_fact(int l, int h) {
    while(l <= h)
        factorize(l++);
}

int main() {

    fill(isprime, isprime+MAX_PRIME+1, true);
    isprime[0] = isprime[1] = false;
    nPrimes = 0;
    {
        for(int i = 2; i <= MAX_PRIME; i++) {
            if (isprime[i]) {
                primes[nPrimes++] = i;
                for(int j = i*i; j <= MAX_PRIME; j += i)
                    isprime[j] = false;
            }
        }
    }

    int n, k;
    while(scanf("%d%d", &n, &k) == 2) {
        int i;
        for(i = 0; i < nPrimes; i++)
            factors[i] = 0;
        //factorize_fact(k);
        //factorize_fact(n-k);
        factorize_fact(1, k);
        for(i = 0; i < nPrimes; i++)
            factors[i] *= -1;
        factorize_fact(n-k+1, n);
        //factorize_fact(n);
        __int64 res = 1;
        for(i = 0; i < nPrimes; i++)
            res *= factors[i]+1;
        printf("%I64d\n", res);
    }
        


    return 0;
}
