#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

    for(;;) {
        int n, nOper;
        cin >> n >> nOper;

        if (n == 0 && nOper == 0)
            break;

        vector<int> deck(n);
        REP(i, n)
            deck[i] = n-i;

        REP(iOper, nOper) {
            int p, c;
            cin >> p >> c;
            rotate(deck.begin(), deck.begin()+(p-1), deck.begin()+(p-1 + c));
        }

        cout << deck[0] << endl;
    }

    return 0;
}
