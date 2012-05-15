#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) (c).begin(), (c).end()

struct trie_t {
    set<int> okay;
    map<char, trie_t*> children;
    ~trie_t() {
        FOR(it, children)
            delete it->second;
    }
};

struct trie_descend {
    int k;
    trie_descend(int k) : k(k) {
    }
    trie_t* operator()(trie_t* here, char c) {
        trie_t*& child = here->children[c];
        if (!child)
            child = new trie_t();
        child->okay.insert(k);
        return child;
    }
};

int traverse(trie_t* here, int n) {
    int res = -1;
    if ((int)here->okay.size() == n)
        res = 0;
    FOR(it, here->children) {
        int t = traverse(it->second, n);
        if (t >= 0)
            res >?= t+1;
    }
    return res;
}


int main() {

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {

        trie_t* root = new trie_t();

        int n;
        cin >> n;

        REP(i, n) {
            string s;
            cin >> s;
            for(int offset = 0; offset < (int)s.size(); offset++) {
                accumulate(s.begin()+offset, s.end(), root, trie_descend(i));
                accumulate(s.rbegin()+offset, s.rend(), root, trie_descend(i));
            }
        }

        int res = traverse(root, n);
        if (res < 0)
            res = 0;

        cout << res << endl;

        delete root;

    }

    return 0;
}

