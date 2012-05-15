#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <limits>

using namespace std;

template<class T>
struct Heap {

    typedef pair<T,int> value_type;
    vector<value_type> heap;
    vector<int> trace;
    int n;

    explicit Heap(int m) : heap(1), trace(m, -1), n(0) {
        heap.reserve(m);
    }

    const value_type& top() const {
        return heap[1];
    }

    void pop() {
        flip(1, n--);
        fixheap(1);
    }

    void push(const T& value, int key) {
        if (trace[key] >= 0) {
            int pos = trace[key];
            heap[pos].first = value;
            fixheap(pos);
        }
        else {
            heap.push_back(make_pair(value, key));
            trace[key] = ++n;
            fixheap(n);
        }
    }

    void remove(int key) {
        if (trace[key] >= 0) {
            int pos = trace[key];
            value_type last = heap[n];
            flip(pos, n);
            swap(heap[pos].first, heap[n].first);
            heap.pop_back();
            trace[key] = -1;
            if (pos != n--)
                push(last.first, last.second);
        }
    }


    void fixheap(int pos) {
        for(int up, cur = pos; cur > 1 && heap[cur] < heap[up = (cur>>1)]; cur = up)
            flip(cur, up);
        for(int down, cur = pos; (down = smaller(cur)) <= n && heap[down] < heap[cur]; cur = down)
            flip(cur, down);
    }

    int smaller(int pos) {
        int down = pos << 1;
        if (down+1 <= n && heap[down+1] < heap[down])
            down++;
        return down;
    }

    void flip(int a, int b) {
        swap(trace[heap[a].second], trace[heap[b].second]);
        swap(heap[a], heap[b]);
    }

};



int main() {

    int n, k;
    scanf("%d%d", &n, &k);

    Heap<int> heap_min(n), heap_max(n);
    vector<int> mins, maxs;

    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        heap_max.push(-a, i);
        heap_min.push(a, i);
        if (i-k >= 0) {
            heap_max.remove(i-k);
            heap_min.remove(i-k);
        }
        if (i+1 >= k) {
            maxs.push_back(-heap_max.top().first);
            mins.push_back(heap_min.top().first);
        }
    }

    printf("%d", mins[0]);
    for(int i = 1; i <= n-k; i++) {
        printf(" %d", mins[i]);
    }
    printf("\n");
    printf("%d", maxs[0]);
    for(int i = 1; i <= n-k; i++) {
        printf(" %d", maxs[i]);
    }
    printf("\n");

    return 0;
}




