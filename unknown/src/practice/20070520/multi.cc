#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


string solve(int n, int k) {
    vector<int> res;
    int s = k;
    int c = 0;
    res.push_back(s);
    map<int, set<int> > mem;
    for(;;) {
        int m = s*n + c;
        s = m % 10;
        c = m / 10;
        if (s == k && c == 0)
            break;
        res.push_back(s);
        if (!mem[s].insert(c).second)
            return "0";
    }
    string str;
    REP(i, res.size())
        str.push_back((char)('0' + res[i]));
    reverse(str.begin(), str.end());
    if (str[0] == '0')
        return "0";
    return str;
}

int main() {

    int nCases;
    cin >> nCases;

    while(nCases-- > 0) {
        int n, k;
        cin >> n >> k;
        cout << solve(n,k) << endl;
    }

    return 0;
}

