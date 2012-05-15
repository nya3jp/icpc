/*
 * UVA 10539 - Almost Prime Numbers
 * 2006-01-14
 * by nya
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

typedef long long int integer;

#define MAX_PRIME 1000000
#define MAX_ALMOSTPRIME 1000000000000ll

int main() {

    std::vector<bool> isprime(MAX_PRIME+1, true);
    isprime[0] = isprime[1] = false;
    for(int i = 4; i <= MAX_PRIME; i += 2) {
        isprime[i] = false;
    }
    for(int i = 3; i <= MAX_PRIME; i += 2) {
        if (isprime[i]) {
            if ((integer)i*(integer)i <= MAX_PRIME) {
                for(int j = i*i; j <= MAX_PRIME; j += i) {
                    isprime[j] = false;
                }
            }
        }
    }

    std::list<integer> almostprimeslist;
    for(integer i = 2; i <= MAX_PRIME; i++) {
        if (isprime[i]) {
            for(integer j = i*i; j <= MAX_ALMOSTPRIME; j *= i) {
                almostprimeslist.push_back(j);
            }
        }
    }

    std::vector<integer> almostprimes(almostprimeslist.begin(), almostprimeslist.end());
    std::sort(almostprimes.begin(), almostprimes.end());

    /*
    for(std::vector<integer>::const_iterator it = almostprimes.begin();
        it != almostprimes.end();
        ++it)
    {
        std::cout << *it << std::endl;
    }
    */

    int nCases;
    std::cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        integer iLower, iHigher;
        std::cin >> iLower >> iHigher;
        int result =   std::upper_bound(almostprimes.begin(), almostprimes.end(), iHigher)
                     - std::lower_bound(almostprimes.begin(), almostprimes.end(), iLower);
        std::cout << result << std::endl;
    }

    return 0;
}

