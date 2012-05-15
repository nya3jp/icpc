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
    int time;
    Node() {
    }
    Node(int floor, int prev, int time) : floor(floor), prev(prev), time(time) {
    }
};
inline bool operator>(const Node& a, const Node& b) {
    return (a.time > b.time);
}

int solve(const std::vector<bool>& dests, std::vector<int>& result) {
    std::vector<bool> visited(FLOORS+1, false);
    Node nodes[FLOORS+1];

    int lastFloor = FLOORS;
    while(!dests[lastFloor])
        lastFloor--;

    //std::printf("Lastfloor: %d\n", lastFloor);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node> > q;

    q.push(Node(0, -1, -COST_STOP));
    while(! q.empty()) {
        Node node = q.top();
        q.pop();

        if (visited[node.floor])
            continue;

        //std::printf("stop at %d floor : time = %d\n", node.floor, node.time);

        visited[node.floor] = true;
        nodes[node.floor] = node;

        if (node.floor == lastFloor)
            break;

        for(int nextFloor = node.floor+1; nextFloor <= lastFloor; nextFloor++) {
            int stopTime = node.time + COST_STOP + COST_ELVT*(nextFloor-node.floor);
            int newTime = stopTime;
            for(int floor = node.floor+1; floor < nextFloor; floor++) {
                if (dests[floor]) {
                    int time = std::min(stopTime + (nextFloor-floor)*COST_WALK,
                                        node.time + (floor-node.floor)*COST_WALK);
                    newTime = std::max(newTime, time);
                }
            }

            //std::printf("  Cand: %d floor %d\n", nextFloor, newTime);
            q.push(Node(nextFloor, node.floor, newTime));
        }
    }

    std::vector<int>& route = result;
    route.clear();
    for(int floor = lastFloor; floor != 0; floor = nodes[floor].prev) {
        route.push_back(floor);
    }
    std::reverse(route.begin(), route.end());

    return nodes[lastFloor].time;
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


