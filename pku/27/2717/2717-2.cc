#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

struct Node {
    int a, b, t;
    Node() {
    }
    Node(int a, int b, int t) : a(a), b(b), t(t) {
    }
};

bool operator<(const Node& a, const Node& b) {
    return make_pair(a.a, make_pair(a.b, a.t)) < make_pair(b.a, make_pair(b.b, b.t));
}

void dijkstra(int n, int m, int t) {
    map<Node, pair<Node, int> > trace;

    typedef pair<int, pair<Node, pair<Node, int> > > QNode;
    priority_queue<QNode, vector<QNode>, greater<QNode> > q;

    q.push(make_pair(0, make_pair(Node(0, 0, 0), make_pair(Node(-1, -1, -1), -1))));

    try {
        while(!q.empty()) {
            int hops = q.top().first;
            QNode::second_type record = q.top().second;
            Node node = record.first;
            q.pop();

            if (node.t > t)
                continue;

            if (trace.find(node) != trace.end())
                continue;

            trace.insert(record);

            //printf("hops=%d time=%d (%d,%d)\n", hops, node.t, node.a, node.b);

            if (node.t == t)
                throw node;

            {
                Node next;
                next.a = n - node.a;
                next.b = m - node.b;

                if (next.a == 0 || next.b == 0) {
                    int e = max(next.a, next.b);
                    next.t = node.t + e;
                    next.a = next.b = 0;
                }
                else {
                    int e = min(next.a, next.b);
                    next.t = node.t + e;
                    next.a -= e; next.b -= e;
                }
                q.push(make_pair(hops+1, make_pair(next, make_pair(node, 3))));
            }
            if (node.t > 0) {
                Node next;
                next.a = n - node.a;
                next.b = node.b;

                if (next.a == 0 || next.b == 0) {
                    int e = max(next.a, next.b);
                    next.t = node.t + e;
                    next.a = next.b = 0;
                }
                else {
                    int e = min(next.a, next.b);
                    next.t = node.t + e;
                    next.a -= e; next.b -= e;
                }
                q.push(make_pair(hops+1, make_pair(next, make_pair(node, 1))));
            }
            if (node.t > 0) {
                Node next;
                next.a = node.a;
                next.b = m - node.b;

                if (next.a == 0 || next.b == 0) {
                    int e = max(next.a, next.b);
                    next.t = node.t + e;
                    next.a = next.b = 0;
                }
                else {
                    int e = min(next.a, next.b);
                    next.t = node.t + e;
                    next.a -= e; next.b -= e;
                }
                q.push(make_pair(hops+1, make_pair(next, make_pair(node, 2))));
            }
            if (node.a + node.b > 0) {
                Node next;
                next.a = node.a;
                next.b = node.b;

                if (next.a == 0 || next.b == 0) {
                    int e = max(next.a, next.b);
                    next.t = node.t + e;
                    next.a = next.b = 0;
                }
                else {
                    int e = min(next.a, next.b);
                    next.t = node.t + e;
                    next.a -= e; next.b -= e;
                }
                q.push(make_pair(hops, make_pair(next, make_pair(node, 0))));
            }
        }
        printf("Impossible\n");
    }
    catch(Node lastNode) {
        vector< pair<int, int> > route;
        for(Node node = lastNode; trace[node].second != -1; node = trace[node].first) {
            route.push_back(make_pair(trace[node].first.t, trace[node].second));
        }
        reverse(route.begin(), route.end());
        for(int i = 0; i < (int)route.size(); i++) {
            if (route[i].second != 0) {
                printf("%d: ", route[i].first);
                if (route[i].second == 3)
                    printf("%d,%d\n", n, m);
                else
                    printf("%d\n", (route[i].second == 1 ? n : m));
            }
        }
    }
}


int main() {
    while(true) {
        int n, m, t;
        scanf("%d%d%d", &n, &m, &t);
        if (n == 0 && m == 0 && t == 0)
            break;

        dijkstra(n, m, t);

        printf("----------\n");
    }
    return 0;
}








