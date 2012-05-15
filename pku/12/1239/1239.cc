#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 80

string line;

int line_cmp(int afrom, int ato, int bfrom, int bto) {
    while(afrom < ato && line[afrom] == '0')
        afrom++;
    while(bfrom < bto && line[bfrom] == '0')
        bfrom++;
    if (ato-afrom != bto-bfrom)
        return ((ato-afrom) - (bto-bfrom));
    if (equal(line.begin()+afrom, line.begin()+ato, line.begin()+bfrom))
        return 0;
    if (lexicographical_compare(line.begin()+afrom, line.begin()+ato, line.begin()+bfrom, line.begin()+bto))
        return -1;
    return 1;
}

bool dp[N+1][N+1];

void solve() {

    int n = line.size();

    int zero_pad = 0;
    while(n > 1 && line[0] == '0') {
        zero_pad++;
        line = line.substr(1);
        n--;
    }

    for(int j = 1; j <= n; j++)
        dp[0][j] = true;

    for(int j = 1; j < n; j++) {
        for(int k = j+1; k <= n; k++) {
            dp[j][k] = false;
            for(int i = 0; i < j; i++) {
                if (dp[i][j] && line_cmp(i, j, j, k) < 0) {
                    dp[j][k] = true;
                    break;
                }
            }
        }
    }

    /*
    for(int i = 0; i < n; i++) {
        cout << string(i+1, '.');
        for(int j = i+1; j <= n; j++)
            cout << dp[i][j];
        cout << endl;
    }
    cout << endl;
    //*/

    int last = n-1;
    while(!dp[last][n])
        last--;

    for(int i = 0; i < last; i++)
        dp[i][last] = (line_cmp(i, last, last, n) < 0);

    for(int i = last-1; i >= 0; i--) {
        for(int j = i+1; j < last; j++) {
            dp[i][j] = false;
            for(int k = j+1; k <= last; k++) {
                if (dp[j][k] && line_cmp(i, j, j, k) < 0) {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }

    /*
    for(int i = 0; i < last; i++) {
        cout << string(i+1, '.');
        for(int j = i+1; j <= last; j++)
            cout << dp[i][j];
        cout << endl;
    }
    cout << endl;
    //*/

    {
        int i = 0, j = last;
        while(i < last) {
            while(!dp[i][j])
                j--;
            if (i == 0)
                cout << string(zero_pad, '0');
            cout << line.substr(i, j-i) << ",";
            i = j;
            j = last;
        }
        if (last == 0)
            cout << string(zero_pad, '0');
        cout << line.substr(last) << endl;
    }

}

int main() {

    while(cin >> line && line != "0")
        solve();

    return 0;
}
