#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template<class T>
int lcs(vector<T>& a, vector<T>& b, vector<T>& r) {
    int n = a.size();
    int m = b.size();

    vector< vector<int> > table(n+1, vector<int>(m+1, 0));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                table[i][j] = table[i-1][j-1] + 1;
            else
                table[i][j] = max(table[i][j-1], table[i-1][j]);
        }
    }

    r.clear();
    for(int i = n, j = m; table[i][j] > 0; ) {
        if (a[i-1] == b[j-1]) {
            r.push_back(a[i-1]);
            i--; j--;
        }
        else {
            (table[i-1][j] >= table[i][j-1] ? i : j)--;
        }
    }
    reverse(r.begin(), r.end());
    return table[n][m];
}


int main() {
    int iCase = 0;
    string s, t;
    while(getline(cin, s) && getline(cin, t) && (s.empty() || s[0] != '#')) {
        vector<char> v(s.begin(), s.end()), u(t.begin(), t.end());
        vector<char> l;
        cout << "Case #"
             << ++iCase
             << ": you can visit at most "
             << lcs(v, u, l)
             << " cities." << endl;
    }
    return 0;
}

