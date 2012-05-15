#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define MAX_PRIME 10000

bool isprime[MAX_PRIME+1];
std::vector<int> primes;
std::vector<int> prime_partial_sums;

void init_primes() {
    std::fill(isprime+2, isprime+MAX_PRIME+1, true);
    isprime[0] = isprime[1] = false;
    primes.clear();
    for(int i=2; i<=MAX_PRIME; i++) {
        if (isprime[i]) {
            for(int j=i*i; j<=MAX_PRIME; j+=i)
                isprime[j] = false;
            primes.push_back(i);
        }
    }
}

void init_prime_partial_sums() {
    prime_partial_sums.clear();
    prime_partial_sums.push_back(0);
    std::partial_sum(primes.begin(), primes.end(), std::back_inserter(prime_partial_sums));
}


int solve(const int n) {
    int count = 0;
    for(int i = ( std::lower_bound(prime_partial_sums.begin(), prime_partial_sums.end(), n) - prime_partial_sums.begin() );
        i < (int)prime_partial_sums.size();
        i++) {
        if (std::binary_search(prime_partial_sums.begin(), prime_partial_sums.end(), prime_partial_sums[i] - n))
            count++;
    }
    return count;
}


int main() {
    init_primes();
    init_prime_partial_sums();

    int n;
    while(std::cin >> n && n != 0) {
        std::cout << solve(n) << std::endl;
    }
    return 0;
}
