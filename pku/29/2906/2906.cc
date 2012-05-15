#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int n, w;
        cin >> n >> w;
        w /= 2;

        vector< vector<int> > schedule(100);
        REP(i, n) {
            int from, to;
            cin >> from >> to;
            from--; to--;
            schedule[from].push_back(to);
        }

        bool fine;
        {
            priority_queue<int, vector<int>, greater<int> > q;
            REP(day, 100) {
                REP(i, schedule[day].size())
                    q.push(schedule[day][i]);
                if (day%7 >= 5)
                    continue;
                REP(i, w) {
                    if (q.empty())
                        break;
                    if (q.top() < day)
                        break;
                    q.pop();
                }
            }
            fine = q.empty();
        }

        bool feasible;
        {
            priority_queue<int, vector<int>, greater<int> > q;
            REP(day, 100) {
                REP(i, schedule[day].size())
                    q.push(schedule[day][i]);
                REP(i, w) {
                    if (q.empty())
                        break;
                    if (q.top() < day)
                        break;
                    q.pop();
                }
            }
            feasible = q.empty();
        }

        if (fine)
            cout << "fine" << endl;
        else if (feasible)
            cout << "weekend work" << endl;
        else
            cout << "serious trouble" << endl;
    }

    return 0;
}
