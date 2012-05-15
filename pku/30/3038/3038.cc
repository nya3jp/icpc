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
#define IN(i,l,u) ((l) <= (i) && (i) < (u))


struct Queue {
    int v[100], v2[200];
    int capacity, len, pos;
    Queue(int capcity) : capacity(capacity), len(0), pos(0) {
    }
    inline int size() const {
        return len;
    }
    void pop_front() {
        pos = (pos+1)%capacity;
        len--;
    }
    void insert(int p, int n, int a) {
        copy(v, v+capacity, v2);
        copy(v, v+capacity, v2+capacity);
        rotate(v2+pos+p, v2+pos+p+n, v2+pos+n+len);
        fill(v2+pos+p, v2+pos+p+n, a);
        copy(v2+pos, v2+capacity, v+pos);
        copy(v2+capacity, v2+capacity+pos, v);
        len += n;
        len <?= capacity;
    }
    inline int operator[](int index) {
        return v[(pos+index)%capacity];
    }
};

int main() {
    int nGroups, nPlaces, capacity;

    cin >> nGroups >> nPlaces >> capacity;

    typedef pair<int,int> range;
    vector< pair<range, int> > cows1, cows2;
    REP(i, nGroups) {
        int s, e, m;
        //cin >> s >> e >> m;
        scanf("%d%d%d", &s, &e, &m);
        s--; e--;
        if (s < e)
            cows1.push_back(make_pair(make_pair(s, e), m));
        if (e < s)
            cows2.push_back(make_pair(make_pair(nPlaces-s-1, nPlaces-e-1), m));
    }
    sort(ALLOF(cows1));
    sort(ALLOF(cows2));

    int res = 0;

    struct node {
        int end, n;
    };

    {
        vector< pair<range, int> >& cows = cows1;

        vector<int> cnt(nPlaces, 0);
        REP(i, cows.size())
            cnt[cows[i].first.first]++;

        node** table = new node*[nPlaces];
        REP(i, nPlaces)
            table[i] = new node[cnt[i]];

        vector<int> idx(nPlaces, 0);
        REP(i, cows.size())
            table[cows[i].first.first][idx[cows[i].first.first]++] = (node){cows[i].first.second, cows[i].second};

        deque<int> q;
        //Queue q(capacity);

        int iGroup = 0;
        int arrivals = 0;
        REP(iPlace, nPlaces) {

            while(arrivals < (int)q.size() && q[arrivals] == iPlace)
                arrivals++;

            /*
            while((int)q.size() > 0 && q[0] == iPlace)
                q.pop_front(), arrivals++;
            */

            while(iGroup < (int)cows.size() && cows[iGroup].first.first == iPlace) {
                int dest = cows[iGroup].first.second;
                int nCows = cows[iGroup].second;
                q.insert(lower_bound(q.begin()+arrivals, q.end(), dest), nCows, dest);
                /*
                int pos = 0;
                while(pos < (int)q.size() && !(q[pos] >= dest))
                    pos++;
                q.insert(pos, nCows, dest);
                */
                iGroup++;
            }
            /*
            node* nodes = table[iPlace];
            REP(i, cnt[iPlace]) {
                node& x = nodes[i];
                int dest = x.end;
                int nCows = x.n;
                int pos = 0;
                while(pos < (int)q.size() && !(q[pos] >= dest))
                    pos++;
                q.insert(pos, nCows, dest);
            }
            */
            if ((int)q.size() > arrivals+capacity)
                q.resize(arrivals+capacity);
        }

        res += arrivals;

    }

    {
        vector< pair<range, int> >& cows = cows2;

        vector<int> cnt(nPlaces, 0);
        REP(i, cows.size())
            cnt[cows[i].first.first]++;

        node** table = new node*[nPlaces];
        REP(i, nPlaces)
            table[i] = new node[cnt[i]];

        vector<int> idx(nPlaces, 0);
        REP(i, cows.size())
            table[cows[i].first.first][idx[cows[i].first.first]++] = (node){cows[i].first.second, cows[i].second};

        deque<int> q;
        //Queue q(capacity);

        int iGroup = 0;
        int arrivals = 0;
        REP(iPlace, nPlaces) {

            while(arrivals < (int)q.size() && q[arrivals] == iPlace)
                arrivals++;

            /*
            while((int)q.size() > 0 && q[0] == iPlace)
                q.pop_front(), arrivals++;
            */

            while(iGroup < (int)cows.size() && cows[iGroup].first.first == iPlace) {
                int dest = cows[iGroup].first.second;
                int nCows = cows[iGroup].second;
                q.insert(lower_bound(q.begin()+arrivals, q.end(), dest), nCows, dest);
                /*
                int pos = 0;
                while(pos < (int)q.size() && !(q[pos] >= dest))
                    pos++;
                q.insert(pos, nCows, dest);
                */
                iGroup++;
            }
            /*
            node* nodes = table[iPlace];
            REP(i, cnt[iPlace]) {
                node& x = nodes[i];
                int dest = x.end;
                int nCows = x.n;
                int pos = 0;
                while(pos < (int)q.size() && !(q[pos] >= dest))
                    pos++;
                q.insert(pos, nCows, dest);
            }
            */
            if ((int)q.size() > arrivals+capacity)
                q.resize(arrivals+capacity);
        }

        res += arrivals;

    }
    cout << res << endl;

    return 0;
}
