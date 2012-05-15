#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <utility>

using namespace std;

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

struct Node {
    int pos[16];
    int dist;
    int distance() {
        int d = 0;
        for(int i = 0; i < 16; i++)
            d += abs(pos[i]%4 - i%4) + abs(pos[i]/4 - i/4);
        return d;
    }
    bool move(int dir) {
        const int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, };
        int dx = DIRS[dir][0];
        int dy = DIRS[dir][1];
        int x = pos[15]%4;
        int y = pos[15]/4;
        if (0 <= x+dx && x+dx < 4 && 0 <= y+dy && y+dy < 4) {
            int z = find(pos, pos+16, (y+dy)*4+x+dx) - pos;
            swap(pos[15], pos[z]);
            return true;
        }
        return false;
    }
    void print() {
        cout << "{ ";
        for(int i = 0; i < 16; i++)
            cout << pos[i] << ' ';
        cout << "}" << endl;
    }
    bool solvable() {
        int faces[16];
        int ref[16];
        for(int i = 0; i < 16; i++) {
            faces[pos[i]] = i;
            ref[i] = i;
        }
        reverse(faces+4, faces+8);
        reverse(faces+12, faces+16);
        reverse(ref+4, ref+8);
        reverse(ref+12, ref+15);
        remove(faces, faces+16, 15);
        int s = 0;
        for(int i = 0; i < 15; i++) {
            if (faces[i] != ref[i]) {
                int z = find(faces, faces+15, ref[i]) - faces;
                swap(faces[i], faces[z]);
                s++;
            }
        }
        return (s%2 == 0);
    }
};

bool operator<(const Node& a, const Node& b) {
    return lexicographical_compare(a.pos, a.pos+16, b.pos, b.pos+16);
}
bool operator>(const Node& a, const Node& b) {
    return (b < a);
}


vector<int> search(Node start) {

    if (!start.solvable())
        return vector<int>(1, -1);
    if (start.distance() == 0)
        return vector<int>();

    typedef pair<int, Node> K;
    priority_queue<K, vector<K>, greater<K> > q;
    q.push(make_pair(0, start));

    map<Node, pair<int, int> > trace;
    trace[start] = make_pair(0, -1);

    while(! q.empty()) {
        Node cur = q.top().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++) {
            Node next = cur;
            if (next.move(dir)) {
                next.dist++;
                if (trace.count(next) == 0) {
                    trace[next] = make_pair(next.dist, dir);
                    if (next.distance() == 0)
                        goto END;
                    int cost = next.dist+next.distance()/2;
                    if (cost <= 50)
                        q.push(make_pair(cost, next));
                }
            }
        }
    }

END:
    Node goal;
    for(int i = 0; i < 16; i++)
        goal.pos[i] = i;
    if (trace.count(goal) == 0)
        return vector<int>(1, -1);

    vector<int> route;
    for(Node cur(goal); trace[cur].second >= 0; cur.move(trace[cur].second^1))
        route.push_back(trace[cur].second);
    reverse(route.begin(), route.end());
    return route;
}



void solve() {
    Node start;
    for(int i = 0; i < 16; i++) {
        int k;
        cin >> k;
        if (k == 0)
            k = 15;
        else
            k--;
        start.pos[k] = i;
    }
    start.dist = 0;
    vector<int> route = search(start);
    if (route.size() == 1 && route[0] < 0) {
        cout << "This puzzle is not solvable." << endl;
    }
    else {
        const char* STR = "DURL";
        for(int i = 0; i < (int)route.size(); i++) {
            cout << STR[route[i]];
        }
        cout << endl;
    }
}


int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}
