/*
 * UVA 10200 Prime Time
 * 2005-05-31
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

#define N 10000
#define UPB 100010041
#define M 10100

bool table[M+1];
vector<int> primes;
bool answers[N+1];

inline bool isprime(int m) {
    for(int i=0; primes[i]*primes[i] <= m; i++) {
        if (m % primes[i] == 0)
            return false;
    }
    return true;
}

int main() {

    fill(table, table+M+1, true);
    table[0] = table[1] = false;
    for(int i=2; i<=M; i++) {
        if (table[i]) {
            primes.push_back(i);
            for(int j=i*2; j<=M; j+=i) {
                table[j] = false;
            }
        }
    }

    for(int n=0; n<=N; n++) {
        answers[n] = isprime(n*n + n + 41);
    }

    int a, b;
    while(cin >> a >> b) {
        int c = count(answers+a, answers+b+1, true);
        printf("%.2lf\n", (double)c / (double)(b-a+1) * 100.0);
    }

    return 0;
}
