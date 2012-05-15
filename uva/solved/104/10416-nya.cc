/*
 * UVA 10416 Folding My T-Shirt
 * 2005-07-28
 * by nya
 */

#include <iostream>
#include <complex>
#include <algorithm>
#include <deque>
#include <cmath>
#include <cassert>

typedef long long int integer;

typedef std::complex<integer> icomplex;

const icomplex II = icomplex(0, 1);

inline int mod_inc(int i, int n) {
    return (i+1)%n;
}
inline int mod_dec(int i, int n) {
    return (i+n-1)%n;
}

template<class T>
T inner_product(const std::complex<T>& a, const std::complex<T>& b) {
    return (a.real()*b.real() + a.imag()*b.imag());
}

template<class T>
T outer_product(const std::complex<T>& a, const std::complex<T>& b) {
    return (a.real()*b.imag() - a.imag()*b.real());
}



bool check_symmetricity(int iPointInc,
                        int iPointDec,
                        int nPoints,
                        const std::deque<icomplex>& points,
                        icomplex base,
                        icomplex delta)
{
    int nCheckPoints = (nPoints+1)/2;

    for(int i=0; i<nCheckPoints; i++) {

        //std::cerr << "check: " << iPointInc << " and " << iPointDec << std::endl;

        icomplex a = points[iPointInc];
        icomplex b = points[iPointDec];

        if (!( inner_product( b-a, delta ) == 0 &&
               outer_product( (a+b) / 2ll - base, delta ) == 0 )) {
            return false;
        }

        iPointInc = mod_inc(iPointInc, nPoints);
        iPointDec = mod_dec(iPointDec, nPoints);
    }

    return true;
}



int main()
{

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int nPoints;
        std::cin >> nPoints;

        std::deque<icomplex> points;
        for(int i=0; i<nPoints; i++) {
            integer x, y;
            std::cin >> x >> y;
            assert(x*x <= 100000000 && y*y <= 100000000);
            x *= 2;
            y *= 2;
            points.push_back( icomplex(x, y) );
        }

        bool bSymmetric = false;

        for(int iBasePoint=0; iBasePoint<nPoints && !bSymmetric; iBasePoint++) {

            icomplex current = points[iBasePoint];
            icomplex prev = points[mod_dec(iBasePoint, nPoints)];
            icomplex next = points[mod_inc(iBasePoint, nPoints)];

            if (! bSymmetric &&
                std::norm(prev-current) == std::norm(next-current)) {

                //std::cerr << "a)" << std::endl;

                icomplex base = current;
                icomplex delta;
                if (next+prev == current*2ll) {
                    delta = (next-current)*II;
                }
                else {
                    delta = next+prev - current*2ll;
                }

                bSymmetric =
                    check_symmetricity(mod_inc(iBasePoint, nPoints),
                                       mod_dec(iBasePoint, nPoints),
                                       nPoints,
                                       points,
                                       base,
                                       delta);

            }

            if (! bSymmetric) {

                //std::cerr << "b)" << std::endl;

                icomplex base = (current + next) / 2ll;
                icomplex delta = (next - current)*II;

                bSymmetric =
                    check_symmetricity(mod_inc(iBasePoint, nPoints),
                                       iBasePoint,
                                       nPoints,
                                       points,
                                       base,
                                       delta);

            }

            //std::cerr << iBasePoint << ": " << bSymmetric << std::endl;

        }

        std::cout << (bSymmetric ? "Yes" : "No") << std::endl;

    }
    return 0;
}
