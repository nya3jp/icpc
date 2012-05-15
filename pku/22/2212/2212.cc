#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

bool field[110][110][110];

int height, width, depth;

struct P {
    int x, y, z;
};

void read_case() {
    scanf("%d%d%d", &height, &width, &depth);
    REP(i, height+2) REP(j, width+2) REP(k, depth+2)
        field[i][j][k] = false;
    for(int d = 1; d <= depth; d++) {
        int m;
        scanf("%d", &m);
        REP(t, m) {
            int i, j;
            scanf("%d%d", &i, &j);
            field[i][j][d] = true;
        }
    }
}

int solve() {
    int res = 0;

    vector<P> st;
    REP(i, height+2) REP(j, width+2) {
        if (field[i][j][1]) {
            st.push_back((P){i, j, 1});
            field[i][j][1] = false;
            res++;
        }
    }

    while(!st.empty()) {
        P here = st.back();
        st.pop_back();
        //printf("(%d,%d,%d)\n", here.x, here.y, here.z);
        {
            P there(here);
            there.x++;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
        {
            P there(here);
            there.x--;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
        {
            P there(here);
            there.y++;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
        {
            P there(here);
            there.y--;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
        {
            P there(here);
            there.z++;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
        {
            P there(here);
            there.z--;
            if (field[there.x][there.y][there.z]) {
                st.push_back(there);
                field[there.x][there.y][there.z] = false;
                res++;
            }
        }
    }

    return res;
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {
        read_case();
        printf("Je nutne vycerpat %d litru vody.\n",
               solve()*1000);
    }

    return 0;
}
