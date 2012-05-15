/*
 * 10513 Bangladesh Sequences
 * 2005-10-02
 * by nya
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define N 15

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

struct Solver {

    bool horz[N];
    bool left[N*2-1];
    bool right[N*2-1];
    int seq[N];

    std::vector<int*> ans[N+1];

    Solver() {
        std::fill(horz, horz+N, false);
        std::fill(left, left+N*2+1, false);
        std::fill(right, right+N*2+1, false);
        for(int n=10; n<=N; n++) {
            search(0, n, -10, -10);
        }
    }
    ~Solver() {
        for(int i=0; i<=N; i++) {
            std::vector<int*>& v = ans[i];
            for(int j=0; j<(int)v.size(); j++)
                delete[] v[j];
        }
    }

    int solve(const int n, const bool (&constraints)[N][N]) {
        const std::vector<int*>& v = ans[n];
        const int m = v.size();
        int c = 0;
        for(int i=0; i<m; i++) {
            const int* u = v[i];
            for(int j=0; j<n; j++) {
                if (!constraints[j][u[j]])
                    goto NOT_MATCH;
            }
            c++;
        NOT_MATCH:;
        }
        return c;
    }

    void search(const int i, const int n, const int p1, const int p2) {
        if (i == n) {
            int* v = new int[n];
            for(int j=0; j<n; j++)
                v[j] = seq[j];
            ans[n].push_back(v);
        }
        else {
            for(int j=0; j<n; j++) {
                int jleft = i+j;
                int jright = i-j+n-1;
                if (abs(j-p1)>2 && abs(j-p2)>2 &&
                    !horz[j] &&
                    !left[jleft] &&
                    !right[jright]) {
                    seq[i] = j;
                    horz[j] = true;
                    left[jleft] = true;
                    right[jright] = true;
                    search(i+1, n, j, p1);
                    horz[j] = false;
                    left[jleft] = false;
                    right[jright] = false;
                }
            }
        }
    }
};



int main() {

    Solver solver;

    if (0) {
        int n = 10;
        std::vector<int*>& v = solver.ans[n];
        std::printf("%d solutions:\n", v.size());
        for(int i=0; i<v.size(); i++) {
            int* u = v[i];
            for(int j=0; j<n; j++) {
                for(int l=0; l<u[j]; l++)
                    std::printf(" ");
                std::printf("*\n");
            }
            std::printf("---------------\n");
        }
    }

    int iCase = 0;
    int n;
    while( std::scanf("%d", &n) == 1 && n != 0 ) {

        bool constraints[N][N];
        unsigned long long int total = 1;
        for(int i=0; i<n; i++) {
            std::fill(constraints[i], constraints[i]+N, false);
            char s[64];
            std::scanf("%s", s);
            int m = std::strlen(s);
            if (std::strcmp(s, "?") == 0) {
                std::fill(constraints[i], constraints[i]+n, true);
                total *= n;
            }
            else {
                for(int j=0; j<m; j++) {
                    constraints[i][ (int)(s[j] - 'A') ] = true;
                }
                total *= m;
            }
        }

        std::printf("Case %d: %llu\n", ++iCase, (total - (unsigned long long int)solver.solve(n, constraints)));

    }

    return 0;
}
