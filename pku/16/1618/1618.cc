#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

long long powll(long long e, int p) {
    long long res = 1;
    REP(i, p)
        res *= e;
    return res;
}

int main() {

    // May fate be with you!

    for(;;) {
        int nAlphabets, totalLength, nWords;

        cin >> nAlphabets >> totalLength >> nWords;

        if (nAlphabets == 0 && totalLength == 0 && nWords == 0)
            break;

        vector<string> words(nWords);
        REP(i, nWords)
            cin >> words[i];
        sort(ALLOF(words));
        words.erase(unique(ALLOF(words)), words.end());
        nWords = words.size();

        int edgeLength = words[0].size();

        if (edgeLength <= totalLength) {

            vector< vector<int> > spm(nWords);
            REP(i, nWords) {
                string& after = words[i];
                REP(j, nWords) {
                    string& before = words[j];
                    if (equal(before.begin()+1, before.end(), after.begin())) {
                        spm[i].push_back(j);
                        //cout << before << " goes to " << after << endl;
                    }
                }
            }

            vector<long long> vec(nWords, 1);
            REP(m, totalLength - edgeLength) {
                /*
                REP(i, nWords) if (vec[i])
                    cout << string(m, '.') << words[i] << endl;
                */
                vector<long long> new_vec(nWords, 0);
                REP(i, nWords) FOR(it, spm[i]) {
                    new_vec[i] += vec[*it];
                }
                vec.swap(new_vec);
            }

            /*
            REP(i, nWords) if (vec[i])
                cout << string(totalLength-edgeLength, '.') << words[i] << endl;
            */
            cout << accumulate(ALLOF(vec), (long long)0) << endl;

        }
        else {
            //cout << powll(nAlphabets, totalLength) << endl;
            cout << 0 << endl;
        }

    }


    return 0;
}



// Powered by fate testarossa
