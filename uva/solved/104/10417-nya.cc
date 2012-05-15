/*
 * UVA 10417 Gift Exchanging
 * 2005-09-26
 * by nya
 */

#include <iostream>
#include <cstdio>

#define BOXES 5
#define MAX_FRIENDS 12


long long int search(int iFriend,
                     int* boxes,
                     const long long int (&probs)[MAX_FRIENDS][BOXES],
                     const int nFriends)
{
    if (iFriend == nFriends)
        return 1;
    long long int iProb = 0;
    for(int iBox=0; iBox<BOXES; iBox++) {
        if (boxes[iBox] > 0) {
            boxes[iBox]--;
            iProb += probs[iFriend][iBox] *
                search(iFriend+1, boxes, probs, nFriends);
            boxes[iBox]++;
        }
    }
    return iProb;
}

int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        int nFriends;
        std::cin >> nFriends;
        int boxes[BOXES];
        for(int i=0; i<BOXES; i++) {
            std::cin >> boxes[i];
        }
        long long int probs[MAX_FRIENDS][BOXES];
        for(int i=0; i<nFriends; i++) {
            for(int j=0; j<BOXES; j++) {
                double d;
                std::cin >> d;
                probs[i][j] = (long long int)(d*10 + 0.5);
            }
        }
        int iBestBox = -1;
        long long int iBestProb = -1;
        long long int iPreProb = 0;
        for(int iBox=0; iBox<BOXES; iBox++) {
            if (boxes[iBox] > 0) {
                boxes[iBox]--;
                long long int iProb =
                    probs[0][iBox] * search(1, boxes, probs, nFriends);
                boxes[iBox]++;
                iPreProb += iProb;
                if (iBestBox < 0 || iProb*boxes[iBestBox] > iBestProb*boxes[iBox]) {
                    iBestBox = iBox;
                    iBestProb = iProb;
                }
            }
        }
        std::printf("%d %.3lf\n", iBestBox+1,
                    ((double)iBestProb / iPreProb / boxes[iBestBox]));
    }
    return 0;
}
