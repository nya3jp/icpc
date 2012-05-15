/*
 * UVA 10402 Triangle Covering
 * 2005-09-25
 * by nya
 */

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>

typedef long double decimal;

const decimal PI = std::acos((decimal)0)*2;
const decimal DU = PI/180;
const decimal EP = 1.0e-18;

#define EQ(x,y) ( std::abs((x)-(y)) < EP )

template<class Fn>
decimal binary_search(Fn f, decimal lower, decimal upper) {
    while(upper-lower > EP) {
        decimal middle = (lower+upper)/2;
        (f(middle) ? upper : lower) = middle;
    }
    return (upper+lower)/2;
}

bool f1(decimal th) {
    return ( std::sqrt((decimal)3)/std::cos(DU*60-th) < (1/std::cos(th) + 1/std::cos(DU*30-th)) );
}

bool f2(decimal th) {
    /*
     * Judge's solution is wrong...
     * see http://online-judge.uva.es/board/viewtopic.php?t=4125
     */
    //return ( 1 - (1 - std::tan(DU*30))*std::tan(DU*30-th) > (1 - std::tan(th))/std::cos(th) ); // This one is correct
    return ( 1 - (1 - std::tan(DU*30))*std::tan(DU*30-th) > (1 - std::sin(th))/std::cos(th) );
}

int main() {

    decimal ratio2, ratio3, ratio4, ratio6;

    { // ratio2
        ratio2 = (std::tan(DU*15)+1)/std::cos(DU*15);
    }

    { // ratio3
        decimal th = binary_search(f1, DU*15, DU*30);
        ratio3 = std::sqrt((decimal)3) / std::cos(DU*60 - th);
    }

    { // ratio4
        ratio4 = 4 / std::sqrt((decimal)3);
        //ratio4 = 1 + ratio2;
        assert(ratio2+1 > ratio4);
    }

    { // ratio6
        decimal th = binary_search(f2, DU*0, DU*15);
        ratio6 = 1 + 1/std::cos(th) + 1/std::cos(DU*30);
    }

    int n;
    std::scanf("%d", &n);
    for(int i=0; i<n; i++) {
        decimal r;
        std::scanf("%Lf", &r);
        std::printf("%.10Lf %.10Lf %.10Lf %.10Lf\n",
                    ratio2*r,
                    ratio3*r,
                    ratio4*r,
                    ratio6*r);
    }

    return 0;
}
