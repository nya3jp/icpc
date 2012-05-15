/*
 * UVA 10466 How Far?
 * 2005-07-30
 * by nya
 */

#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>

typedef long long int integer;
typedef long double decimal;
typedef std::complex<decimal> dcomplex;
const decimal PI2 = std::acos((decimal)0)*4;

int main() {
    integer nBodies, iTime;
    while(std::cin >> nBodies >> iTime) {
        std::vector< std::pair<integer,integer> > data(nBodies);
        for(int i=0; i<nBodies; i++) {
            std::cin >> data[i].first >> data[i].second;
        }
        std::vector<dcomplex> bodies(nBodies);
        for(int i=0; i<nBodies; i++) {
            bodies[i] = std::polar<decimal>(data[i].first, PI2*(iTime%data[i].second)/data[i].second);
            if (i > 0)
                bodies[i] += bodies[i-1];
            if (i > 0)
                std::printf(" ");
            std::printf("%.04f", (double)std::abs(bodies[i]));
        }
        std::printf("\n");
    }
    return 0;
}
