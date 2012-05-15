#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <limits>

using namespace std;

template<class T, class K>
struct Heap {

    typedef pair<T,K> value_type;
    vector<value_type> heap;
    map<K,int> trace;
    int n;

    Heap() : heap(1), n(0) {}

    const value_type& top() const {
        return heap[1];
    }

    void pop() {
        flip(1, n--);
        heap.pop_back();
        fixheap(1);
    }

    void push(const T& value, const K& key) {
        if (trace.count(key) == 0) {
            heap.push_back(make_pair(value, key));
            trace[key] = ++n;
        }
        heap[trace[key]].first = value;
        fixheap(trace[key]);
    }

    void remove(const K& key) {
        if (trace.count(key) > 0) {
            int pos = trace[key];
            flip(pos, n--);
            heap.pop_back();
            trace.erase(key);
            if (pos <= n)
                fixheap(pos);
        }
    }

    void fixheap(int pos) {
        for(int up, cur = pos; cur > 1 && heap[cur] < heap[up = (cur>>1)]; cur = up)
            flip(cur, up);
        for(int down, cur = pos; (down = descend(cur)) <= n && heap[down] < heap[cur]; cur = down)
            flip(cur, down);
    }

    int descend(int pos) {
        int down = pos << 1;
        return down + (down+1 <= n && heap[down+1] < heap[down] ? 1 : 0);
    }

    void flip(int a, int b) {
        swap(trace[heap[a].second], trace[heap[b].second]);
        swap(heap[a], heap[b]);
    }

};


void solve() {

    vector<pair<int,int> > events;

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        b++;
        events.push_back(make_pair(a, i));
        events.push_back(make_pair(b, i));
    }

    vector<bool> v(n, false);
    events.push_back(make_pair(numeric_limits<int>::max(), -1));

    sort(events.begin(), events.end());

    Heap<int,int> heap;

    vector<bool> seen(n, false);

    for(int i = 0; i < (int)events.size(); i++) {

        if (i > 0 && events[i].first > events[i-1].first) {
            if (heap.n > 0) {
                //printf("marked %d\n", heap.top().second);
                seen[heap.top().second] = true;
            }
        }

        int id = events[i].second;
        if (id < 0)
            continue;

        if (!v[id]) {
            v[id] = true;
            heap.push(-id, id);
            //printf("push %d\n", id);
        }
        else {
            heap.remove(id);
            //printf("pop %d\n", id);
            v[id] = false;
        }

    }

    printf("%d\n", count(seen.begin(), seen.end(), true));
}

int main() {

    int nCases;
    scanf("%d", &nCases);

    while(nCases-- > 0)
        solve();

    return 0;
}




