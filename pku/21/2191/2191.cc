#include <iostream>
#include <unistd.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

const char* TABLE[] = {
    "2: 3: 3\n",
    "3: 7: 7\n",
    "5: 31: 31\n",
    "7: 127: 127\n",
    "11: 2047: 23 89\n",
    "13: 8191: 8191\n",
    "17: 131071: 131071\n",
    "19: 524287: 524287\n",
    "23: 8388607: 47 178481\n",
    "29: 536870911: 233 1103 2089\n",
    "31: 2147483647: 2147483647\n",
    "37: 137438953471: 223 616318177\n",
    "41: 2199023255551: 13367 164511353\n",
    "43: 8796093022207: 431 9719 2099863\n",
    "47: 140737488355327: 2351 4513 13264529\n",
    "53: 9007199254740991: 6361 69431 20394401\n",
    "59: 576460752303423487: 179951 3203431780337\n",
    "61: 2305843009213693951: 2305843009213693951\n"};

int main() {

    int n;
    cin >> n;

    REP(i, sizeof(TABLE)/sizeof(const char*)) {
        const char* S = TABLE[i];
        int m;
        unsigned long long int a, b, c, d;
        int r = sscanf(S, "%d:%I64u:%I64u%I64u%I64u", &m, &a, &b, &c, &d);
        if (r > 3 && m <= n) {
            printf("%I64u * %I64u", b, c);
            if (r == 5)
                printf(" * %I64u", d);
            printf(" = %I64u = ( 2 ^ %d ) - 1\n", a, m);
        }
    }

    /*
    for(int n = 2; n <= 63; n++) {
        for(int m = 2; m < n; m++)
            if (n%m == 0)
                goto NEXT;
        unsigned long long x = (1ull << n) - 1;
        char cmd[1024];
        sprintf(cmd, "factor %llu", x);
        printf("%d: ", n);
        fflush(stdout);
        system(cmd);
    NEXT:;
    }
    */

    return 0;
}

