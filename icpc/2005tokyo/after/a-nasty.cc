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

int solve(const int n) {
    int count = 0;
    for(int i=0; i<(int)primes.size(); i++) {
        int sum = 0;
        for(int j=i; j<(int)primes.size(); j++) {
            sum += primes[j];
            if (sum >= n) {
                if (sum == n)
                    count++;
                break;
            }
        }
    }
    return count;
}


int main() {
    init_primes();

    int n;
    while(std::cin >> n && n != 0) {
        std::cout << solve(n) << std::endl;
    }
    return 0;
}
