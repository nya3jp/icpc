#include <cstdio>
#include <cstring>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

char line[1000000+1024];
char buf[1000000+1024];

void decompress(const char* s, char* t) {
    while(*s != '\0') {
        char c = *s;
        if ('0' <= c && c <= '9') {
            int r = 0;
            while(c = *s, '0' <= c && c <= '9') {
                r = r * 10 + (int)(c - '0');
                s++;
            }
            char last = *--t;
            REP(i, r)
                *t++ = last;
        }
        else {
            *t++ = c;
            s++;
        }
    }
    *t = '\0';
}

#define index(c) ((c) == '.' ? 0 : (int)((c) - 'A') + 1)

void solve(const char* s) {

    int n = strlen(s);

    int sum[27];
    memset(sum, 0, sizeof(sum));

    int start;
    REP(i, n) {
        int idx = index(s[i]);
        sum[idx]++;
        if (idx == 0)
            start = i;
    }

    for(int i = 1; i < 27; i++)
        sum[i] += sum[i-1];

    static int* g = new int[1000000+1024];

    for(int i = n-1; i >= 0; i--) {
        int here = --sum[index(s[i])];
        int there = i;
        //fprintf(stderr, "%d -> %d\n", here, there);
        g[here] = there;
    }

    for(int i = g[start]; i != start; i = g[i])
        putc(s[i], stdout);
    puts(".");

    //delete[] g;

}

int main() {

    gets(line);
    int nCases;
    sscanf(line, "%d", &nCases);

    REP(iCase, nCases) {
        gets(line);
        decompress(line, buf);
        solve(buf);
    }

    return 0;
}
