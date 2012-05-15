#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int fib[40];

void fibtodec(const char* str, int& dec) {
    int& total = dec;
    total = 0;
    const int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if (str[i] == '1')
            total += fib[len-1-i];
    }
}

void dectofib(int dec, char* str) {
    str[0] = '0';
    int top = 0;
    for(int i = 40-1; i >= 0; i--) {
        if (dec >= fib[i]) {
            str[i] = '1';
            dec -= fib[i];
            if (i > top)
                top = i;
        }
        else {
            str[i] = '0';
        }
    }
    str[top+1] = '\0';
    reverse(str, str+top+1);
}

int main() {
    fib[0] = 1;
    fib[1] = 2;
    for(int i = 2; i < 40; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    char s0[1024], s1[1024], s2[1024];
    while(scanf("%s%s", s1, s2) == 2) {
        int i0, i1, i2;
        fibtodec(s1, i1); dectofib(i1, s1);
        fibtodec(s2, i2); dectofib(i2, s2);
        i0 = i1 + i2;
        dectofib(i0, s0);
        int l0, l1, l2;
        l0 = strlen(s0);
        l1 = strlen(s1);
        l2 = strlen(s2);
        printf("  ");
        for(int i=0; i<l0-l1; i++) printf(" ");
        printf("%s\n+ ", s1);
        for(int i=0; i<l0-l2; i++) printf(" ");
        printf("%s\n  ", s2);
        for(int i=0; i<l0; i++) printf("-");
        printf("\n  %s\n\n", s0);
    }
    return 0;
}
