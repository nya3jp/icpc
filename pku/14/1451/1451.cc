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
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

const char* KEYS[] = {
    "",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

struct trie_t {
    char c;
    int freq;
    trie_t* parent;
    map<char, trie_t*> children;

    trie_t(char c = 0, trie_t* parent = 0) : c(c), freq(0), parent(parent) {
    }
    ~trie_t() {
        FOR(it, children)
            delete it->second;
    }
    void insert(const char* w, int freq) {
        this->freq += freq;
        if (*w)
            descend(*w)->insert(w+1, freq);
    }
    trie_t* descend(char c) {
        if (children.count(c) == 0)
            children[c] = new trie_t(c, this);
        return children[c];
    }
    void print() {
        if (c) {
            parent->print();
            cout << c;
        }
    }
};

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {

        cout << "Scenario #" << iCase+1 << ":" << endl;

        trie_t root;

        int nDic;
        cin >> nDic;
        REP(i, nDic) {
            string word;
            int freq;
            cin >> word >> freq;
            root.insert(word.c_str(), freq);
        }

        int nQ;
        cin >> nQ;

        REP(iQ, nQ) {
            string q;
            cin >> q;
            vector<trie_t*> currents(1, &root);
            REP(pos, q.size()) {
                int d = (int)(q[pos] - '0');
                if (d == 1)
                    break;
                vector<trie_t*> nexts;
                for(const char* pc = KEYS[d]; *pc; pc++) {
                    char c = *pc;
                    REP(i, currents.size()) {
                        trie_t& here = *currents[i];
                        if (here.children.count(c) > 0)
                            nexts.push_back(here.children[c]);
                    }
                }
                currents.swap(nexts);
                if (currents.empty()) {
                    cout << "MANUALLY" << endl;
                }
                else {
                    int best = 0;
                    REP(i, currents.size()) {
                        trie_t& a = *currents[best];
                        trie_t& b = *currents[i];
                        if (b.freq > a.freq)
                            best = i;
                    }
                    currents[best]->print();
                    cout << endl;
                }
            }
            cout << endl;
        }
        cout << endl;

    }

    return 0;
}
