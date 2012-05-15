/*
 * UVA 334 Identifying Concurrent Events
 * 2005-07-04
 * coded by nya
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <assert.h>

template<class T>
struct matrix : public std::vector< std::vector<T> >
{
    typedef std::vector<T> vector_type;
    typedef std::vector<vector_type> matrix_type;
    matrix(int n, int m, const T& value = T())
        : matrix_type(n, vector_type(m, value)) {
    }
};


int main() {

    int iCase = 0;
    while(true) {
        int n;
        std::cin >> n;
        if (n == 0)
            break;

        std::vector< std::vector<std::string> > comps;
        comps.resize(n);

        for(int i=0; i<n; i++) {
            std::vector<std::string>& c = comps[i];
            int k;
            std::cin >> k;
            for(int j=0; j<k; j++) {
                std::string s;
                std::cin >> s;
                c.push_back(s);
            }
        }

        int nids = 0;

        for(int i=0; i<comps.size(); i++) {
            nids += comps[i].size();
        }

        std::map<std::string,int> nametoid;
        std::vector<std::string> idtoname(nids);
        matrix<bool> dep(nids, nids, false);

        {
            int id = 0;
            for(int i=0; i<comps.size(); i++) {
                const std::vector<std::string>& c = comps[i];
                for(int j=0; j<c.size(); j++) {
                    if (j+1 < c.size())
                        dep[id][id+1] = true;
                    nametoid[c[j]] = id;
                    idtoname[id] = c[j];
                    id++;
                }
            }
            assert(id == nids);
        }

        int m;
        std::cin >> m;
        for(int i=0; i<m; i++) {
            std::string s, t;
            std::cin >> s >> t;
            dep[ nametoid[s] ][ nametoid[t] ] = true;
        }

        for(int k=0; k<nids; k++) {
            for(int i=0; i<nids; i++) {
                if (dep[i][k]) {
                    for(int j=0; j<nids; j++) {
                        if (dep[k][j]) {
                            dep[i][j] = true;
                        }
                    }
                }
            }
        }

        int ncons = 0;
        int pairs[2][2];
        for(int i=0; i<nids; i++) {
            for(int j=i+1; j<nids; j++) {
                if (!dep[i][j] && !dep[j][i]) {
                    if (ncons < 2) {
                        pairs[ncons][0] = i;
                        pairs[ncons][1] = j;
                    }
                    ncons++;
                }
            }
        }

        std::cout << "Case " << (++iCase) <<", ";
        if (ncons == 0) {
            std::cout << "no concurrent events." << std::endl;
        }
        else {
            std::cout << ncons << " concurrent events:" << std::endl;
            for(int i=0; i<std::min(ncons, 2); i++) {
                if (i > 0)
                    std::cout << " ";
                std::cout << "(" << idtoname[pairs[i][0]]
                          << "," << idtoname[pairs[i][1]] << ")";
            }
            std::cout << std::endl;
        }

    }

    return 0;
}
