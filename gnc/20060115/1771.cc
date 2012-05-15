#include <cstdio>
#include <queue>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

#define FLOORS 30
#define COST_ELVT 4
#define COST_STOP 10
#define COST_WALK 20

const int INFTY = std::numeric_limits<int>::max();

struct Node {
    int floor;
    int prev;
    int stops;
    int time;
    Node() {
    }
    Node(int floor, int prev, int stops, int time) : floor(floor), prev(prev), stops(stops), time(time) {
    }
};
inline bool operator>(const Node& a, const Node& b) {
    return (a.time > b.time);
}

int solve(const std::vector<bool>& dests, std::vector<int>& result) {
    bool visited[FLOORS+1][FLOORS+1];
    for(int i=0; i<=FLOORS; i++)
        for(int j=0; j<=FLOORS; j++)
            visited[i][j] = false;
    Node nodes[FLOORS+1][FLOORS+1];

    int lastFloor = FLOORS;
    while(!dests[lastFloor])
        lastFloor--;

    //std::printf("Lastfloor: %d\n", lastFloor);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node> > q;

    Node lastNode;

    q.push(Node(0, -1, 0, 0));
    while(! q.empty()) {
        Node node = q.top();
        q.pop();

        if (visited[node.floor][node.stops])
            continue;

        //std::printf("stop at %d floor at %d : time = %d\n", node.floor, node.stops, node.time);

        visited[node.floor][node.stops] = true;
        nodes[node.floor][node.stops] = node;

        if (node.floor == lastFloor) {
            lastNode = node;
            break;
        }

        for(int nextFloor = node.floor+1; nextFloor <= lastFloor; nextFloor++) {
            int stopTime = node.floor*COST_ELVT + (node.stops-1)*COST_STOP;
            int nextStopTime = nextFloor*COST_ELVT + node.stops*COST_STOP;
            //node.time + COST_STOP + COST_ELVT*(nextFloor-node.floor);
            int newTime = node.time;
            for(int floor = node.floor+1; floor <= nextFloor; floor++) {
                if (dests[floor]) {
                    int time = INFTY;
                    time = std::min(time, nextStopTime + (nextFloor-floor)*COST_WALK);
                    if (node.floor != 0)
                        time = std::min(time, stopTime + (floor-node.floor)*COST_WALK);
                    else
                        time = std::min(time, (floor-node.floor)*COST_WALK);

                    newTime = std::max(newTime, time);
                }
            }

            //std::printf("  Cand: %d floor %d\n", nextFloor, newTime);
            q.push(Node(nextFloor, node.floor, node.stops+1, newTime));
        }
    }

    int tripTime = lastNode.time;
    std::vector<int>& route = result;
    route.clear();
    while(lastNode.floor != 0) {
        route.push_back(lastNode.floor);
        lastNode = nodes[lastNode.prev][lastNode.stops-1];
    }
    assert(lastNode.stops == 0);
    std::reverse(route.begin(), route.end());

    return tripTime;
}



int main() {
    while(true) {
        int n;
        std::scanf("%d", &n);
        if (n == 0)
            break;

        std::vector<bool> dests(FLOORS+1, false);
        assert(dests.size() == FLOORS+1);
        for(int i = 0; i < n; i++) {
            int k;
            std::scanf("%d", &k);
            dests[k-1] = true;
            //std::printf("> person at %d\n", k);
        }

        std::vector<int> route;
        int time = solve(dests, route);

        std::printf("%d\n%d", time, (int)route.size());
        for(int i = 0; i < (int)route.size(); i++) {
            std::printf(" %d", route[i]+1);
        }
        std::printf("\n");

    }
    return 0;
}


