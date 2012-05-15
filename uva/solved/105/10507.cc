#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    while(scanf("%d", &n) == 1) {

        int m;
        scanf("%d", &m);

        vector<bool> awake(26, false);
        bool adj[26][26];
        for(int i = 0; i < 26; i++)
            fill(adj[i], adj[i]+26, false);

        for(int i = 0; i < 3; i++) {
            char c;
            scanf(" %c", &c);
            awake[(int)(c - 'A')] = true;
        }

        for(int i = 0; i < m; i++) {
            char c1, c2;
            scanf(" %c %c", &c1, &c2);
            int a = (int)(c1 - 'A'), b = (int)(c2 - 'A');
            adj[a][b] = adj[b][a] = true;
        }

        int years = 0;
        while(count(awake.begin(), awake.end(), true) < n) {
            vector<int> stim(26, 0);
            for(int i = 0; i < 26; i++) {
                for(int j = 0; j < 26; j++)
                    if (adj[i][j] && awake[j])
                        stim[i]++;
            }
            bool halt = true;
            for(int i = 0; i < 26; i++) {
                if (stim[i] >= 3 && !awake[i]) {
                    awake[i] = true;
                    halt = false;
                }
            }
            if (halt) {
                years = -1;
                break;
            }
            years++;
        }

        if (years < 0) {
            printf("THIS BRAIN NEVER WAKES UP\n");
        }
        else {
            printf("WAKE UP IN, %d, YEARS\n", years);
        }

    }
    return 0;
}
