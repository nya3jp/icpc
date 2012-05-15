/*
 * UVA 562 Dividing coins
 * 2004-12-30
 * by nya
 */

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;

int main(int argc, char** argv)
{
    int nCases;

    cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {

        int nCoins;
        cin >> nCoins;

        vector<int> coins;
        coins.resize(nCoins);
        for(int iCoin=0; iCoin<nCoins; iCoin++) {
            cin >> coins[iCoin];
        }

        // sort coins by descending order so that
        // pruning gets more efficient
        sort(coins.begin(), coins.end(), greater<int>());

        int iRemainingValue = accumulate(coins.begin(), coins.end(), 0);

        set<int> gaps;
        gaps.insert(0);

        for(int iCoin=0; iCoin<nCoins; iCoin++) {
            set<int> new_gaps;
            int value = coins[iCoin];

            for(set<int>::iterator it = gaps.begin(); it != gaps.end(); it++) {
                new_gaps.insert(*it + value);
                new_gaps.insert(abs(*it - value));
            }

            iRemainingValue -= value;
            {
                // eliminate gaps that are greater than M,
                // where M is the lower_bound of sum of remaining values
                set<int>::iterator it;
                it = new_gaps.lower_bound(iRemainingValue);
                if (it != new_gaps.end()) {
                    new_gaps.erase(++it, new_gaps.end());
                }
            }

#if 0
            // for debugging, print all the candidate gaps
            {
                cerr << value << ": ";
                ostream_iterator<int> iterr(cerr, " ");
                copy(new_gaps.begin(), new_gaps.end(), iterr);
                cerr << endl;
            }
#endif

            gaps = new_gaps;
        }

        cout << *gaps.begin() << endl;
    }

    return 0;
}

