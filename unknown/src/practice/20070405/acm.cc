#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

int solve(const string& abbrev, const vector<string>& words, int abbrevPos, int wordsPos, map<int, map<int, int> >& mem) {

    if (abbrevPos == (int)abbrev.size() && wordsPos == (int)words.size())
        return 1;
    if (abbrevPos == (int)abbrev.size() || wordsPos == (int)words.size())
        return 0;

    string word = words[wordsPos];
    int wordLen = word.size();
    int abbrevLen = abbrev.size() - abbrevPos;

    vector< vector<int> > dp(abbrevLen+1, vector<int>(wordLen+1, 0));

    //cout << "match " << abbrev.substr(abbrevPos) << " against " << word << endl;

    REP(j, wordLen+1)
        dp[0][j] = 1;

    REP(i, abbrevLen) REP(j, wordLen) {
        dp[i+1][j+1] = dp[i+1][j];
        if (abbrev[abbrevPos+i]+0x20 == word[j])
            dp[i+1][j+1] += dp[i][j];
    }
    /*
    REP(i, abbrevLen+1) {
        REP(j, wordLen+1) {
            cout << dp[i][j];
        }
        cout << endl;
    }
    */

    int res = 0;
    for(int i = 1; i <= abbrevLen; i++) {
        res += dp[i][wordLen] * solve(abbrev, words, abbrevPos+i, wordsPos+1, mem);
    }

    return mem[abbrevPos][wordsPos] = res;
}

int solve(string abbrev, vector<string> words) {
    map<int, map<int, int> > mem;
    return solve(abbrev, words, 0, 0, mem);
}


int main() {

    for(;;) {

        int nIgnores;
        cin >> nIgnores >> ws;

        if (nIgnores == 0)
            break;

        set<string> ignores;
        REP(i, nIgnores) {
            string s;
            getline(cin, s);
            ignores.insert(s);
        }

        for(;;) {

            string query;
            getline(cin, query);
            if (query == "LAST CASE")
                break;

            istringstream is(query);

            string abbrev;
            is >> abbrev;

            vector<string> words;
            for(string s; is >> s;)
                if (ignores.count(s) == 0)
                    words.push_back(s);

            int res = solve(abbrev, words);
            if (res == 0)
                cout << abbrev << " is not a valid abbreviation" << endl;
            else
                cout << abbrev << " can be formed in " << res << " ways" << endl;

        }

    }

    return 0;
}

