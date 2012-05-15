#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()



int main() {

    int nWords;
    cin >> nWords;

    set<string> words;
    REP(i, nWords) {
        string s;
        cin >> s;
        sort(ALLOF(s));
        words.insert(s);
    }

    int nCases;
    cin >> nCases;
    while(nCases-- > 0) {

        int nTiles;
        cin >> nTiles;

        vector<char> chrs(nTiles);
        vector<int> scores(nTiles);
        REP(i, nTiles)
            cin >> chrs[i] >> scores[i];

        int res = 0;
        REP(i, 1<<nTiles) {
            string s;
            int c = 0;
            REP(j, nTiles)
                if (i&(1<<j))
                    s.push_back(chrs[j]), c += scores[j];
            sort(ALLOF(s));
            if (words.count(s) > 0)
                res >?= c;
        }

        cout << res << endl;


        /*
        vector<int> edges(1<<nTiles, -10000);
        REP(i, 1<<nTiles) {
            string s;
            int c = 0;
            REP(j, nTiles)
                if (i&(1<<j))
                    s.push_back(chrs[j]), c += scores[j];
            sort(ALLOF(s));
            if (words.count(s) > 0)
                edges[i] = c;
        }

        vector<int> dp(1<<nTiles, -10000);
        dp[0] = 0;
        REP(i, 1<<nTiles)
            REP(j, 1<<nTiles)
                if ((i&j) == 0)
                    dp[i|j] >?= dp[i] + edges[j];

        cout << *max_element(ALLOF(dp)) << endl;
        */

    }

    return 0;
}
