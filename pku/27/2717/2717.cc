#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 200+1;
const int T = 2000+1;

inline int make_state(int side, int remain, int time) {
    return (side*N+remain)*T+time;
}

void solve(int n, int m, int t) {
    const int SIZE = N*2*T;
    int* trace = new int[SIZE];
    fill(trace, trace+SIZE, -1);
    int* flips = new int[SIZE];
    fill(flips, flips+SIZE, -1);

    priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
    q.push(make_pair(0, 0));
    trace[0] = -2;
    flips[0] = -2;

    int endpoint = -1;

    while(!q.empty()) {
        int hops = q.top().first;
        int state = q.top().second;
        q.pop();

        int side = state/N/T; // expiring side
        int remain = state/T%N;
        int time = state%T;

        printf("side=%d remain=%d time=%d\n", side, remain, time);

        if (time == t) {
            endpoint = state;
            break;
        }

        {
            // flip both hourglass
            int a, b;
            if (side == 0) {
                a = n; b = m - remain;
            }
            else {
                a = n - remain; b = m;
            }
            int next = make_state((a < b ? 0 : 1), max(a,b)-min(a,b), time+min(a,b));
            if (trace[next] < 0) {
                trace[next] = state;
                flips[next] = 1+2;
                q.push(make_pair(hops+1, next));
            }
        }
        if (time > 0) {
            // flip expiring hourglass
            int expire = (side == 0 ? n : m);
            if (expire >= remain) {
                int next = make_state(side^1, expire-remain, time+remain);
                if (trace[next] < 0) {
                    trace[next] = state;
                    flips[next] = side + 1;
                    q.push(make_pair(hops+1, next));
                }
            }
            else {
                int next = make_state(side, remain-expire, time+expire);
                if (trace[next] < 0) {
                    trace[next] = state;
                    flips[next] = side + 1;
                    q.push(make_pair(hops+1, next));
                }
            }
        }
        if (time > 0) {
            // flip not-expiring hourglass
            int next = make_state(side^1, 0, time+(side == 0 ? m : n) - remain);
            if (trace[next] < 0) {
                trace[next] = state;
                flips[next] = side^1 + 1;
                q.push(make_pair(hops+1, next));
            }
        }
        if (remain > 0) {
            // don't flip any hourglass
            int next = make_state(side^1, 0, time+remain);
            if (trace[next] < 0) {
                trace[next] = state;
                flips[next] = 0;
                q.push(make_pair(hops, next));
            }
        }
    }

    if (endpoint < 0) {
        printf("Impossible\n");
    }
    else {
        vector< pair<int, int> > v; //<time, flip>
        for(int i = endpoint; trace[i] >= 0; i = trace[i]) {
            int time = trace[i]%T;
            int flip = flips[i];
            v.push_back(make_pair(time, flip));
        }
        reverse(v.begin(), v.end());
        for(int i = 0; i < (int)v.size(); i++) {
            if (v[i].second != 0) {
                printf("%d: ", v[i].first);
                if (v[i].second == 3)
                    printf("%d,%d\n", n, m);
                else
                    printf("%d\n", (v[i].second == 1 ? n : m));
            }
        }
    }

    delete[] trace;
    delete[] flips;
}




struct State {
    int side, remain, time;
};

bool operator>(const State& a, const State& b) {
    return false;
}

int encode_state(const State& state) {
    return (state.side*N+state.remain)*T+state.time;
}
State decode_state(int id) {
    State state;
    state.side = id/N/T;
    state.remain = id/T%N;
    state.time = id%T;
    return state;
}

void state_dijkstra(int n, int m, int t) {

    const int STATE_SIZE = 2*N*T;

    vector< pair<int,int> > trace(STATE_SIZE, make_pair(-1, -1)); // <id, change>

    typedef pair<int, pair< pair<int,int> , int> > QNode;
    priority_queue<QNode, vector<QNode>, greater<QNode> > q;

    int init_state = 0;

    q.push(make_pair(0, make_pair(make_pair(init_state, -1), -1)));

    int end_state = -1;

    while(!q.empty()) {
        int hops = q.top().first;
        int id = q.top().second.first.first;
        int prev_id = q.top().second.first.second;
        int change = q.top().second.second;
        q.pop();

        State state = decode_state(id);

        if (trace[id].first >= 0)
            continue;
        trace[id].first = prev_id;
        trace[id].second = change;

        if (state.time == t) {
            end_state = id;
            break;
        }

        if (state.time < t) {
            int a, b;
            a = (state.side == 0 ? 0 : state.remain);
            b = (state.side == 1 ? 0 : state.remain);

            //print("hops=%d time=%d (%d, %d)", hops, state.time, a, b);

            { // flip both
                int aa, bb;
                aa = n - a; bb = m - b;
                State next_state;
                assert(!(aa == 0 && bb == 0));
                if (aa == 0 || bb == 0) {
                    next_state.side = (aa > 0 ? 0 : 1);
                    next_state.remain = 0;
                    next_state.time = state.time + max(aa, bb);
                }
                else {
                    next_state.side = (aa < bb ? 0 : 1);
                    next_state.remain = max(aa, bb) - min(aa, bb);
                    next_state.time = state.time + min(aa, bb);
                }
                int next_id = encode_state(next_state);
                if (trace[next_id].first < 0) {
                    q.push(make_pair(hops+1, make_pair(make_pair(next_id, id), 3)));
                    //print(" 3");
                }
            }
            if (state.time > 0) { // flip n
                int aa, bb;
                aa = n - a; bb = b;
                
                State next_state;
                assert(!(aa == 0 && bb == 0));
                if (aa == 0 || bb == 0) {
                    next_state.side = (aa > 0 ? 0 : 1);
                    next_state.remain = 0;
                    next_state.time = state.time + max(aa, bb);
                }
                else {
                    next_state.side = (aa < bb ? 0 : 1);
                    next_state.remain = max(aa, bb) - min(aa, bb);
                    next_state.time = state.time + min(aa, bb);
                }
                int next_id = encode_state(next_state);
                if (trace[next_id].first < 0) {
                    q.push(make_pair(hops+1, make_pair(make_pair(next_id, id), 1)));
                    //print(" 1");
                }
            }
            if (state.time > 0) { // flip m
                int aa, bb;
                aa = a; bb = m - b;
                
                State next_state;
                assert(!(aa == 0 && bb == 0));
                if (aa == 0 || bb == 0) {
                    next_state.side = (aa > 0 ? 0 : 1);
                    next_state.remain = 0;
                    next_state.time = state.time + max(aa, bb);
                }
                else {
                    next_state.side = (aa < bb ? 0 : 1);
                    next_state.remain = max(aa, bb) - min(aa, bb);
                    next_state.time = state.time + min(aa, bb);
                }
                int next_id = encode_state(next_state);
                if (trace[next_id].first < 0) {
                    q.push(make_pair(hops+1, make_pair(make_pair(next_id, id), 2)));
                    //print(" 2");
                }
            }
            if (state.remain > 0) { // flip none
                int aa, bb;
                aa = a;
                bb = b;
                
                State next_state;
                assert(!(aa == 0 && bb == 0));
                if (aa == 0 || bb == 0) {
                    next_state.side = (aa > 0 ? 0 : 1);
                    next_state.remain = 0;
                    next_state.time = state.time + max(aa, bb);
                }
                else {
                    next_state.side = (aa < bb ? 0 : 1);
                    next_state.remain = max(aa, bb) - min(aa, bb);
                    next_state.time = state.time + min(aa, bb);
                }
                int next_id = encode_state(next_state);
                if (trace[next_id].first < 0) {
                    q.push(make_pair(hops, make_pair(make_pair(next_id, id), 0)));
                    //print(" 0");
                }
            }
            //print("\n");
        }
    }

    if (end_state == -1) {
        printf("Impossible\n");
    }
    else {
        vector< pair<int, int> > route;
        for(int id = end_state; trace[id].first >= 0; id = trace[id].first) {
            State prev_state = decode_state(trace[id].first);
            int change = trace[id].second;
            route.push_back(make_pair(prev_state.time, change));
        }
        reverse(route.begin(), route.end());

        for(int i = 0; i < (int)route.size(); i++) {
            if (route[i].second > 0) {
                printf("%d: ", route[i].first);
                if (route[i].second == 3) {
                    printf("%d,%d\n", n, m);
                }
                else {
                    printf("%d\n", (route[i].second == 1 ? n : m));
                }
            }
        }
    }
}

















/*
struct State {
};

bool operator>(const State& a, const State& b) {
    return false;
}

int encode_state(const State& state) {
}
State decode_state(int id) {
}

vector<?> state_dijkstra() {

    const int STATE_SIZE = 12345;

    vector< pair<int,int> > trace(STATE_SIZE, make_pair(-1, -1)); // <id, change>

    typedef pair<int, State> QNode;
    priority_queue<QNode, vector<QNode>, greater<QNode> > q;

    int init_state = 12345;

    q.push(make_pair(0, init_state));

    int end_state = -1;

    while(!q.empty()) {
        int hops = q.top().first;
        int id = q.top().second;
        q.pop();

        State state = decode_state(id);

        if (finish_state(state)) {
            end_state = id;
            break;
        }

        if (can_shift(change)) {
            State next_state = next_state(state, change);
            int next_id = encode_state(next_state);
            if (trace[next_id].first < 0) {
                trace[next_id] = make_pair(id, change);
                q.push(make_pair(hops+1, next_id));
            }
        }
    }

    if (end_state == -1)
        throw no_route();

    vector<?> route;
    for(int id = end_state; id >= 0; id = trace[id].first) {
        State state = decode_state(id);
        int change = trace[id].second;
        route.push_back(make_route_node(state, change));
    }
    reverse(route.begin(), route.end());

    return route;
}
*/










int main() {
    while(true) {
        int n, m, t;
        scanf("%d%d%d", &n, &m, &t);
        if (n == 0 && m == 0 && t == 0)
            break;

        state_dijkstra(n, m, t);

        printf("----------\n");
    }
    return 0;
}
