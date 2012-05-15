#include <iostream>
#include <vector>

using namespace std;


#define MAX_PRIME 60000u
#define INF       0x7fffffffu
#define MAX_N     0x7fffffffu
/*
#define MAX_PRIME 16u
#define INF       0x7fffffffu
#define MAX_N     100u
*/

vector<int> primes_v;
int* primes;
int nPrimes;

bool isprime[MAX_PRIME+1];

void init_primes() {
    fill(isprime, isprime+MAX_PRIME+1, true);
    isprime[0] = isprime[1] = false;
    for(unsigned int n = 2; n <= MAX_PRIME; n++) {
        if (isprime[n]) {
            for(unsigned int m = n*n; m <= MAX_PRIME; m += n)
                isprime[m] = false;
            primes_v.push_back(n);
        }
    }
    nPrimes = primes_v.size();
    primes = new int[nPrimes];
    copy(primes_v.begin(), primes_v.end(), primes);
    assert(MAX_PRIME*MAX_PRIME >= MAX_N);
}



int main() {
    init_primes();
    unsigned int lower, upper;
    while(cin >> lower >> upper) {
        unsigned int delta = upper-lower;
        //vector<bool> v(delta+1, true);
        bool* v = new bool[delta+1];
        fill(v, v+delta+1, true);
        if (lower == 1)
            v[0] = false;
        for(int i = 0; i < nPrimes; i++) {
            unsigned int p = primes[i];
            for(unsigned int n = (lower+p-1)/p*p; n <= upper; n += p) {
                if (n != p)
                    v[n-lower] = false;
            }
        }
        /*
        for(int i = 0; i <= delta; i++) {
            if (v[i])
                cout << lower+i << endl;
        }
        */
        int last = -1;
        int closestFirst = -1, distantFirst = -1;
        int closestDelta = INF, distantDelta = 0;
        for(unsigned int i = 0; i <= delta; i++) {
            if (v[i]) {
                if (last >= 0) {
                    int d = i - last;
                    if (d < closestDelta) {
                        closestFirst = last+lower;
                        closestDelta = d;
                    }
                    if (d > distantDelta) {
                        distantFirst = last+lower;
                        distantDelta = d;
                    }
                }
                last = i;
            }
        }
        if (closestFirst < 0) {
            cout << "There are no adjacent primes." << endl;
        }
        else {
            cout << closestFirst << "," << (closestFirst+closestDelta) << " are closest, "
                 << distantFirst << "," << (distantFirst+distantDelta) << " are most distant." << endl;

        }
        delete[] v;
    }
    return 0;
}

