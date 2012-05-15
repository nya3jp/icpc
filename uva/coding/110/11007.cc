#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

/*        19 18
 *        17 16
 *  22 20 00 01 09 11
 *  23 21 02 03 08 10
 *        04 05
 *        06 07
 *        12 13
 *        14 15
 */

struct state {
    int x[24];
};
typedef unsigned long long int stateI;

bool operator<(const state& a, const state& b) {
    return lexicographical_compare(a.x, a.x+24, b.x, b.x+24);
}

void rotateX(state& s) {
    swap(s.x[22], s.x[0]);
    swap(s.x[20], s.x[1]);
    swap(s.x[0], s.x[9]);
    swap(s.x[1], s.x[11]);
    swap(s.x[9], s.x[15]);
    swap(s.x[11], s.x[14]);
    swap(s.x[16], s.x[18]);
    swap(s.x[18], s.x[19]);
    swap(s.x[19], s.x[17]);
}
void rotateY(state& s) {
    swap(s.x[19], s.x[0]);
    swap(s.x[17], s.x[2]);
    swap(s.x[0], s.x[4]);
    swap(s.x[2], s.x[6]);
    swap(s.x[4], s.x[12]);
    swap(s.x[6], s.x[14]);
    swap(s.x[20], s.x[21]);
    swap(s.x[21], s.x[23]);
    swap(s.x[23], s.x[22]);
}
void rotateZ(state& s) {
    swap(s.x[4], s.x[8]);
    swap(s.x[5], s.x[9]);
    swap(s.x[8], s.x[16]);
    swap(s.x[9], s.x[17]);
    swap(s.x[16], s.x[20]);
    swap(s.x[17], s.x[21]);
    swap(s.x[2], s.x[3]);
    swap(s.x[3], s.x[1]);
    swap(s.x[1], s.x[0]);
}
state normalize(const state& s) {
    state t = s;
    
}
state fromInt(stateI repr) {
    state s;
    REP(i, 24) {
        s.x[24-i-1] = repr%6;
        repr /= 6;
    }
    return s;
}
stateI toInt(const state& s) {
    state t = normailze(s);
    stateI repr = 0;
    REP(i, 24)
        repr = repr * 6 + t.x[i];
    return repr;
}

bool isAccepted(const state& s) {
    int c = 0;
    REP(i, 6) {
        int j = i*4;
        if (s.x[j] == s.x[j+1] && s.x[j] == s.x[j+2] && s.x[j] == s.x[j+3])
            c++;
    }
    return (c == 6);
}

void solve() {
    state init;
    map<char,int> mp;
    REP(i, 6) {
        string s;
        cin >> s;
        REP(j, 4) {
            char c = s[j];
            if (mp.count(c) == 0)
                mp.insert(make_pair(c,mp.size()));
            init.x[i*4+j] = mp[s[j]];
        }
    }

    int res;
    map<stateI,int> costs;
    costs[toInt(init)] = 0;
    queue<stateI> q;
    q.push(toInt(init));
    for(;;) {
        assert(!q.empty());
        stateI si = q.front();
        state s = fromInt(si);
        q.pop();
        int c = costs[si];

        if (isAccepted(s)) {
            res = c;
            break;
        }

        rotateX(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateX(s);rotateX(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateX(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateY(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateY(s);rotateY(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateY(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateZ(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateZ(s);rotateZ(s);
        si = toInt(s);
        if (costs.count(si) == 0)
            costs[si] = c+1, q.push(si);

        rotateZ(s);

    }

    cout << res << endl;

}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
