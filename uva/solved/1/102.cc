#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define BINS    3
#define GLASSES 3

int main() {

    while(true) {

        int bins[BINS][GLASSES];

        for(int i = 0; i < BINS; i++)
            for(int j = 0; j < GLASSES; j++)
                cin >> bins[i][j];
        if (!cin)
            break;

        for(int i = 0; i < BINS; i++)
            swap(bins[i][1], bins[i][2]); // swap green and clear

        int perm[BINS];
        for(int i = 0; i < BINS; i++)
            perm[i] = i;

        int best_perm[BINS];
        int best_cost = 0x7fffffff;

        do {
            int cost = 0;
            for(int i = 0; i < BINS; i++) {
                for(int j = 0; j < GLASSES; j++) {
                    if (j != perm[i])
                        cost += bins[i][j];
                }
            }
            if (cost < best_cost) {
                copy(perm, perm+BINS, best_perm);
                best_cost = cost;
            }
        } while(next_permutation(perm, perm+BINS));

        const char NAMES[] = "BCG";

        for(int i = 0; i < BINS; i++)
            cout << NAMES[best_perm[i]];
        cout << ' ' << best_cost << endl;

    }


    return 0;
}


