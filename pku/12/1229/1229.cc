#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

struct part_t {
    string str;
    string special;
};

vector<part_t> split_parse(string s) {
    istringstream is(s);
    string t;

    vector<part_t> res;
    while(getline(is, t, '.')) {
        if (t == "*") {
            res.push_back((part_t){"", "+"});
        }
        else if (t == "?") {
            res.push_back((part_t){"", "."});
            res.push_back((part_t){"", "?"});
            res.push_back((part_t){"", "?"});
        }
        else if (t == "!") {
            res.push_back((part_t){"", "."});
            res.push_back((part_t){"", "."});
            res.push_back((part_t){"", "+"});
        }
        else {
            res.push_back((part_t){t, ""});
        }
    }
    res.push_back((part_t){"", "$"});

    return res;
}

bool solve(vector<part_t>& first, vector<part_t>& second) {
    int n = first.size(), m = second.size();

    vector< vector<int> > memo(n+1, vector<int>(m+1, false));

    for(int i = n-1; i >= 0; i--) {
        for(int j = m-1; j >= 0; j--) {
            part_t& a = first[i];
            part_t& b = second[j];
            int& res = memo[i][j];
            if (a.special == "$" || b.special == "$") {
                res = (a.special == b.special);
            }
            else if (a.special == "?") {
                res = (memo[i+1][j] || memo[i+1][j+1]);
                if (b.special == "?")
                    res = res || memo[i][j+1];
            }
            else if (a.special == ".") {
                res = memo[i+1][j+1];
                if (b.special == "?")
                    res = res || memo[i][j+1];
                if (b.special == "+")
                    res = res || memo[i+1][j];
            }
            else if (a.special == "+") {
                res = memo[i][j+1] || memo[i+1][j+1];
                if (b.special == "+")
                    res = res || memo[i+1][j];
            }
            else if (a.special == "") {
                res = ((a.str == b.str) && memo[i+1][j+1]);
                if (b.special == ".")
                    res = res || memo[i+1][j+1];
                if (b.special == "?")
                    res = res || memo[i][j+1] || memo[i+1][j+1];
                if (b.special == "+")
                    res = res || memo[i+1][j+1] || memo[i+1][j];
            }
        }
    }

    return memo[0][0];
}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        string s;
        cin >> s;
        vector<part_t> first = split_parse(s);
        cin >> s;
        vector<part_t> second = split_parse(s);

        cout << (solve(first, second) ? "YES" : "NO") << endl;

    }

    return 0;
}

