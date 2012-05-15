/*
 * UVA 10449 Traffic
 * 2005-08-20
 * by nya
 */

#define NDEBUG

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

#undef assert

inline void assert(bool x) {
    if (!x)
        *(char*)0=1;
}

const int INF = 0x7fffffff;

typedef std::vector< std::list<int> > AdjList;

template<class T>
struct matrix : public std::vector< std::vector<T> > {
    matrix(int n, T def = T())
        : std::vector< std::vector<int> >(n, std::vector<int>(n, def)) {
    }
};
typedef matrix<int> AdjMatrix;

int back_traverse(int p, const AdjMatrix& m, const AdjList& l, std::vector<int>& mem) {
    if (mem[p] < 0) {
        mem[p] = 0;
        int r = (p == 0 ? 1 : 0);
        for(AdjList::value_type::const_iterator it = l[p].begin();
            it != l[p].end();
            ++it) {
            r = std::max(r, back_traverse(*it, m, l, mem));
        }
        if (r >= 1 && m[p][p] < 0)
            r = 2;
        mem[p] = r;

#ifndef NDEBUG
        std::cout << " " << (p+1) << "=" << r;
#endif
    }
    return mem[p];
}

int main() {
    int iCase = 0;
    int n;
    while(std::cin >> n) {
        std::vector<int> b(n);
        for(int i=0; i<n; i++)
            std::cin >> b[i];
        AdjMatrix v(n, INF);
        AdjList l(n);
        for(int i=0; i<n; i++)
            v[i][i] = 0;

        int m;
        std::cin >> m;
        for(int i=0; i<m; i++) {
            int p, q;
            std::cin >> p >> q;
            p--; q--;
            int d = b[q]-b[p];
            v[p][q] = d*d*d;
            l[q].push_back(p);
            //v[q][p] = -d*d*d;
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if (v[j][i] != INF) {
                    for(int k=0; k<n; k++) {
                        if (v[i][k] != INF) {
                            v[j][k] = std::min(v[j][k], v[j][i]+v[i][k]);
                        }
                    }
                }
            }
        }

#ifndef NDEBUG
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                std::cout << v[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
#endif

        std::vector<int> loop(n, -1);
        for(int i=0; i<n; i++) {
            std::vector<int> mem(n, -1);
#ifndef NDEBUG
            std::cout << "back_traverse";
#endif
            loop[i] = ( back_traverse(i, v, l, mem) == 2 );
#ifndef NDEBUG
            std::cout << std::endl;
#endif
        }

        std::cout << "Set #" << (++iCase) << std::endl;
        int q;
        std::cin >> q;
        for(int i=0; i<q; i++) {
            int p;
            std::cin >> p;
            p--;
            int d = v[0][p];
            if (loop[p])
                d = 0;

#ifndef NDEBUG
            std::cout << (p+1) << " -> loop=" << loop[p] << " dist=";
#endif

            if (d == INF)
                d = 0;
            //assert(d != INF);

            if (d < 3)
                std::cout << "?" << std::endl;
            else
                std::cout << d << std::endl;
        }
    }
    return 0;
}

