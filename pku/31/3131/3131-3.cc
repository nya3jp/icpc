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

const int ADJ[6][2] = {
    {3, 5},
    {4, 2},
    {5, 1},
    {0, 4},
    {1, 3},
    {2, 0},
};

typedef int State;

template<class T, int N=1000000>
struct nyaq {
    T* data;
    int begin, end;
    nyaq() : data(new T[N]), begin(0), end(0) {
    }
    virtual ~nyaq() {
        while(!empty())
            pop();
        delete[] data;
    }
    inline void clear() {
        begin = end = 0;
    }
    inline bool empty() const {
        return (begin == end);
    }
    inline const T& front() const {
        return data[begin];
    }
    inline void pop() {
        begin++;
        if (begin == N)
            begin = 0;
    }
    inline void push(const T& value) {
        data[end++] = value;
        if (end == N)
            end = 0;
    }
};

State toright(State state) {
    const int here = state>>27;
    if (here%3 == 2)
        return -1;
    const int there = here+1;
    const int dir = 0;
    const int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State toleft(State state) {
    const int here = state>>27;
    if (here%3 == 0)
        return -1;
    const int there = here-1;
    const int dir = 0;
    const int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State toup(State state) {
    const int here = state>>27;
    if (here/3 == 0)
        return -1;
    const int there = here-3;
    const int dir = 1;
    const int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State todown(State state) {
    const int here = state>>27;
    if (here/3 == 2)
        return -1;
    const int there = here+3;
    const int dir = 1;
    const int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}

State (*MOVES[4])(State) = {toleft, toright, toup, todown};

#define TAIL 11
#define STATE_SIZE (6*6*6*6*6*6*6*6*9)

char dists[STATE_SIZE];
#define FLAG 0x20

inline int encode(const State s) {
    const int empty = s>>27;
    int code = 0;
    REP(i, 9) {
        if (i != empty)
            code = code * 6 + ((s>>(3*i))&7);
    }
    code = code * 9 + empty;
    return code;
}

nyaq<State> q;


int make_dists(State startState, State goalState) {

    REP(i, STATE_SIZE)
        dists[i] = -1;

    //queue<State> q;
    q.clear();
    q.push(startState);

    dists[encode(startState)] = FLAG;
    if ((startState&~0111111111) == goalState)
        return 0;

    while(!q.empty()) {
        State state = q.front();
        q.pop();

        int code = encode(state);

        REP(dir, 4) {
            State newState = MOVES[dir](state);
            int newCode = encode(newState);
            if (newState != -1 && dists[newCode] < 0) {
                dists[newCode] = dists[code] + 1;
                if ((dists[newCode]&~FLAG) < 30-TAIL)
                    q.push(newState);
                if ((newState&~0111111111) == goalState)
                    return (dists[newCode] & ~FLAG);
            }
        }
    }

    return -1;
}

int solve(State goalState) {

    //queue<State> q;
    q.clear();

    int res = 10000;

    REP(p, 1<<8) {
        int t = p;
        State g = goalState;
        int empty = g >> 27;
        REP(i, 9) {
            if (i != empty) {
                g |= (t&1) << (3*i);
                t >>= 1;
            }
        }
        int code = encode(g);
        q.push(g);
        if (dists[code] != -1 && (dists[code]&FLAG) != 0) {
            int tt = (dists[code] & ~FLAG);
            if (tt < res)
                res = tt;
        }
        dists[code] = 0;
    }

    while(!q.empty()) {
        State state = q.front();
        q.pop();

        int code = encode(state);

        int newLen = dists[code] + 1;

        REP(dir, 4) {
            State newState = MOVES[dir](state);
            int newCode = encode(newState);
            if (newState != -1) {
                if (dists[newCode] < 0) {
                    dists[newCode] = newLen;
                    if (newLen < TAIL && res > 30)
                        q.push(newState);
                }
                else if ((dists[newCode] & FLAG) != 0) {
                    int t = (dists[newCode] & ~FLAG) + newLen;
                    if (t < res)
                        res = t;
                }
            }
        }
    }

    if (res > 30)
        res = -1;
    return res;
}

int main() {

    // May fate be with you!

    for(;;) {

        int x, y;
        cin >> x >> y;

        if (x == 0 && y == 0)
            break;
        x--; y--;

        State startState = (y*3+x)<<27;

        State goalState = 0;
        REP(i, 9) {
            char c;
            cin >> c;
            switch(c) {
            case 'E':
                goalState |= i << 27;
                break;
            case 'W':
                goalState |= 0 << (3*i);
                break;
            case 'B':
                goalState |= 2 << (3*i);
                break;
            case 'R':
                goalState |= 4 << (3*i);
                break;
            }
        }

        int res;
        res = make_dists(startState, goalState);
        if (res < 0)
            res = solve(goalState);
        cout << res << endl;

    }

    return 0;
}



// Powered by fate testarossa
