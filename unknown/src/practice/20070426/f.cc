#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 200

int adj[N][N];

int main() {

    for(;;) {
        int n;
        //cin >> n;
        scanf("%d", &n);
        if (n == 0)
            break;

        REP(i, n) REP(j, n)
            adj[i][j] = 0;

        for(;;) {
            int a, b;
            //cin >> a >> b;
            scanf("%d%d", &a, &b);
            if (a == 0 && b == 0)
                break;
            //string s;
            //cin >> s;
            char buf[32];
            scanf("%s", buf);

            a--; b--;
            int c = 0;
            /*
            REP(i, s.size())
                c |= 1 << (int)(s[i] - 'a');
            */
            REP(i, strlen(buf))
                c |= 1 << (int)(buf[i] - 'a');
            //printf("adj[%d][%d] = %d\n", a, b, c);
            adj[a][b] = c;
        }

        REP(j, n) REP(i, n) REP(k, n)
            adj[i][k] |= adj[i][j] & adj[j][k];

        for(;;) {
            int a, b;
            //cin >> a >> b;
            scanf("%d%d", &a, &b);
            if (a == 0 && b == 0)
                break;
            a--; b--;

            int c = adj[a][b];
            bool empty = true;
            REP(i, 26) {
                if (c & (1<<i)) {
                    //cout << (char)('a' + i);
                    printf("%c", (char)('a' + i));
                    empty = false;
                }
            }
            if (empty)
                //cout << '-';
                printf("-");
            //cout << endl;
            printf("\n");

        }

        //cout << endl;
        printf("\n");

    }

    return 0;
}

