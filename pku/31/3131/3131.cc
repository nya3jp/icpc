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

template<class T, int N>
struct nyaq {
    T* data;
    int pos, n;
    nyaq() : data(new T[N]), n(0) {
    }
    virtual ~nyaq() {
        while(!empty())
            pop();
        delete[] data;
    }
    inline bool empty() const {
        return (n == 0);
    }
    inline const T& front() const {
        return data[pos];
    }
    inline void pop() {
        n--;
        pos++;
        if (pos == N)
            pos = 0;
    }
    inline void push(const T& value) {
        data[(pos+n)%N] = value;
        n++;
    }
};

State toright(State state) {
    int here = state>>27;
    if (here%3 == 2)
        return -1;
    int there = here+1;
    int dir = 0;
    int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State toleft(State state) {
    int here = state>>27;
    if (here%3 == 0)
        return -1;
    int there = here-1;
    int dir = 0;
    int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State toup(State state) {
    int here = state>>27;
    if (here/3 == 0)
        return -1;
    int there = here-3;
    int dir = 1;
    int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}
State todown(State state) {
    int here = state>>27;
    if (here/3 == 2)
        return -1;
    int there = here+3;
    int dir = 1;
    int mask = (7<<(3*here)) | (7<<(3*there));
    state = (state & (((1<<27)-1) & ~mask)) | (ADJ[(state>>(3*there))&7][dir] << (3*here)) | (there << 27);
    return state;
}

State (*MOVES[4])(State) = {toleft, toright, toup, todown};

State startState, goalState;

#define BIDIRECTIONAL_SEARCH 1
#define A_STAR 0
#define AGGRESSIVE 0
#define FAST_QUEUE 0
#define ID_A_STAR 0
#define USE_MAP 1

#if !ID_A_STAR
#if USE_MAP
map<State, int> dists;
#else
#define STATE_SIZE (6*6*6*6*6*6*6*6*9)
int dists[STATE_SIZE];
#endif
#endif

#if BIDIRECTIONAL_SEARCH
#define REVERSE_FLAG 0x1000
#endif

inline bool isGoal(State state) {
    return ((state&~0111111111) == goalState);
}

#if !USE_MAP
inline int encode(State s) {
    int empty = s>>27;
    int code = 0;
    REP(i, 9) {
        if (i != empty)
            code = code * 6 + ((s>>(3*i))&7);
    }
    code = code * 9 + empty;
    return code;
}
#else
#define encode(s) s
#endif

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

inline int estimate(State s) {
    s &= ~0111111111;
    int t = goalState;
    int empty1 = s >> 27;
    int empty2 = t >> 27;
    s |= 7<<(empty1*3);
    t |= 7<<(empty2*3);
    int h1 = -1;
    REP(i, 9)
        if (((s >> (3*i)) & 7) != ((t >> (3*i)) & 7))
            h1++;
    int h2 = abs(empty1%3 - empty2%3) + abs(empty1/3 - empty2/3);
    return max(h1, h2);
}


#if ID_A_STAR

int limit;

bool search_ida(State here, int depth) {
    if (isGoal(here))
        return true;
    if (depth+estimate(here) > limit)
        return false;
    REP(dir, 4) {
        State there = MOVES[dir](here);
        if (there != -1)
            if (search_ida(there, depth+1))
                return true;
    }
    return false;
}

int solve_ida() {
    for(limit = 0; limit <= 30; limit++) {
        if (search_ida(startState, 0))
            return limit;
    }
    return -1;
}

#else

int solve() {

    if (isGoal(startState))
        return 0;

#if !USE_MAP
    REP(i, STATE_SIZE)
        dists[i] = -1;
#else
    dists.clear();
#endif

#if A_STAR
    typedef pair<int,State> K;
    priority_queue<K, vector<K>, greater<K> > q;
    q.push(make_pair(0, startState));
#else
#if FAST_QUEUE
    nyaq<State, (1024*1024)> q;
#else
    queue<State> q;
#endif
    q.push(startState);
#endif

    dists[encode(startState)] = 0;

#if BIDIRECTIONAL_SEARCH
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
        q.push(g);
        dists[encode(g)] = REVERSE_FLAG;
    }
#endif

    while(!q.empty()) {

#if A_STAR
        State state = q.top().second;
        q.pop();
#else
        State state = q.front();
        q.pop();
#endif

        int code = encode(state);
#if !AGGRESSIVE
#if BIDIRECTIONAL_SEARCH
        if ((dists[code]&~REVERSE_FLAG) > 30/2)
            break;
#else
        if (dists[code] > 30)
            break;
#endif
#endif

//#define DEBUG
#ifdef DEBUG
        printf("%011o (f=%d; h=%d)\n", state, dists[code], estimate(state));
        REP(i, 3) {
            REP(j, 3) {
                int id = i*3 + j;
                int face = ((state>>(3*id))&7)/2;
                printf("%c ", (id == (state>>27) ? '.' : "WBR"[face]));
            }
            printf("\n");
        }
#endif

        REP(dir, 4) {
            State newState = MOVES[dir](state);
            int newCode = encode(newState);
            if (newState != -1) {
#if !USE_MAP
                if (dists[newCode] < 0) {
#else
                if (dists.count(newCode) == 0) {
#endif
                    dists[newCode] = dists[code] + 1;
#if A_STAR
                    int estimated = dists[newCode] + estimate(newState);
#if !AGGRESSIVE
                    if (estimated <= 30)
#endif
                        q.push(make_pair(estimated, newState));
#else
                    q.push(newState);
#endif
#if !BIDIRECTIONAL_SEARCH
                    if (isGoal(newState))
                        return dists[newCode];
#endif
                }
#if BIDIRECTIONAL_SEARCH
                else if (((dists[newCode] ^ dists[code]) & REVERSE_FLAG) != 0) {
                    return ((dists[code]+1 + dists[newCode]) & ~REVERSE_FLAG);
                }
#endif
            }
        }

    }

    return 1000;
}

#endif

int main() {

    // May fate be with you!

    /*
    int cnt = 0;
    REP(s, 9) REP(t, 9) REP(p, 3*3*3*3*3*3*3*3) {
        startState = s << 27;
        goalState = t << 27;
        int k = p;
        REP(i, 9) {
            if (i != t) {
                goalState |= (k%3*2) << (i*3);
                k /= 3;
            }
        }
        int res = solve();
        if (res > 30)
            res = -1;
        printf("(%d,%d) = %d\n", startState, goalState, res);
        if (++cnt == 20)
            return 0;
    }
    return 0;
    */

    for(;;) {

        int x, y;
        cin >> x >> y;

        if (x == 0 && y == 0)
            break;
        x--; y--;

        startState = (y*3+x)<<27;

        goalState = 0;
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

#if ID_A_STAR
        int res = solve_ida();
#else
        int res = solve();
#endif
#if !AGGRESSIVE
        if (res > 30)
            res = -1;
#endif
        cout << res << endl;

    }

    return 0;
}



// Powered by fate testarossa
