#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>
#include <fstream>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

ifstream fin("kickdown.in");

#define cin fin

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

void solve(string first, string second)
{
    int min = first.size() + second.size() - first.size() * 2;

    REP(iStart, (second.size() - first.size())) {
        bool isOk = true;
        REP (i, first.size()) {
            int firstIdx  = i;
            int secondIdx = iStart + i;

            int height = (first[firstIdx] - '0') + (second[secondIdx] - '0');
//            cout << height << ":" << idx << endl;
            if (height > 3) {
                isOk = false;
                break;
            }
        }

        if (isOk) {
            int left  = min(iStart, first.size());
            int right = max(iStart + first.size(), second.size() - first.size());
            min <?= right - left;
        }
    }

    cout << min << endl;
}

int
main(void)
{
    int nCases;
    cin >> nCases;
    while (nCases--) {
        string first;
        string second;
        cin >> first;
        cin >> second;

        if (first.size() > second.size()) {
            string tmp = second;
            second = first;
            first = tmp;
        }

        REP(i, first.size()) {
            second = string("0") + second + string("0");
        }

        solve(first, second);
    }
    return 0;
}
