/*
 * UVA 10801 Lift Hopping
 * 2005-01-29
 * by nya
 */

#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <iterator>
#include <cmath>
#include <cassert>

using namespace std;

#define ELEVATORS  5
#define FLOORS     100
#define INFINITE   1000000000
#define FLOOR_COST 60

struct Node {
    int cost;
    bool visited;
    Node() : cost(0), visited(false) {}
};

struct DijkstraNode {
    int iFloor;
    int iElevator;
    int cost;
    DijkstraNode(int iFloor, int iElevator, int cost) : iFloor(iFloor), iElevator(iElevator), cost(cost) {}
};

bool operator<(const DijkstraNode& a, const DijkstraNode& b) {
    return (a.cost > b.cost);
}

set<int> elevators[ELEVATORS];
bool visited[FLOORS][ELEVATORS];
int costs[ELEVATORS];
int nElevators, iDestinationFloor;

int doDijkstra()
{
    priority_queue<DijkstraNode> pq;

    for(int iElevator=0; iElevator<nElevators; iElevator++) {
        set<int>& elevator = elevators[iElevator];
        if (elevator.find(0) != elevator.end())
            pq.push(DijkstraNode(0, iElevator, 0));
    }

    while(! pq.empty()) {
        DijkstraNode dij = pq.top();
        pq.pop();

        if (dij.iFloor == iDestinationFloor)
            return dij.cost;

        if (visited[dij.iFloor][dij.iElevator])
            continue;

        //cerr << "Floor " << dij.iFloor << ", Elevator " << dij.iElevator << ": " << dij.cost << endl;

        visited[dij.iFloor][dij.iElevator] = true;

        {
            set<int>& elevator = elevators[dij.iElevator];
            for(set<int>::iterator it = elevator.begin(); it != elevator.end(); ++it) {
                if (*it != dij.iFloor) {
                    if (! visited[*it][dij.iElevator]) {
                        pq.push(DijkstraNode(*it, dij.iElevator, dij.cost + (costs[dij.iElevator] * abs(dij.iFloor - *it))));
                    }
                }
            }
        }
        {
            for(int iElevator=0; iElevator<nElevators; iElevator++) {
                if (iElevator != dij.iElevator) {
                    set<int>& elevator = elevators[iElevator];
                    if (elevator.find(dij.iFloor) != elevator.end()) {
                        if (! visited[dij.iFloor][iElevator]) {
                            pq.push(DijkstraNode(dij.iFloor, iElevator, dij.cost + FLOOR_COST));
                        }
                    }
                }
            }
        }
    }

    return -1;
}


int main(int argc, char** argv)
{
    while(true) {
        cin >> nElevators >> iDestinationFloor;
        if (! cin) break;

        assert(nElevators <= ELEVATORS);
        assert(iDestinationFloor < FLOORS);

        for(int iElevator=0; iElevator<nElevators; iElevator++) {
            elevators[iElevator].clear();
        }
        for(int iFloor=0; iFloor<FLOORS; iFloor++) {
            for(int iElevator=0; iElevator<nElevators; iElevator++) {
                visited[iFloor][iElevator] = false;
            }
        }

        for(int iElevator=0; iElevator<nElevators; iElevator++) {
            cin >> costs[iElevator];
        }
        cin >> ws;

        for(int iElevator=0; iElevator<nElevators; iElevator++) {
            string line;
            getline(cin, line);
            istringstream is(line);
            for(istream_iterator<int> it(is); it != istream_iterator<int>(); ++it) {
                elevators[iElevator].insert(*it);
            }
        }

        int cost = doDijkstra();

        if (cost < 0)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << cost << endl;
    }

    return 0;
}


