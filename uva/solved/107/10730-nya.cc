/*
 * UVA 10730 Antiarithmetic?
 * 2005-02-02
 * by nya
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

using namespace std;

inline int sgn(int n)
{
    if (n != 0)
        return n/abs(n);
    return 0;
}


int main(int argc, char** argv)
{
    while(true) {
        int n;
        cin >> n;
        if (n == 0) break;
        {
            char c;
            cin >> c;
        }

        int seq[n];
        int map[n];
        fill(seq, seq+n, -1);
        fill(map, map+n, -1);

        for(int i=0; i<n; i++) {
            int t;
            cin >> t;
            seq[i] = t;
            map[t] = i;
        }

        bool found = false;

        for(int m=0; m<n; m++) {
            for(int d=-1; m+d*2>=0; d--) {
                if (sgn(map[m+d*2]-map[m+d])*sgn(map[m+d]-map[m]) > 0) {
                    found = true;
                    goto OUT;
                }
            }
            for(int d=1; m+d*2<n; d++) {
                if (sgn(map[m+d*2]-map[m+d])*sgn(map[m+d]-map[m]) > 0) {
                    found = true;
                    goto OUT;
                }
            }
        }

    OUT:
        cout << (found ? "no" : "yes") << endl;
    }
    return 0;
}
