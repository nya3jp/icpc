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

typedef int integer;
const integer IMPOSSIBLE = -(numeric_limits<integer>::max() - 28);

char expr[256];
int target;

integer eval_expr(char*& p);

integer eval_atom(char*& p) {
    if (*p == '(') {
        p++;
        int a = eval_expr(p);
        p++;
        return a;
    }
    else {
        int d = 0;
        while(isdigit(*p)) {
            d = d * 10 + (int)(*p - '0');
            p++;
        }
        return d;
    }
}

integer eval_term(char*& p) {
    integer a = eval_atom(p);
    if (a == IMPOSSIBLE)
        return IMPOSSIBLE;
    while(*p == '*' || *p == '/') {
        bool div = (*p == '/');
        p++;
        integer b = eval_atom(p);
        if (b == IMPOSSIBLE)
            return IMPOSSIBLE;
        if (div) {
            if (b == 0)
                return IMPOSSIBLE;
            a /= b;
        }
        else {
            a *= b;
        }
    }
    return a;
}
integer eval_expr(char*& p) {
    integer a = eval_term(p);
    if (a == IMPOSSIBLE)
        return IMPOSSIBLE;
    while(*p == '+' || *p == '-') {
        integer s = (*p == '+' ? 1 : -1);
        p++;
        integer b = eval_term(p);
        if (b == IMPOSSIBLE)
            return IMPOSSIBLE;
        a += s*b;
    }
    return a;
}

integer eval() {
    //puts(expr);
    char* p = expr;
    return eval_expr(p);
}

void input() {
    gets(expr);
    scanf("%d ", &target);
}

void solve() {

    char* holes[12];
    int nHoles = 0;

    for(char* p = expr; *p; p++) {
        if (*p == '?') {
            holes[nHoles++] = p;
        }
    }

    int nPatterns = 1<<(2*nHoles);
    REP(ptn, nPatterns) {
        REP(i, nHoles) {
            int op = (ptn >> (2*i)) & 3;
            *holes[i] = "+-*/"[op];
        }
        if (eval() == target) {
            puts("yes");
            return;
        }
    }

    puts("no");
}

int main() {

    int nCases;
    scanf("%d ", &nCases);

    REP(iCase, nCases) {
        input();
        solve();
    }

    return 0;
}

