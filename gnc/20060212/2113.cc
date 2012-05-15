#include <cstdio>
#include <cassert>

using namespace std;

int main() {
    bool v[500][500];

    int n, e;
    while(scanf("%d%d", &n, &e) == 2 && !(n == 0 && e == 0)) {
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                v[i][j] = false;

        for(int i=0; i<e; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            v[a][b] = v[b][a] = true;
        }

        struct damepo {};
        try {
            for(int i=0; i<n; i++)
                for(int j=i+1; j<n; j++)
                    if (v[i][j])
                        for(int k=j+1; k<n; k++)
                            if (v[i][k] && v[j][k])
                                for(int l=k+1; l<n; l++)
                                    if (v[i][l] && v[j][l] && v[k][l])
                                        throw damepo();
            int team[500];
            for(int i = 0; i < n; i++) {
                team[i] = -1;
                for(int t=0; t<3; t++) {
                    for(int j = 0; j < i; j++) {
                        if (v[i][j] && team[j] == t)
                            goto next;
                    }
                    team[i] = t;
                    break;
                next:;
                }
                if (team[i] < 0)
                    *(int*)123 = 0;
                printf("%d%s", team[i], (i < n-1 ? " " : "\n"));
            }
        }
        catch(damepo) {
            printf("The agents cannot be split\n");
        }
    }

    return 0;
}


