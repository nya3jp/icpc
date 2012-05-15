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

#define INF 0x7fffffff

struct Solution {
    int cost;
    int next;
};

struct Trie {
    Trie* children[26];
    int id;

    Trie() {
        REP(i, 26)
            children[i] = 0;
        id = -1;
    }
    ~Trie() {
        REP(i, 26)
            if (children[i])
                delete children[i];
    }
};

Trie* descend_trie(Trie* here, int index) {
    Trie*& child = here->children[index];
    if (!child)
        child = new Trie();
    return child;
}

vector<string> dict;
string query;
vector<Solution> solutions;
vector<string> typings;
vector<int> costs;
Trie* trie = 0;

string rolltostring(int n) {
    char buf[16] = "";
    if (n != 0)
        sprintf(buf, "%c(%d)", (n > 0 ? 'U' : 'D'), abs(n));
    return buf;
}

string todigit(const string& s) {
    const int TABLE[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    string res;
    REP(i, s.size())
        res.push_back((char)('0'+TABLE[(int)(s[i]-'a')]));
    return res;
}

void init() {

    if (trie)
        delete trie;
    trie = new Trie();

    int n = dict.size();

    typings.resize(n);
    costs.resize(n);

    vector<string> digits(n);
    REP(i, n)
        digits[i] = todigit(dict[i]);

    map<string,int> conflicts;
    vector<int> indexes(n);
    REP(i, n)
        indexes[i] = conflicts[digits[i]]++;

    REP(i, n) {
        int confs = conflicts[digits[i]];
        int roll = indexes[i];
        if (confs - indexes[i] < indexes[i])
            roll = indexes[i] - confs;
        string typing = digits[i] + rolltostring(roll) + "R";
        typings[i] = typing;
        costs[i] = digits[i].size() + abs(roll) + 1;
    }

    REP(i, n) {
        const string& s = dict[i];
        Trie* here = trie;
        REP(j, s.size())
            here = descend_trie(here, (int)(s[j] - 'a'));
        here->id = i;
    }

    /*
    REP(i, n)
        cout << dict[i] << " " << digits[i] << " " << costs[i] << " " << typings[i] << endl;
    //*/
}

Solution& solve(int pos) {
    static Solution term = {0, -1};

    //fprintf(stderr, "solve(%d)\n", pos);

    int len = query.size();
    if (pos == len)
        return term;

    Solution& sol = solutions[pos];
    if (solutions[pos].next < 0) {
        sol.cost = INF;
        Trie* here = trie;
        for(int i = pos; i <= len && here; i++) {
            int iWord = here->id;
            if (iWord >= 0) {
                int c = costs[iWord] + solve(i).cost;
                if (c < sol.cost) {
                    sol.cost = c;
                    sol.next = iWord;
                }
            }
            if (i < len)
                here = here->children[(int)(query[i] - 'a')];
        }
    }

    return sol;
}

void solve() {
    int len = query.size();
    solutions.assign(len, (Solution){-1, -1});
    int pos = 0;

    string res;
    while(pos < len) {
        //fprintf(stderr, "at %d\n", pos);
        Solution sol = solve(pos);
        res += typings[sol.next];
        pos += dict[sol.next].size();
    }

    cout << res.substr(0, res.size()-1) << endl;
}


int main() {

    //freopen("sms.in", "r", stdin);

    for(;;) {

        int nDictWords;
        cin >> nDictWords;

        if (nDictWords == 0)
            break;

        dict.resize(nDictWords);
        REP(i, nDictWords)
            cin >> dict[i];

        init();

        int nQueries;
        cin >> nQueries;
        REP(i, nQueries) {
            cin >> query;
            solve();
        }

    }

    return 0;
}
