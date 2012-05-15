/*
 * UVA 10816 Travel in Desert
 * 2005-07-21
 * by nya
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <list>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>


template<class T>
struct reverse_priority_queue : std::priority_queue<T, std::vector<T>, std::greater<T> > {
};


typedef std::vector< std::list< std::pair<int, std::pair<double, double> > > > Graph;

const int NOT_VISITED = -1;
const int TERMINAL = -2;

double dijkstra_temperature(const Graph& g, const int iSource, const int iDestination) {
    
    const int nNodes = g.size();

    reverse_priority_queue< std::pair<double,int> > q;
    std::vector<double> nodes(nNodes, 0.0);

    q.push( std::make_pair(20.0, iDestination) );

    while(! q.empty()) {

        const int iNode = q.top().second;
        const double temperature = q.top().first;
        q.pop();

        if (nodes[iNode] != 0.0)
            continue; // already visited

        nodes[iNode] = temperature;

        if (iNode == iSource)
            break;

        for(Graph::value_type::const_iterator it = g[iNode].begin();
            it != g[iNode].end();
            ++it) {
            if (nodes[it->first] == 0.0) {
                q.push( std::make_pair(
                            std::max(temperature, it->second.first),
                            it->first)
                    );
            }
        }

    }

    return nodes[iSource];
}

std::pair<double, std::vector<int> > dijkstra_route(const Graph& g, const int iSource, const int iDestination, const double temperature_limit) {

    const int nNodes = g.size();

    reverse_priority_queue< std::pair<double, std::pair<int, int> > > q;
    std::vector< std::pair<int, double> > nodes(nNodes, std::make_pair(NOT_VISITED, 0.0) );

    q.push( std::make_pair( 0.0, std::make_pair(iDestination, TERMINAL) ) );

    while(! q.empty()) {

        std::pair<double, std::pair<int, int> > data = q.top();
        q.pop();

        const int iNode = data.second.first;
        const int iPrevNode = data.second.second;
        const double length = data.first;

        if (nodes[iNode].first != NOT_VISITED)
            continue; // already visited

        nodes[iNode].first = iPrevNode;
        nodes[iNode].second = length;

        if (iNode == iSource)
            break;

        for(Graph::value_type::const_iterator it = g[iNode].begin();
            it != g[iNode].end();
            ++it) {
            if (nodes[it->first].first == NOT_VISITED &&
                it->second.first <= temperature_limit) {
                q.push( std::make_pair(
                            length + it->second.second,
                            std::make_pair(
                                it->first,
                                iNode)
                            )
                    );
            }
        }

    }

    std::vector<int> route;
    route.push_back(iSource);
    while(nodes[route.back()].first != TERMINAL) {
        route.push_back( nodes[route.back()].first );
    }

    return std::make_pair(
        nodes[iSource].second,
        route);
}


int main() {

    int nNodes, nLinks;
    while(std::cin >> nNodes >> nLinks) {

        int iSource, iDestination;
        std::cin >> iSource >> iDestination;
        iSource--; iDestination--;

        Graph g(nNodes);

        for(int i=0; i<nLinks; i++) {
            int iFrom, iTo;
            std::pair<double, double> condition;
            std::cin >> iFrom >> iTo >> condition.first >> condition.second;
            iFrom--; iTo--;
            g[iFrom].push_back( std::make_pair(iTo, condition) );
            g[iTo].push_back( std::make_pair(iFrom, condition) );
        }

        double temperature = dijkstra_temperature(g, iSource, iDestination);
        std::pair<double, std::vector<int> > route_info = dijkstra_route(g, iSource, iDestination, temperature);
        double length = route_info.first;
        std::vector<int>& route = route_info.second;

        for(int i=0; i<(int)route.size(); i++) {
            if (i > 0)
                std::cout << ' ';
            std::cout << (route[i]+1);
        }
        std::cout << std::endl;
        std::printf("%.1f %.1f\n", length, temperature);

    }
    return 0;
}




