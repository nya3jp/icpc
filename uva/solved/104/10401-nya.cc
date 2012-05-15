/*
 * UVA 10401 Injured Queen Problem
 * 2005-08-08
 * by nya
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cassert>

#define N 15

int main() {
    std::string line;
    while(std::cin >> line) {
        int n = line.size();
        std::vector<int> v(n);
        for(int i=0; i<n; i++) {
            char c = line[i];
            if ('1' <= c && c <= '9') {
                v[i] = (int)(c - '1');
            }
            else if ('A' <= c && c <= 'F') {
                v[i] = (int)(c - 'A') + 9;
            }
            else if (c == '?') {
                v[i] = -1;
            }
            else {
                assert(false);
            }
            std::cerr << v[i] << std::endl;
        }

        std::vector< std::vector<long long int> > dpt;
        dpt.resize(n);
        for(int i=0; i<n; i++)
            dpt[i].resize(n, 0);

        for(int y=0; y<n; y++) {
            for(int x=0; x<n; x++) {
                if (v[y] < 0 || x == v[y]) {
                    long long int& m = dpt[y][x];
                    if (y == 0) {
                        m = 1;
                    }
                    else {
                        for(int px=0; px<n; px++) {
                            if (!(x-1 <= px && px <= x+1)) {
                                long long int& pm = dpt[y-1][px];
                                m += pm;
                            }
                        }
                    }
                }
            }
        }

        long long int r = 0;
        for(int x=0; x<n; x++) {
            r += dpt[n-1][x];
        }
        std::cout << r << std::endl;
    }
    return 0;
}




