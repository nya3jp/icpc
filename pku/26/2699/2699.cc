#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

vector<int> read_sequence() {
    string line;
    getline(cin, line);
    istringstream is(line);
    return vector<int>(istream_iterator<int>(is), istream_iterator<int>());
}

void search(vector<int>& wins, vector<int>& losts, vector< vector<int> >& matches, const vector<int>& scores, int& res) {
    int n = wins.size();

    vector<bool> kings(n, true);
    REP(a, n) REP(b, n)
        if (scores[a] > scores[b] && matches[a][b] == 1)
            kings[b] = false;

    int cur = count(ALLOF(kings), true);
    if (cur <= res)
        return;

    REP(i, n) {
        if (wins[i] == 0 && losts[i] == 0)
            continue;
        if (wins[i] == 0 || losts[i] == 0) {
            vector<int>& a = (wins[i] > 0 ? wins : losts);
            vector<int>& b = (wins[i] == 0 ? wins : losts);
            int sgn = (wins[i] > 0 ? 1 : -1);

            bool valid = true;
            vector<bool> changed(n, false);
            REP(j, n) {
                if (i != j && matches[i][j] == 0) {
                    changed[j] = true;
                    matches[i][j] = sgn;
                    matches[j][i] = -sgn;
                    a[i]--;
                    b[j]--;
                    if (b[j] < 0)
                        valid = false;
                }
            }
            assert(a[i] == 0);

            if (valid)
                search(wins, losts, matches, scores, res);

            REP(j, n) {
                if (changed[j]) {
                    matches[i][j] = matches[j][i] = 0;
                    a[i]++;
                    b[j]++;
                }
            }
            return;
        }
    }

    {
        int i = 0;
        while(i < n && wins[i] == 0)
            i++;

        if (i == n) {
            res = max(res, cur);
            return;
        }

        int j = 0;
        while(j < n && !(i != j && wins[j] > 0 && matches[i][j] == 0))
            j++;
        if (j == n)
            return;

        REP(turn, 2) {
            wins[i]--;
            losts[j]--;
            matches[i][j] = 1;
            matches[j][i] = -1;
            search(wins, losts, matches, scores, res);
            matches[i][j] = matches[j][i] = 0;
            wins[i]++;
            losts[j]++;
            swap(i, j);
        }
    }

}

int main() {

    int nCases = read_sequence()[0];

    REP(iCase, nCases) {
        vector<int> scores = read_sequence();
        reverse(ALLOF(scores));

        int n = scores.size();
        vector<int> wins(n), losts(n);
        REP(i, n) {
            wins[i] = scores[i];
            losts[i] = (n-1) - scores[i];
        }

        vector< vector<int> > matches(n, vector<int>(n, 0));

        int res = 0;
        search(wins, losts, matches, scores, res);

        cout << res << endl;

    } 

    return 0;
}
