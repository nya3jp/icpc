#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

#define MAX_PRIME 10001
#define N 10000

bool isprime_[MAX_PRIME+1];
vector<int> primes_;

void init_prime() {
    isprime_[0] = isprime_[1] = false;
    fill(isprime_+2, isprime_+MAX_PRIME+1, true);
    for(int i = 2; i <= MAX_PRIME; i++) {
        if (isprime_[i]) {
            primes_.push_back(i);
            if ((long long int)i*i <= MAX_PRIME)
                for(int j = i*i; j <= MAX_PRIME; j += i)
                    isprime_[j] = false;
        }
    }
}

bool isprime(int n) {
    if (n <= MAX_PRIME)
        return isprime_[n];
    for(int i = 0; i < (int)primes_.size(); i++) {
        int k = primes_[i];
        if (k*k > n)
            break;
        if (n%k == 0)
            return false;
    }
    return true;
}

int main() {

    init_prime();

    vector<bool> table(N+1);
    for(int n = 0; n <= N; n++)
        table[n] = isprime(n*n + n + 41);

    int a, b;
    while(cin >> a >> b)
        printf("%.2f\n",
               100.0 * count(table.begin()+a, table.begin()+b+1, true) / (b-a+1));

    return 0;
}
