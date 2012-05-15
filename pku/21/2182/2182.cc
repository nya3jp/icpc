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

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())



template<class T>
struct Treap {
    T value;
    int prio;
    Treap* ch[2];
    bool cached;
    int cache;
    Treap(const T& value) : value(value), prio(rand()), cached(false) {
        ch[0] = ch[1] = 0; // is this necessary?
    }
    Treap* insert(const T& newvalue) {
        if (!this)
            return new Treap(newvalue);
        if (newvalue == value)
            return this;
        int side = (newvalue < value ? 0 : 1);
        ch[side] = ch[side]->insert(newvalue);
        cached = false;
        return rotate(side);
    }
    Treap* rotate(int side) {
        if (ch[side] && ch[side]->prio > prio) {
            //cout << "rotating" << endl;
            Treap* rot = ch[side];
            this->ch[side] = rot->ch[side^1];
            rot->ch[side^1] = this;
            this->cached = rot->cached = false;
            return rot;
        }
        return this;
    }
    void clear() {
        if (this) {
            ch[0]->clear();
            ch[1]->clear();
            delete this;
        }
    }
    Treap* remove(const T& oldvalue) {
        if (!this)
            return this;
        if (value == oldvalue) {
            if (!ch[1]) {
                Treap* res = ch[0];
                delete this;
                return res;
            }
            pair<Treap*, Treap*> res = ch[1]->delete_min();
            res.first->ch[0] = this->ch[0];
            res.first->ch[1] = res.second;
            res.first->cached = false;
            delete this;
            return res.first->balance();
        }
        int side = (oldvalue < value ? 0 : 1);
        ch[side] = ch[side]->remove(oldvalue);
        cached = false;
        return this;
    }
    pair<Treap*, Treap*> delete_min() {
        cached = false;
        if (!ch[0])
            return make_pair(this, ch[1]);
        pair<Treap*, Treap*> res = ch[0]->delete_min();
        ch[0] = res.second;
        return make_pair(res.first, this);
    }
    inline int priority() {
        return (this ? prio : -1);
    }
    Treap* balance() {
        //cout << "balance: " << *this << endl;
        int side = (ch[0]->priority() > ch[1]->priority() ? 0 : 1);
        Treap* rot = rotate(side);
        if (rot == this)
            return this;
        return rot->balance();
    }
    int eval() {
        if (!this)
            return 0;
        if (!cached)
            cache = 1 + ch[0]->eval() + ch[1]->eval();
        cached = true;
        return cache;
    }
    Treap* order(int k) {
        if (!this)
            return 0;
        int l = ch[0]->eval();
        if (k < l)
            return ch[0]->order(k);
        if (k == l)
            return this;
        return ch[1]->order(k-(l+1));
    }
};


template<class T>
ostream& operator<<(ostream& os, const Treap<T>& t) {
    if (&t)
        cout << "([" << t.value << "," << t.prio << "] " << *t.ch[0] << " " << *t.ch[1] << ")";
    else
        cout << "()";
    return os;
}


vector<int> solve(const vector<int>& query) {
    int n = query.size();

    Treap<int>* treap = 0;
    for(int i = 1; i <= n; i++)
        treap = treap->insert(i);

    vector<int> res(n);
    for(int i = n-1; i >= 0; i--) {
        //cout << *treap << endl;
        Treap<int>* t = treap->order(query[i]);
        if (!t) {
            REP(j, n)
                cout << query[j] << " ";
            cout << endl;
            for(int j = i; j < n; j++)
                cout << res[j] << " ";
            cout << endl;
            exit(0);
        }
        res[i] = t->value;
        treap = treap->remove(res[i]);
    }

    return res;
}

int main() {

    while(0) {
        int n = 10;
        vector<int> seq(n);
        REP(i, n)
            seq[i] = i+1;
        REP(i, n) {
            int j = (rand()%(n-i))+i;
            swap(seq[i], seq[j]);
        }
        vector<int> query(n);
        REP(i, n) REP(j, i)
            if (seq[j] < seq[i])
                query[i]++;
        vector<int> res = solve(query);
        assert(res == seq);
    }

    int n;
    scanf("%d", &n);

    vector<int> query(n, 0);
    for(int i = 1; i < n; i++)
        scanf("%d", &query[i]);

    vector<int> res = solve(query);

    REP(i, n)
        printf("%d\n", res[i]);

    return 0;
}



