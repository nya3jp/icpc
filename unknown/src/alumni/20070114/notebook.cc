#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>

using namespace std;

ifstream fin("i.in");
#define cin fin

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

bool solve(vector<int> f) {
    vector<int> loops(26+1, 0);
    vector<bool> visited(26, false);
    REP(a, 26) {
        if (!visited[a]) {
            int len = 0;
            for(int x = a; !visited[x]; x = f[x]) {
                visited[x] = true;
                len++;
            }
            loops[len]++;
        }
    }
    for(int k = 2; k <= 26; k+=2)
        if (loops[k]%2 == 1)
            return false;
    return true;
}

int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        string line;
        cin >> line;
        vector<int> given(26);
        REP(i, 26)
            given[i] = (int)(line[i] - 'A');
        cout << (solve(given) ? "Yes" : "No") << endl;
    }
    return 0;
}


