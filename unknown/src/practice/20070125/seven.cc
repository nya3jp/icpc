#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <deque>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        int num, denom, from, to;
        cin >> num >> denom >> from >> to;

        printf("Problem set %d: %d / %d, base 7 digits %d through %d: ", iCase+1, num, denom, from, to);

        num %= denom;

        REP(i, from)
            num = num*7%denom;

        REP(i, to-from+1) {
            num *= 7;
            int digit = num / denom;
            printf("%d", digit);
            num %= denom;
        }
        printf("\n");

    }


    return 0;
}
