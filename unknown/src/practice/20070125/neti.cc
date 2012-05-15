#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <deque>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

bool isMark(char c) {
    return !(isalpha(c) || isdigit(c) || isspace(c));
}
bool isUpper(char c) {
    return ('A' <= c && c <= 'Z');
}

int main() {
    string line;

    while(getline(cin, line) && line != "#") {

        line = string(" ") + line + string(" ");

        int n = line.size();

        bool ok = true;
        REP(i, n-1) {
            if (isUpper(line[i]) && isUpper(line[i+1]))
                ok = false;
            if (isdigit(line[i]) && isalpha(line[i+1]))
                ok = false;
            if (isalpha(line[i]) && isdigit(line[i+1]))
                ok = false;
            if (isMark(line[i]) && isMark(line[i+1]) && line[i] != '\"' && line[i+1] != '\"')
                ok = false;
        }
        REP(i, n-2) {
            if (isspace(line[i]) && isspace(line[i+2])) {
                char c = line[i+1];
                if (!(isspace(c) || c == 'A' || c == 'a' || c == 'I'))
                    ok = false;
            }
        }

        cout << (ok ? "OK" : "suspicious") << endl;

    }


    return 0;
}


