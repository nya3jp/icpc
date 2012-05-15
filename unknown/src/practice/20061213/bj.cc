#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

void decompose(vector<string>& v, string s) {
    v.clear();
    int n = s.size();
    REP(i, n) {
        for(int len = 1; i+len <= n; len++) {
            v.push_back(s.substr(i, len));
        }
    }
}

bool hoge(const string& a, const string& b) {
    return make_pair(-a.size(), a) < make_pair(-b.size(), b);
}

void solve() {
    int n;
    cin >> n;
    vector<string> inter;

    {
        string s;
        cin >> s;
        decompose(inter, s);
    }

    REP(i, n-1) {
        vector<string> inter2;
        string s;
        cin >> s;
        decompose(inter2, s);
        sort(ALLOF(inter));
        sort(ALLOF(inter2));
        inter.erase(set_intersection(ALLOF(inter), ALLOF(inter2), inter.begin()), inter.end());
    }

    sort(ALLOF(inter), hoge);
    string res = (inter.empty() ? "" : inter.front());

    if (res.size() <= 2) {
        cout << "no significant commonalities" << endl;
    }
    else {
        cout << res << endl;
    }

}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
