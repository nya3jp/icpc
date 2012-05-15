#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        int m;
        cin >> m;

        vector< pair<int,int> > v;
        while(true) {
            int a, b;
            cin >> a >> b;
            if (a == 0 && b == 0)
                break;
            v.push_back(make_pair(a, b));
        }
        v.push_back(make_pair(m+1, m+1));
        int n = v.size();

        sort(v.begin(), v.end());

        vector< pair<int,int> > u;
        int right = 0;
        pair<int,int> next(-1, -1);
        for(int i = 0; i < n; i++) {
            pair<int,int>& range = v[i];
            if (range.first > right) {
                if (next.second <= right) {
                    u.clear();
                    break;
                }
                u.push_back(next);
                right = next.second;
                if (right >= m)
                    break;
                next = make_pair(-1, -1);
            }
            if (range.second > next.second)
                next = range;
        }
        if (right < m)
            u.clear();

        if (iCase > 0)
            cout << endl;
        cout << (int)u.size() << endl;
        for(int i = 0; i < (int)u.size(); i++)
            cout << u[i].first << ' ' << u[i].second <<endl;

    }


    return 0;
}
