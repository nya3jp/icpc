#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int main() {

    for(;;) {
        string line;
        getline(cin, line);
        int nLines;
        sscanf(line.c_str(), "%d", &nLines);
        if (nLines == 0)
            break;

        string text;
        {
            ostringstream os;
            REP(i, nLines) {
                getline(cin, line);
                os << line;
            }
            text = os.str();
        }

        const char* p = text.c_str();
        int n = text.size();

        vector<int> hist(128*128, 0);

        REP(i, n-1) {
            int x = (int)p[i] * 128 + (int)p[i+1];
            hist[x]++;
        }

        vector< pair<int,string> > cands;
        REP(i, 128*128) {
            if (hist[i] > 0) {
                cands.push_back(make_pair(-hist[i], string(1, (char)(i/128)) + string(1, (char)(i%128))));
            }
        }

        sort(ALLOF(cands));

        REP(i, 5) {
            int f = -cands[i].first;
            string s = cands[i].second;
            printf("%s %d %.6f\n", s.c_str(), f, (double)f / (n-1));
        }
        printf("\n");

    }


    return 0;
}
