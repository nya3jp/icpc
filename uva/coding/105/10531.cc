#include <iostream>
#include <vector>
#include <cstdio>
#include <numeric>
#include <algorithm>

using namespace std;

#define H 5
#define W 6
#define WS (1<<W)

int h, w;

typedef long double decimal;

decimal barrierProbs[H][W];

decimal calcValidProb(int bi, int bj) {
    const int ws = 1<<w;
    decimal probs[WS];
    fill(probs, probs+ws, 0);
    probs[1] = 1;

    for(int i = 0; i < h; i++) {

        decimal nextprobs[WS];
        fill(nextprobs, nextprobs+ws, 0);

        for(int last = 0; last < ws; last++) {
            for(int ptn = 0; ptn < ws; ptn++) {
                if (i == bi && (ptn&(1<<bj)) != 0)
                    continue;
                decimal p = probs[last];
                for(int j = 0; j < w; j++)
                    p *= ((ptn&(1<<j)) == 0 ? barrierProbs[i][j] : 1-barrierProbs[i][j]);
                int next = last&ptn;
                for(int x = 0; x < w-1; x++)
                    next |= ((next<<1)|(next>>1))&ptn;
                nextprobs[next] += p;
            }
        }

        copy(nextprobs, nextprobs+ws, probs);
    }

    decimal sum = 0;
    for(int ptn = (ws>>1); ptn < ws; ptn++)
        sum += probs[ptn];
    return sum;
}



void solve() {

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            printf("%.6f", (double)(calcValidProb(i, j) / calcValidProb(-1, -1)));
            //printf("(=%.3f/%.3f)", (double)calcValidProb(i, j), (double)calcValidProb(-1, -1));
            printf(j == w-1 ? "\n" : " ");
        }
    }

}


int main() {

    int nCases;
    cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        if (iCase > 0)
            printf("\n");

        cin >> h >> w;

        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                cin >> barrierProbs[i][j];

        solve();

    }

    return 0;
}


