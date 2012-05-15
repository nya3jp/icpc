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

char buf[1024];

#define N 27
int n;

double mat[N][N];
double y[N], x[N];

inline void skip(char*& p) {
    while(isspace(*p))
        p++;
}

vector<double> parse(char*& p) {
    skip(p);
    vector<double> f(n+1, 0);
    char c = *p;
    if (c == '(') {
        p++;
        int m = 0;
        while(skip(p), *p != ')') {
            vector<double> ff = parse(p);
            REP(i, n+1)
                f[i] += ff[i];
            m++;
        }
        assert(*p == ')');
        REP(i, n+1)
            f[i] /= m;
        p++;
    }
    else if (isdigit(*p) || *p == '-') {
        bool neg = (*p == '-');
        if (neg)
            p++;
        double x = 0;
        while(isdigit(*p)) {
            x = x * 10 + (int)(*p - '0');
            p++;
        }
        if (neg)
            x = -x;
        f[n] = x;
    }
    else {
        assert(isalpha(*p));
        int k = (int)(*p - 'a');
        p++;
        f[k] = 1;
    }
    return f;
}

void iterate() {
    REP(r, 100000) {
        REP(i, n+1)
            y[i] = 0;
        REP(i, n+1) REP(j, n+1)
            y[i] += mat[i][j] * x[j];

        {
            double norm = 0;
            REP(i, n)
                norm += (x[i]-y[i])*(x[i]-y[i]);
            norm = sqrt(norm);
            if (norm < 1e-8)
                break;
        }

        REP(i, n+1)
            x[i] = y[i];
    }
}

int main() {

    int iCase = 0;
    for(;;) {

        gets(buf);
        sscanf(buf, "%d", &n);

        if (n == 0)
            break;

        printf("Game %d\n", ++iCase);

        REP(i, n) {
            gets(buf);
            char* p = buf;
            while(*p != '=')
                p++;
            p++;
            vector<double> f = parse(p);
            REP(j, n+1)
                mat[i][j] = f[j];
        }
        REP(j, n+1)
            mat[n][j] = (j == n ? 1 : 0);

        REP(i, n)
            x[i] = rand()*1e5+1e5;
        x[n] = 1;
        iterate();
        vector<double> x1(x, x+n+1);

        REP(i, n)
            x[i] = rand()%1000*1e1+1e5;
        x[n] = 1;
        iterate();
        vector<double> x2(x, x+n+1);

        REP(i, n) {
            char c = (char)('a' + i);
            printf("Expected score for %c ", c);
            double z1 = x1[i];
            double z2 = x2[i];
            if (abs(z1-z2) < 1e-5) {
                if (abs(z1) < 1e-5)
                    z1 = 0;
                printf("= %.3f\n", z1);
            }
            else {
                printf("undefined\n");
            }
        }

        printf("\n");

    }

    return 0;
}

