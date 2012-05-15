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

typedef unsigned long long state;

state mask, phone;

int mem[1<<18];

int solve_morphius(int morphius, int agent1, int agent2);
int solve_morphius0(int morphius, int agent1, int agent2);
int solve_agent1(int morphius, int agent1, int agent2);
int solve_agent2(int morphius, int agent1, int agent2);

int depth = 0;

int solve_morphius(int morphius, int agent1, int agent2) {
    depth++;
    int res = solve_morphius0(morphius, agent1, agent2);
    printf("%d ", depth);
    depth--;
    return res;
}
int solve_morphius0(int morphius, int agent1, int agent2) {
    if (agent1 > agent2)
        swap(agent1, agent2);

    if (morphius == agent1 || morphius == agent2)
        return 2;
    if (phone & (1ull << morphius))
        return 1;

#if 0
    REP(i, 8) {
        REP(j, 8) {
            int id = i*8+j;
            state bit = 1ull<<id;
            char c = '.';
            if (~mask&bit)
                c = '#';
            else if (morphius == id)
                c = 'M';
            else if (agent1 == id || agent2 == id)
                c = 'A';
            else if (phone&bit)
                c = 'P';
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
#endif

    if (morphius == agent1 || morphius == agent2)
        return 2;

    int id = (agent1*64+agent2)*64+morphius;
    int& res = mem[id];

    if (res < 0) {

        res = 0;
        bool can_win = false, can_loop = false;

        if (morphius%8 > 0) { // to left
            morphius--;
            if (mask & (1ull << morphius)) {
                int next = solve_agent1(morphius, agent1, agent2);
                if (next == 1)
                    can_win = true;
                else if (next == 2)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            morphius++;
        }
        if (morphius%8 < 7) { // to right
            morphius++;
            if (mask & (1ull << morphius)) {
                int next = solve_agent1(morphius, agent1, agent2);
                if (next == 1)
                    can_win = true;
                else if (next == 2)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            morphius--;
        }
        if (morphius/8 > 0) { // to up
            morphius -= 8;
            if (mask & (1ull << morphius)) {
                int next = solve_agent1(morphius, agent1, agent2);
                if (next == 1)
                    can_win = true;
                else if (next == 2)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            morphius += 8;
        }
        if (morphius/8 < 7) { // to down
            morphius += 8;
            if (mask & (1ull << morphius)) {
                int next = solve_agent1(morphius, agent1, agent2);
                if (next == 1)
                    can_win = true;
                else if (next == 2)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            morphius -= 8;
        }

        if (can_win)
            res = 1;
        else if (can_loop)
            res = 0;
        else
            res = 2;
    }
    return res;
}

int solve_agent1(int morphius, int agent1, int agent2) {
    if (morphius == agent1 || morphius == agent2)
        return 2;
    if (phone & (1ull << morphius))
        return 1;

    int res;
    {
        res = 0;
        bool can_catch = false, can_loop = false;
        if (agent1%8 > 0) { // to left
            agent1--;
            if (mask & (1ull << agent1)) {
                int next = solve_agent2(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent1++;
        }
        if (agent1%8 < 7) { // to right
            agent1++;
            if (mask & (1ull << agent1)) {
                int next = solve_agent2(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent1--;
        }
        if (agent1/8 > 0) { // to up
            agent1 -= 8;
            if (mask & (1ull << agent1)) {
                int next = solve_agent2(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent1 += 8;
        }
        if (agent1/8 < 7) { // to down
            agent1 += 8;
            if (mask & (1ull << agent1)) {
                int next = solve_agent2(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent1 -= 8;
        }

        if (can_catch)
            res = 2;
        else if (can_loop)
            res = 0;
        else
            res = 1;
    }
    return res;
}

int solve_agent2(int morphius, int agent1, int agent2) {
    if (morphius == agent1 || morphius == agent2)
        return 2;
    if (phone & (1ull << morphius))
        return 1;

    int res;
    {
        res = 0;
        bool can_catch = false, can_loop = false;
        if (agent2%8 > 0) { // to left
            agent2--;
            if (mask & (1ull << agent2)) {
                int next = solve_morphius(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent2++;
        }
        if (agent2%8 < 7) { // to right
            agent2++;
            if (mask & (1ull << agent2)) {
                int next = solve_morphius(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent2--;
        }
        if (agent2/8 > 0) { // to up
            agent2 -= 8;
            if (mask & (1ull << agent2)) {
                int next = solve_morphius(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent2 += 8;
        }
        if (agent2/8 < 7) { // to down
            agent2 += 8;
            if (mask & (1ull << agent2)) {
                int next = solve_morphius(morphius, agent1, agent2);
                if (next == 2)
                    can_catch = true;
                else if (next == 1)
                    ;
                else if (next == 0)
                    can_loop = true;
            }
            agent2 -= 8;
        }

        if (can_catch)
            res = 2;
        else if (can_loop)
            res = 0;
        else
            res = 1;
    }
    return res;
}

int main() {

    int n;
    cin >> n;
    while(n-- > 0) {

        vector<int> agents;
        int morphius;

        mask = 0xFFFFFFFFFFFFFFFFull;
        phone = 0;

        REP(i, 8) {
            string s;
            cin >> s;
            REP(j, 8) {
                int id = (i*8+j);
                state bit = 1ull << id;
                switch(s[j]) {
                case '#':
                    mask ^= bit;
                    break;
                case 'P':
                    phone ^= bit;
                    break;
                case 'A':
                    agents.push_back(id);
                    break;
                case 'M':
                    morphius = id;
                    break;
                }
            }
        }

        int agent1 = agents[0];
        int agent2 = agents[1];

        REP(i, 1<<18) mem[i] = -1;
        int res = solve_morphius(morphius, agent1, agent2);
        switch(res) {
        case 0:
            cout << "You are trapped in the Matrix." << endl;
            break;
        case 1:
            cout << "You can escape." << endl;
            break;
        case 2:
            cout << "You are eliminated." << endl;
            break;
        default:
            cout << res << endl;
            break;
        }
    }

    return 0;
}
