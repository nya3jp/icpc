#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 52

typedef int Deck[N];

Deck ref_decks[10+1];


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


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("number of cases should be specified\n");
        return 1;
    }

    srand(time(0));

    init_deck(ref_decks[0]);
    for(int c = 0; c < 10; c++) {
        shuffle_deck(ref_decks[c], ref_decks[c+1]);
    }

    Deck decks[10+1];

    init_deck(decks[0]);

    int nCases;

    sscanf(argv[1], "%d", &nCases);

    cout << nCases << endl;

    for(int iCase = 0; iCase < nCases; iCase++) {

        int nShuffles = 10;

        vector<int> swaps(nShuffles, -1);

        for(int iShuffle = 0; iShuffle < nShuffles; iShuffle++) {
            shuffle_deck(decks[iShuffle], decks[iShuffle+1]);
            Deck& newdeck = decks[iShuffle+1];

            if ( (rand()/16)%100 < 50 ) {
                int pos = rand()%(N-1);
                swap(newdeck[pos], newdeck[pos+1]);
                swaps[iShuffle] = pos;
            }
        }

        for(int i = 0; i < N; i++)
            cout << decks[nShuffles][i] << ' ';
        cout << endl;


        cerr << "Case " << (iCase+1) << endl;
        cerr << "Number of shuffles = " << nShuffles << endl;

        bool error = false;
        for(int i = 0; i < nShuffles; i++) {
            int s = swaps[i];
            if (s >= 0) {
                cerr << "Error in shuffle " << (i+1) << " at location " << s << endl;
                error = true;
            }
        }
        if (!error)
            cerr << "No error in any shuffle" << endl;

        cerr << endl;

    }

    return 0;
}
