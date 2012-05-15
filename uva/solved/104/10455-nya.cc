/*
 * UVA 10455 Gray Code
 * 2005-08-23
 * by nya
 */

#define NDEBUG

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#define N 6

unsigned long long int g[N+1];


void generate_graycode(std::vector<bool>& bits, std::vector<int>& order, unsigned long long int index, int n) {
    if (n == 0) {
        for(int i=0; i<(int)bits.size(); i++) {
            std::cout << (bits[i] ? '1' : '0');
        }
        std::cout << std::endl;
    }
    else {
        assert(0 <= index && index < g[n]);
        int second = index % g[n-1];
        int first = index / g[n-1] % g[n-1];
        int rpos = index / g[n-1] / g[n-1];
#ifndef NDEBUG
        std::cerr << "n=" << n << ": (p,f,s) = (" << rpos << "," << first << "," << second << ")" << std::endl;
#endif
        int pos = order[rpos];
        std::rotate(order.begin()+rpos, order.begin()+rpos+1, order.begin()+n);
        generate_graycode(bits, order, first, n-1);
        bits[pos] = !bits[pos];
        generate_graycode(bits, order, second, n-1);
        std::rotate(order.begin()+rpos, order.begin()+n-1, order.begin()+n);
    }
}


int main() {

    g[0] = g[1] = 1;
    for(int n=2; n<=N; n++) {
        g[n] = g[n-1]*g[n-1]*n;
    }

#ifndef NDEBUG
    for(int n=1; n<=N; n++) {
        std::cerr << "g(" << n << ") = " << g[n] << std::endl;
    }
#endif

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {
        std::string bits_string;
        unsigned long long int index;
        std::cin >> bits_string >> index;
        index--;
        int n = (int)bits_string.size();
        std::vector<bool> bits(n);
        for(int i=0; i<n; i++)
            bits[i] = (bits_string[i] == '1');
        std::vector<int> order(n);
        for(int i=0; i<n; i++)
            order[i] = i;
        if (iCase > 0)
            std::cout << std::endl;
        generate_graycode(bits, order, index, n);
    }

    return 0;
}
