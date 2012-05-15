/*
 * UVA 10457 Magic Car
 * 2005-08-27
 * by nya
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <queue>
#include <set>
#include <cassert>

typedef std::vector< std::list< std::pair<int, int> > > AdjList;

const int INF = 0x7fffffff; // std::numeric_limits<int>::max();

struct Range {
    int min, max;
    Range(int min, int max) : min(min), max(max) {}
    friend bool operator<(const Range& a, const Range& b) {
        return ( (a.max-a.min) > (b.max-b.min) );
    }
};

int solve(const AdjList& adj, const int iSource, const int iDestination) {
    std::priority_queue< std::pair<Range, int> > q;
    std::vector< std::set< std::pair<int, int> > > mem(adj.size());
    q.push( std::make_pair( Range(INF, 0), iSource ) );

    while(! q.empty()) {

        Range range = q.top().first;
        int iNode = q.top().second;
        q.pop();

        if (iNode == iDestination)
            return (range.max - range.min);

        {
            std::set< std::pair<int, int> >& s = mem[iNode];
            std::set< std::pair<int, int> >::iterator first = s.lower_bound( std::make_pair(range.min, 0) );
            std::set< std::pair<int, int> >::iterator last = s.lower_bound( std::make_pair(range.max+1, 0) );
            bool ok = true;
            for(std::set< std::pair<int, int> >::iterator it = first; it != last; ++it) {
                if (range.min <= it->first && it->second <= range.max) {
                    ok = false;
                    break;
                }
            }
            if (! ok)
                continue;
            s.insert( std::make_pair(range.min, range.max) );
        }

        //std::cerr << "Visit " << (iNode+1) << " with (" << range.min << "," << range.max << ")" << std::endl;

        const AdjList::value_type& adjl = adj[iNode];
        for(AdjList::value_type::const_iterator it = adjl.begin(); it != adjl.end(); ++it) {
            q.push( std::make_pair(
                             Range( std::min(range.min, it->second),
                                    std::max(range.max, it->second) ),
                             it->first ) );
        }

    }

    assert(false);
    return 0;
}

int main() {
    int nNodes, nLinks;
    while(std::cin >> nNodes >> nLinks) {
        AdjList adj(nNodes);
        for(int i=0; i<nLinks; i++) {
            int a, b, s;
            std::cin >> a >> b >> s;
            a--; b--;
            adj[a].push_back( std::make_pair(b, s) );
            adj[b].push_back( std::make_pair(a, s) );
        }
        int iInitCost, iStopCost;
        std::cin >> iInitCost >> iStopCost;
        int nQueries;
        std::cin >> nQueries;
        for(int i=0; i<nQueries; i++) {
            int a, b;
            std::cin >> a >> b;
            a--; b--;
            std::cout << (iInitCost + iStopCost + solve(adj, a, b)) << std::endl;
        }
    }
    return 0;
}
