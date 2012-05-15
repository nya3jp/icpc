/*
 * UVA 10421 Critical Wave
 * 2005-07-17
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

typedef std::pair<int,int> Point;
typedef std::pair<Point,bool> Node;

#define N 0x10000

int main() {
    int n;
    std::vector<int> v(N*2);
    std::vector<Node> ps;
    while(std::cin >> n) {
        ps.clear();
        ps.reserve(n*2);
        for(int i=0; i<n; i++) {
            Point p;
            std::cin >> p.first >> p.second;
            p.second += N/2;
            if (p.second < N-2) {
                ps.push_back( std::make_pair(std::make_pair(p.first, p.second+1), false ) );
            }
            if (p.second >= 2) {
                ps.push_back( std::make_pair(std::make_pair(p.first, p.second-1), true ) );
            }
        }
        std::sort(ps.begin(), ps.end());
        std::fill(v.begin(), v.end(), 0);

        for(int i=0; i<ps.size(); ) {
            int k;
            for(k=1; i+k<ps.size(); k++) {
                if (ps[i+k].first != ps[i].first)
                    break;
            }
            int kup=std::upper_bound(ps.begin()+i, ps.begin()+i+k, std::make_pair(ps[i].first, false)) - (ps.begin()+i);
            int kdown=k-kup;
            int y = ps[i].first.second;
            //bool down = ps[i].second;
            //v[y+(down?N:0)] = std::max(v[y+(down?N:0)], v[y+(down?0:N)]+k);
            int u, d;
            u = v[y];
            d = v[y+N];
            if (kup > 0)
                v[y] = std::max(u, d+1);
            if (kdown > 0)
                v[y+N] = std::max(d, u+1);
            //std::cerr << "i=" << i << " (" << ps[i].first.first << "," << ps[i].first.second << ") : up=" << kup << ", kdown=" << kdown << std::endl;
             i += k;
        }

        std::cout << *std::max_element(v.begin(), v.end()) << std::endl;
    }
    return 0;
}
