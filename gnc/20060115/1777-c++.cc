#include <cstdio>
#include <queue>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

using namespace std;

#define mymax(a,b) ((a)>(b)?(a):(b))
#define mymin(a,b) ((a)<(b)?(a):(b))

#define FLOORS 30
#define COST_ELVT 4
#define COST_STOP 10
#define COST_WALK 20

const int INFTY = numeric_limits<int>::max();

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

int solve(const vector<bool>& dests, vector<int>& result) {
    vector<bool> visited(FLOORS+1, false);
    Node nodes[FLOORS+1];

    int lastFloor = FLOORS;
    while(!dests[lastFloor])
        lastFloor--;

    //printf("Lastfloor: %d\n", lastFloor);

    priority_queue<Node, vector<Node>, greater<Node> > q;

    q.push(Node(0, -1, -COST_STOP));
    while(! q.empty()) {
        Node node = q.top();
        q.pop();

        if (visited[node.floor])
            continue;

        //printf("stop at %d floor : time = %d\n", node.floor, node.time);

        visited[node.floor] = true;
        nodes[node.floor] = node;

        if (node.floor == lastFloor)
            break;

        for(int nextFloor = node.floor+1; nextFloor <= lastFloor; nextFloor++) {
            int stopTime = node.time + COST_STOP + COST_ELVT*(nextFloor-node.floor);
            int newTime = stopTime;
            for(int floor = node.floor+1; floor < nextFloor; floor++) {
                if (dests[floor]) {
                    int time = mymin(stopTime + (nextFloor-floor)*COST_WALK,
                                        node.time + (floor-node.floor)*COST_WALK);
                    newTime = mymax(newTime, time);
                }
            }

            //printf("  Cand: %d floor %d\n", nextFloor, newTime);
            q.push(Node(nextFloor, node.floor, newTime));
        }
    }

    vector<int>& route = result;
    route.clear();
    for(int floor = lastFloor; floor != 0; floor = nodes[floor].prev) {
        route.push_back(floor);
    }
    reverse(route.begin(), route.end());

    return nodes[lastFloor].time;
}



int main() {
    while(true) {
        int n;
        int i;
        scanf("%d", &n);
        if (n == 0)
            break;

        vector<bool> dests(FLOORS+1, false);
        for(i = 0; i < n; i++) {
            int k;
            scanf("%d", &k);
            dests[k-1] = true;
            //printf("> person at %d\n", k);
        }

        vector<int> route;
        int time = solve(dests, route);

        printf("%d\n%d", time, (int)route.size());
        for(i = 0; i < (int)route.size(); i++) {
            printf(" %d", route[i]+1);
        }
        printf("\n");

    }
    return 0;
}


