#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())
#define IN(i,l,u) ((l) <= (i) && (i) < (u))

const char vowels[] = "aiueo";

bool isvowel[26];
bool cand[26];
char s[16];

void dfs(int pos, int idx, int v, int c, int len) {
    if (pos == len) {
        if (v >= 1 && c >= 2)
            printf("%s\n", s);
    }
    else {
        while(idx < 26) {
            if (cand[idx]) {
                s[pos] = (char)('a' + idx);
                dfs(pos+1, idx+1, (isvowel[idx]?v+1:v), (isvowel[idx]?c:c+1), len);
            }
            idx++;
        }
    }
}

int main() {

    fill(isvowel, isvowel+26, false);
    REP(i, 5)
        isvowel[vowels[i]-'a'] = true;

    int len, n;
    cin >> len >> n;

    fill(cand, cand+26, false);
    REP(i, n) {
        char c;
        cin >> c;
        cand[c-'a'] = true;
    }

    s[len] = '\0';
    dfs(0, 0, 0, 0, len);

    return 0;
}
