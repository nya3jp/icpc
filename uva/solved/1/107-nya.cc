/*
 * UVA 107 The Cat in the Hat
 * 2005-07-21
 * by nya
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>

#define PRIME_MAX 65536

std::vector<unsigned int> primes;

void init_prime() {
    std::vector<bool> isprime(PRIME_MAX+1, true);
    for(unsigned int i=2; i<=PRIME_MAX; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            for(unsigned int j=i*i; j<=PRIME_MAX; j+=i) {
                isprime[j] = false;
            }
        }
    }
}

unsigned int gcd(unsigned int n, unsigned int m) {
    unsigned int r;
    while( (r = n%m) != 0 ) {
        n = m;
        m = r;
    }
    return m;
}

std::vector<unsigned int> divs(unsigned int n) {
    std::vector<unsigned int> v;
    for(unsigned int m=1; m*m<=n; m++) {
        if (n%m == 0)
            v.push_back(m);
    }
    std::vector<unsigned int> u(v);
    std::reverse(u.begin(), u.end());
    if (v.back()*v.back() == n)
        v.pop_back();
    std::transform(u.begin(), u.end(), std::back_inserter(v), std::bind1st(std::divides<unsigned int>(), n));
    return v;
}

std::vector< std::pair<unsigned int, int> > roots(unsigned int n) {
    assert(n > 1);
    std::vector< std::pair<unsigned int, int> > v;
    for(int i=0; i<(int)primes.size() && n != 1; i++) {
        int p = primes[i];
        int m = 0;
        while(n % p == 0) {
            n /= p;
            m++;
        }
        if (m > 0) {
            v.push_back( std::make_pair(p, m) );
        }
    }
    if (n != 1) {
        v.push_back( std::make_pair(n, 1) );
    }
    int g = v[0].second;
    for(int i=1; i<(int)v.size(); i++) {
        g = gcd(g, v[i].second);
    }

    std::vector<unsigned int> ml = divs(g);

    unsigned int base = 1;
    for(int i=0; i<(int)v.size(); i++) {
        const std::pair<unsigned int, int>& pair = v[i];
        for(int j=0; j<pair.second/g; j++) {
            base *= pair.first;
        }
    }

    std::vector< std::pair<unsigned int, int> > rts;
    assert(ml[0] == 1);
    rts.push_back( std::make_pair(base, g) );
    unsigned int cur = base;
    for(int i=1; i<(int)ml.size(); i++) {
        int k = ml[i] - ml[i-1];
        for(int j=0; j<k; j++)
            cur *= base;
        rts.push_back( std::make_pair(cur, g/ml[i]) );
    }
    return rts;
}


unsigned int pow(unsigned int n, int m) {
    unsigned int r = 1;
    for(int i=0; i<m; i++)
        r *= n;
    return r;
}

// H(0) = 1
// H(h) = H(h-1)*n + (n+1)^h

unsigned int sum1(unsigned int n, int h) {
    unsigned int s = 0;
    unsigned int t = 1;
    for(int i=0; i<h; i++) {
        s += t;
        t *= n;
    }
    return s;
}

unsigned int sum2(unsigned int n, int h) {
    unsigned int s = 1;
    for(int i=1; i<=h; i++) {
        s = s*n + pow(n+1, i);
    }
    return s;
}


std::pair<unsigned int, int> find_nh(unsigned int a, unsigned int b) {
    if (b == 1) {
        unsigned int n = 1;
        int h = 0;
        unsigned int t = a;
        while(t > 1) {
            h++;
            t >>= 1;
        }
        return std::make_pair(n, h);
    }
    else {
        std::vector< std::pair<unsigned int, int> > rts = roots(b);

        for(int i=0; i<(int)rts.size(); i++) {
            std::cerr << "(n,h) = (" << rts[i].first << "," << rts[i].second << ")" << std::endl;
            if (a == pow(rts[i].first+1, rts[i].second)) {
                unsigned int n = rts[i].first;
                int h = rts[i].second;
                return std::make_pair(n, h);
            }
        }
    }
    assert(false);
    return std::make_pair(0, 0);
}


int main() {

    init_prime();

    unsigned int a, b;
    while(std::cin >> a >> b && !(a == 0 && b == 0)) {

        std::pair<unsigned int, int> pair = find_nh(a, b);
        unsigned int n = pair.first;
        int h = pair.second;
        std::cout << sum1(n, h) << ' ' << sum2(n, h) << std::endl;

    }

    return 0;
}



