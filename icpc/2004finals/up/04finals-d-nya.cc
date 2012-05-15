/*
 * 2004-2005 ICPC Finals Problem D "cNteSahruPfefrlefe"
 * or "Near Perfect Shuffle"
 *
 * by nya@qoo
 */


#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <cassert>

using namespace std;


#define N 52

typedef int Deck[N];


Deck ref_decks[10+1]; // reference-decks shuffled without misses


void init_deck(Deck& deck) {
    for(int i = 0; i < N; i++)
        deck[i] = i;
}

void shuffle_deck(const Deck& deck, Deck& shuffled_deck) {
    for(int i = 0; i < N; i++) {
        int j = (i < N/2 ? i*2+1 : (i-N/2)*2);
        shuffled_deck[j] = deck[i];
    }
}

void unshuffle_deck(const Deck& deck, Deck& unshuffled_deck) {
    for(int i = 0; i < N; i++) {
        int j = (i < N/2 ? i*2+1 : (i-N/2)*2);
        unshuffled_deck[i] = deck[j];
    }
}



struct Found {};

void search(Deck& deck,
            int iUnshuffle,
            int nUnmatches,
            int nSwaps,
            int nShuffles,
            vector<int>& swaps,
            vector<int>& bestSwaps,
            int nLimitSwaps)
{
    // prun if any solution cannot be found no more
    if (nUnmatches > min(nShuffles-iUnshuffle, nLimitSwaps-nSwaps)*2)
        return;

    if (iUnshuffle == nShuffles) {
        // optimal solution found!
        bestSwaps = swaps;
        throw Found();
    }


    Deck prev_decks[N]; // unshuffled decks
    int priorities[N];  // priority of each prev_decks

    for(int i = 0; i < N-1; i++) {

        int nNewMatches = 0;

        if (deck[i] == ref_decks[nShuffles-iUnshuffle][i])
            nNewMatches--;
        if (deck[i+1] == ref_decks[nShuffles-iUnshuffle][i+1])
            nNewMatches--;

        swap(deck[i], deck[i+1]);

        unshuffle_deck(deck, prev_decks[i+1]);

        if (deck[i] == ref_decks[nShuffles-iUnshuffle][i])
            nNewMatches++;
        if (deck[i+1] == ref_decks[nShuffles-iUnshuffle][i+1])
            nNewMatches++;

        swap(deck[i], deck[i+1]);

        priorities[i+1] = nNewMatches; // use nNewMatches for priority
    }

    // a case without (un)shuffle
    priorities[0] = 0;
    unshuffle_deck(deck, prev_decks[0]);


    // sort cases
    vector< pair<int, int> > order(N);
    for(int i = 0; i < N; i++)
        order[i] = make_pair(priorities[i], i);
    sort(order.begin(), order.end(), greater< pair<int, int> >());


    for(int i = 0; i < N; i++) {
        int j = order[i].second;
        int nNewMatches = order[i].first;
        swaps[iUnshuffle] = j - 1;
        search(prev_decks[j],
               iUnshuffle+1,
               nUnmatches-nNewMatches,
               nSwaps + (j == 0 ? 0 : 1),
               nShuffles,
               swaps,
               bestSwaps,
               nLimitSwaps);
    }

}



int main() {

    init_deck(ref_decks[0]);
    for(int c = 0; c < 10; c++) {
        shuffle_deck(ref_decks[c], ref_decks[c+1]);
    }


    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        // read a case
        Deck deck;
        for(int i = 0; i < N; i++) {
            cin >> deck[i];
        }

        // determine the number of shuffles done
        int nShuffles;
        int nUnmatches;
        for(nShuffles = 1; nShuffles <= 10; nShuffles++) {
            int m = 0;
            for(int i = 0; i < N; i++)
                if (deck[i] == ref_decks[nShuffles][i])
                    m++;
            if (m >= N - 2*10) {
                nUnmatches = N - m;
                break;
            }
        }
        assert(nShuffles <= 10);


        vector<int> bestSwaps;
        try {
            // iterative deepening
            for(int nSwaps = 0; ; nSwaps++) {
                vector<int> swaps(nShuffles, -1);
                search(deck,
                       0,
                       nUnmatches,
                       0,
                       nShuffles,
                       swaps,
                       bestSwaps,
                       nSwaps);
            }
        }
        catch(Found) {
        }


        // output
        cout << "Case " << (iCase+1) << endl;
        cout << "Number of shuffles = " << nShuffles << endl;

        bool error = false;
        for(int i = 0; i < nShuffles; i++) {
            int s = bestSwaps[nShuffles-1-i];
            if (s >= 0) {
                cout << "Error in shuffle " << (i+1) << " at location " << s << endl;
                error = true;
            }
        }
        if (!error)
            cout << "No error in any shuffle" << endl;

        cout << endl;

    }

    return 0;
}
