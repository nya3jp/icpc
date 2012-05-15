/*
 * UVA 10448 Unique World
 * 2005-07-09
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 100000000;

typedef std::vector< std::vector<int> > links_type;

bool find_path(const links_type& links, std::vector<int>& route, int goal) {
    int pos = route.back();
    int prev = (route.size() >= 2 ? route[route.size()-2] : -1);
    if (pos == goal)
        return true;
    for(int i=0; i<links[pos].size(); i++) {
        if (i == prev) continue;
        if (links[pos][i] != INF) {
            route.push_back(i);
            if (find_path(links, route, goal))
                return true;
            route.pop_back();
        }
    }
    return false;
}


int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int nNodes, nLinks;
        std::cin >> nNodes >> nLinks;

        links_type links(nNodes, std::vector<int>(nNodes, INF));

        for(int i=0; i<nLinks; i++) {
            int a, b, d;
            std::cin >> a >> b >> d;
            a--; b--;
            links[a][b] = d;
            links[b][a] = d;
        }

        int nTests;
        std::cin >> nTests;

        if (iCase > 0)
            std::cout << std::endl;

        for(int iTest=0; iTest<nTests; iTest++) {

            int start, goal, total;
            std::cin >> start >> goal >> total;
            start--; goal--;

            std::vector<int> route;
            route.push_back(start);
            find_path(links, route, goal);

            std::vector<int> loops;
            for(int i=0; i+2<route.size(); i++) {
                loops.push_back( links[route[i]][route[i+1]] * 2 );
            }

            int min_dist = 0;
            for(int i=0; i+1<route.size(); i++) {
                min_dist += links[route[i]][route[i+1]];
            }

            int dist_limit = total - min_dist;
            if (dist_limit < 0 || dist_limit%2 != 0) {
                std::cout << "No" << std::endl;
            }
            else if (dist_limit == 0) {
                std::cout << "Yes " << (route.size()-1) << std::endl;
            }
            else {
                std::vector<int> v(dist_limit+1, INF);
                v[0] = 0;
                for(int n=0; n<loops.size(); n++) {
                    int c = loops[n];
                    for(int i=c; i<=dist_limit; i++) {
                        if (v[i-c] != INF && v[i-c] + 2 < v[i]) {
                            v[i] = v[i-c] + 2;
                        }
                    }
                    /*
                    for(int i=0; i<=dist_limit; i++) {
                        std::cout << v[i] << " ";
                    }
                    std::cout << std::endl;
                    */
                }
                if (v[dist_limit] < INF) {
                    std::cout << "Yes " << (route.size()-1+v[dist_limit]) << std::endl;
                }
                else {
                    std::cout << "No" << std::endl;
                }
            }

        }

    }

    return 0;
}
