/*
 * UVA 10392 Factoring Large Numbers
 * 2005-06-01
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define LIMIT 1000000
#define HEADER "    "

bool isprime[LIMIT+1];
vector<int> primes;

void init() {
    fill(isprime, isprime+LIMIT+1, true);
    isprime[0] = isprime[1] = false;
    for(int n=2; n<=LIMIT; n++) {
        if (isprime[n]) {
            for(int m=n*2; m<=LIMIT; m+=n) {
                isprime[m] = false;
            }
            primes.push_back(n);
        }
    }
}

int main() {

    init();

    long long int n;
    while(cin >> n && n >= 0) {

        for(vector<int>::const_iterator it = primes.begin(); n != 1 && it != primes.end(); ++it) {
            int prime = *it;

            while(n % prime == 0) {
                n /= prime;
                cout << HEADER << prime << endl;
            }
        }

        if (n != 1) {
            cout << HEADER << n << endl;
        }

        cout << endl;
    }

    return 0;
}
