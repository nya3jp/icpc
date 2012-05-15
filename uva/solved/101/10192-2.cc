#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int lcss(const string& str1, const string& str2) {
    int N, n, M, m;
    N = n = str1.size();
    M = m = str2.size();
int lcs[N+1][M+1];
REP(i, n+1) REP(j, m+1) lcs[i][j] = 0;
REP(i, n) REP(j, m)
    lcs[i+1][j+1] = (str1[i] == str2[j] ? lcs[i][j]+1 : 0)
                    >? lcs[i+1][j] >? lcs[i][j+1];
return lcs[n][m];
    
}


int main() {
    int iCase = 0;
    string s, t;
    while(getline(cin, s) && getline(cin, t) && (s.empty() || s[0] != '#')) {
        cout << "Case #"
             << ++iCase
             << ": you can visit at most "
             << lcss(s, t)
             << " cities." << endl;
    }
    return 0;
}

