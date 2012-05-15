#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>
#include <cstdio>
#include <cassert>
#include <numeric>
#include <ctype.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

const int INF = 0x1fffffff;
int costs[4];

typedef const char* (&ptr_t);

int parse_expr(ptr_t p);

int optimize(const vector<int>& v, const vector<bool>& commutatives, int* costs) {
    int n = v.size();

    /*
    printf("optimize: [ ");
    REP(i, n)
        printf("%c%d ", (commutatives[i] ? '+' : '-'), v[i]);
    printf("] (cost=%d,%d)", costs[0], costs[1]);
    */

    int res = 0;
    vector< vector<int> > dp(n, n+1);
    REP(i, n)
        dp[i][1] = v[i];
    for(int w = 2; w <= n; w++) {
        for(int first = 0; first + w <= n; first++) {
            int& res = dp[first][w];
            res = INF;
            if (commutatives[first]) {
                for(int u = 1; u < w; u++) {
                    if (!commutatives[first+u]) {
                        res <?= max(dp[first][u], dp[first+u][w-u]) + costs[1];
                    }
                    else {
                        res <?= max(dp[first][u], dp[first+u][w-u]) + costs[0];
                    }
                }
            }
        }
    }
    res = dp[0][n];

    //printf(" = %d\n", res);
    return res;
}

int parse_atom(ptr_t p) {
    int res = INF;
    if (*p == '(') {
        p++;
        res = parse_expr(p);
        p++;
    }
    else if (isdigit(*p)) {
        while(isdigit(*p))
            p++;
        res = 0;
    }
    else {
        assert(false);
    }
    return res;
}

int parse_cross_divide(ptr_t p) {
    vector<int> v;
    vector<bool> c;
    c.push_back(true);
    v.push_back(parse_atom(p));
    while(*p == '*' || *p == '/') {
        c.push_back(*p == '*');
        p++;
        v.push_back(parse_atom(p));
    }
    return optimize(v, c, costs+2);
}

int parse_plus_minus(ptr_t p) {
    vector<int> v;
    vector<bool> c;
    c.push_back(true);
    v.push_back(parse_cross_divide(p));
    while(*p == '+' || *p == '-') {
        c.push_back(*p == '+');
        p++;
        v.push_back(parse_cross_divide(p));
    }
    return optimize(v, c, costs+0);
}


int parse_expr(ptr_t p) {
    return parse_plus_minus(p);
}


int solve(string expr) {
    const char* p = expr.c_str();
    return parse_expr(p);
}

int main() {

    for(;;) {
        REP(i, 4)
            cin >> costs[i];

        if ((costs[0]|costs[1]|costs[2]|costs[3]) == 0)
            break;

        string expr;
        cin >> expr;

        cout << solve(expr) << endl;

    }
    assert(cin);

    return 0;
}
