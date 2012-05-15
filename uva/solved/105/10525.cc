#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
//#include <limits>

template<class Fst, class Snd>
std::pair<Fst, Snd> operator+(const std::pair<Fst, Snd>& left,
                              const std::pair<Fst, Snd>& right)
{
    return std::make_pair(left.first+right.first,
                          left.second+right.second);
}

template<class G, class C>
void dijkstra(const G& g,
              int iNodeFrom,
              int iNodeTo,
              std::vector<C>& costs,
              std::vector<int>& prevs,
              const C& cost_zero,
              const C& cost_infty)
{
    const int nNodes = g.size();

    std::vector<bool> visited(nNodes, false);
    costs.resize(nNodes);
    prevs.resize(nNodes);
    std::fill(costs.begin(), costs.end(), cost_infty);
    std::fill(prevs.begin(), prevs.end(), -1);

    typedef std::pair<C, std::pair<int, int> > K;
    std::priority_queue<K, std::vector<K>, std::greater<K> > q;
    q.push( std::make_pair(cost_zero, std::make_pair(iNodeFrom, -1)) );

    while(! q.empty())
    {
        C currentCost = q.top().first;
        int iCurrentNode = q.top().second.first;
        int iPreviousNode = q.top().second.second;
        q.pop();

        if (visited[iCurrentNode])
            continue;

        costs[iCurrentNode] = currentCost;
        prevs[iCurrentNode] = iPreviousNode;
        visited[iCurrentNode] = true;

        if (iCurrentNode == iNodeTo)
            break;

        for(typename G::value_type::const_iterator it = g[iCurrentNode].begin();
            it != g[iCurrentNode].end();
            ++it)
        {
            int iNextNode = it->first;
            C costToNextNode = it->second;

            if (visited[iNextNode])
                continue;

            C newCost = currentCost + costToNextNode;
            q.push( std::make_pair(newCost, std::make_pair(iNextNode, iCurrentNode)) );
        }
    }
}




typedef int Time;
typedef int Length;
typedef std::pair<Time, Length> Cost;
typedef std::vector< std::list< std::pair<int, Cost> > > WeighedGraph;

/*
Cost cost_infty(std::numeric_limits<int>::max(),
                std::numeric_limits<int>::max());
*/
Cost cost_infty(0x7fffffff, 0x7fffffff);

int main(int argc, char** argv)
{
    /*
    if (argc >= 2)
        freopen(argv[1], "r", stdin);
    */

    int nCases;
    std::cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++)
    {
        int nNodes, nLinks;
        std::cin >> nNodes >> nLinks;

        WeighedGraph g(nNodes);

        for(int iLink = 0; iLink < nLinks; iLink++)
        {
            int iNodeFrom, iNodeTo;
            Time time;
            Length length;
            std::cin >> iNodeFrom >> iNodeTo >> time >> length;
            iNodeFrom--; iNodeTo--;

            g[iNodeFrom].push_back( std::make_pair( iNodeTo, Cost(time, length) ) );
            g[iNodeTo].push_back( std::make_pair( iNodeFrom, Cost(time, length) ) );
        }

        if (iCase > 0)
            std::cout << std::endl;

        int nQueries;
        std::cin >> nQueries;
        for(int iQuery = 0; iQuery < nQueries; iQuery++)
        {
            int iNodeFrom, iNodeTo;
            std::cin >> iNodeFrom >> iNodeTo;
            iNodeFrom--; iNodeTo--;

            std::vector<Cost> costs(nNodes);
            std::vector<int> prevs(nNodes);

            dijkstra(g,
                     iNodeFrom,
                     iNodeTo,
                     costs,
                     prevs,
                     Cost(0, 0),
                     cost_infty);

            const Cost& cost = costs[iNodeTo];

            if (cost == cost_infty)
            {
                std::cout << "No Path." << std::endl;
            }
            else {
                std::cout << "Distance and time to reach destination is "
                          << cost.second
                          << " & "
                          << cost.first
                          << "."
                          << std::endl;
            }
        }
    }
    return 0;
}
