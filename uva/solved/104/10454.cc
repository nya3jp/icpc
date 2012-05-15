/*
 * UVA 10454 - Trexpression
 * 2006-01-03
 * by nya
 */

#include <cstdio>
#include <cassert>

#define MAX_OPERANDS 36

typedef long long int integer;

integer BINTREES[MAX_OPERANDS+1];

void init() {
    BINTREES[0] = BINTREES[1] = 1;

    for(int n=2; n<=MAX_OPERANDS; n++) {
        BINTREES[n] = 0;
        for(int i=0; i<=n-1; i++) {
            int j = (n-1) - i;

            BINTREES[n] += BINTREES[i] * BINTREES[j];
        }
    }

    /*
    for(int i=0; i<=MAX_OPERANDS; i++) {
        std::printf("%d: %llu\n", i, BINTREES[i]);
    }
    */
}

integer eval_fact(char* (&p));
integer eval_term(char* (&p));
integer eval_expr(char* (&p));


integer eval_fact(char* (&p)) {
    integer n;
    if (*p == '(') {
        p++;
        n = eval_expr(p);
        assert(*p == ')');
        p++;
    }
    else if ('0' <= *p && *p <= '9') {
        p++;
        n = 1;
    }
    else {
        assert(false);
    }
    return n;
}

integer eval_term(char* (&p)) {
    integer n = eval_fact(p);
    int oprs = 0;
    while(*p == '*') {
        p++;
        n *= eval_fact(p);
        oprs++;
    }
    return n * BINTREES[oprs];
}

integer eval_expr(char* (&p)) {
    integer n = eval_term(p);
    int oprs = 0;
    while(*p == '+') {
        p++;
        n *= eval_term(p);
        oprs++;
    }
    return n * BINTREES[oprs];
}

integer solve(char* p) {
    return eval_expr(p);
}


int main() {

    init();

    char buf[150];
    while(std::fgets(buf, sizeof(buf), stdin)) {
        std::printf("%llu\n", solve(buf));
    }

    return 0;
}
