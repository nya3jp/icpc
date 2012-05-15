#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

vector<int> res[110];

template<class T>
ostream& operator<<(ostream& s, const vector<T>& v) {
    REP(i, v.size()-1)
        s << v[i] << ' ';
    s << v.back();
    return s;
}

void iddfs(vector<int>& v, int limit) {
    if (v.back() > 100)
        return;
    //cout << "iddfs " << v << endl;
    if (res[v.back()].empty())
        res[v.back()] = v;
    if ((int)v.size() >= limit)
        return;

    int n = v.size();
    //set<int> s;
    vector<int> t(110, false);
    REP(i, n) REP(j, n) if (i <= j) {
        int x = v[i] + v[j];
        if (x <= 100 && x > v.back() && !t[x]/*s.insert(x).second*/) {
            t[x] = true;
            v.push_back(x);
            iddfs(v, limit);
            v.pop_back();
        }
    }
}

int main() {

    vector<int> v(1, 1);
    for(int limit = 1; limit <= 10; limit++) {
        //cout << limit << endl;
        iddfs(v, limit);
    }

    int n;
    while(cin >> n && n > 0) {
        cout << res[n] << endl;
    }

    return 0;
}
