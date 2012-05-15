#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <queue>
#include <functional>
#include <cstring>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

const char* TABLE[26] = {
    "4",
    "|3",
    "(",
    "|)",
    "3",
    "|=",
    "6",
    "#",
    "|",
    "_|",
    "|<",
    "|_",
    "|\\/|",
    "|/|",
    "0",
    "|0",
    "(,)",
    "|?",
    "5",
    "7",
    "|_|",
    "\\/",
    "\\/\\/",
    "><",
    "-/",
    "2",
};


void solve(string given) {
    string encoded;
    REP(i, given.size())
        encoded += TABLE[(int)(given[i]-'A')];
    const char* cencoded = encoded.c_str();
    int len = strlen(cencoded);
    //printf("%s%d\n", cencoded, len);
    int table[len+1];
    table[len] = 1;
    for(int pos = len-1; pos >= 0; pos--) {
        table[pos] = 0;
        REP(ch, 26) {
            int l = strlen(TABLE[ch]);
            if (pos+l <= len && strncmp(cencoded+pos, TABLE[ch], l) == 0)
                table[pos] += table[pos+l];
        }
    }
    printf("%d\n", table[0]);
}

int main() {

    string given;
    while(getline(cin, given) && given != "end")
        solve(given);

    return 0;
}
