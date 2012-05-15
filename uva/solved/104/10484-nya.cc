/*
 * UVA 10484 Divisibility of Factors
 * 2005-09-16
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define N_MAX 100

bool bPrimes[N_MAX+1];
std::vector<int> primes;
int nPrimes;

void init_primes() {
    bPrimes[0] = bPrimes[1] = false;
    std::fill(bPrimes+2, bPrimes+N_MAX+1, true);
    for(int i=2; i<=N_MAX; i++) {
        if (bPrimes[i]) {
            for(int j=i*i; j<=N_MAX; j+=i)
                bPrimes[j] = false;
            primes.push_back(i);
        }
    }
    nPrimes = primes.size();
}

inline bool isprime(int n) {
    return bPrimes[n];
}

struct Unfactorizable {};

std::vector<int> factorize(int n) {
    std::vector<int> factors(nPrimes, 0);
    for(int i=0; i<nPrimes; i++) {
        int p = primes[i];
        while(n%p == 0) {
            factors[i]++;
            n /= p;
        }
    }
    if (n != 1)
        throw Unfactorizable();
    return factors;
}


std::vector< std::vector<int> > composites;

void init_composites() {
    composites.assign(N_MAX+1, std::vector<int>(nPrimes, 0));
    for(int n=2; n<=N_MAX; n++) {
        composites[n] = composites[n-1];
        std::vector<int> factors = factorize(n);
        for(int i=0; i<nPrimes; i++)
            composites[n][i] += factors[i];
    }
}


unsigned long long int solve(const int n, const int d) {
    unsigned long long int nFactors;
    try {
        const std::vector<int>& factorsOfN = composites[n];
        const std::vector<int>& factorsOfD = factorize(d);
        nFactors = 1;
        for(int i=0; i<nPrimes; i++) {
            if (factorsOfN[i] < factorsOfD[i]) {
                nFactors = 0;
                break;
            }
            nFactors *= (factorsOfN[i] - factorsOfD[i] + 1);
        }
    }
    catch(Unfactorizable) {
        nFactors = 0;
    }
    return nFactors;
}

int main() {

    init_primes();
    init_composites();

    int n, d;
    while(std::cin >> n >> d && !(n == 0 && d == 0)) {
        std::cout << solve(n, d) << std::endl;
    }

    return 0;
}
