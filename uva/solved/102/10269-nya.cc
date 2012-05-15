/*
 * UVA 10269 Adventure of Super Mario
 * 2005-06-29
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <iterator>

const int MAX_NODES = 100;
const int MAX_SKIPS = 10;
const int INF = 100000;

int nNodes;
int nCastles;

int dist[MAX_NODES][MAX_NODES];

int dij[MAX_NODES][MAX_SKIPS+1];
//bool dijb[MAX_NODES][MAX_SKIPS+1];

struct Node {
    int iNode;
    int nSkips;
    int len;
    Node() {}
    Node(int iNode, int nSkips, int len)
        : iNode(iNode), nSkips(nSkips), len(len) {}
    friend bool operator<(const Node& a, const Node& b) {
        return (a.len > b.len);
    }
};

template<class T>
class FixedHeap {
private:
    std::vector< std::pair<int, T> > heap;
    std::vector<int> tracker;
    const int N;
    int n;

public:
    FixedHeap(int N) : N(N) {
        heap.resize(N+1);
        tracker.resize(N, -1);
        n = 0;
    }

    void update(int id, const T& value) {
        if (tracker[id] < 0) {
            n++;
            heap[n].first = id;
            heap[n].second = value;
            tracker[id] = n;
            upheap(n);
        }
        else {
            int pos = tracker[id];
            bool up = (value < heap[pos].second);
            heap[pos].second = value;
            if (up)
                upheap(pos);
            else
                downheap(pos);
        }
    }

    bool empty() const {
        return (n == 0);
    }

    bool contains(int id) const {
        return (tracker[id] >= 0);
    }

    const std::pair<int, T>& top() const {
        return heap[1];
    }

    const T& get(int id) const {
        return heap[tracker[id]].second;
    }

    void pop() {
        tracker[heap[1].first] = -1;
        tracker[heap[n].first] = 1;
        heap[1] = heap[n--];
        downheap(1);
    }

private:
    void upheap(int pos) {
        while(pos > 1 && heap[pos].second < heap[pos>>1].second) {
            swapheap(pos, pos>>1);
            pos >>= 1;
        }
    }
    void downheap(int pos) {
        int next;
        while( (next = pos<<1) <= n ) {
            if (next+1 <= n && heap[next+1].second < heap[next].second)
                next++;
            if (! (heap[next].second < heap[pos].second))
                break;
            swapheap(pos, next);
            pos = next;
        }
    }
    void swapheap(int a, int b) {
        std::swap(heap[a], heap[b]);
        tracker[heap[a].first] = a;
        tracker[heap[b].first] = b;
    }
};


void floyd() {
    for(int mid = 0; mid < nNodes-nCastles; mid++) {
        for(int first = 0; first < nNodes; first++) {
            if (dist[first][mid] != INF) {
                for(int last = first+1; last < nNodes; last++) {
                    dist[first][last] = dist[last][first] = 
                        std::min( dist[first][last], dist[first][mid] + dist[mid][last] );
                }
            }
        }
    }
}

#if 0
int dijkstra_prim(int first, int last, int nSkips, int nSkipLen) {
    for(int i=0; i<nNodes; i++) {
        for(int j=0; j<=nSkips; j++) {
            dij[i][j] = INF;
            dijb[i][j] = false;
        }
    }

    dij[first][nSkips] = 0;

    while(true) {
        Node node;
        node.len = INF;
        for(int i=0; i<nNodes; i++) {
            for(int j=0; j<=nSkips; j++) {
                if (!dijb[i][j] && dij[i][j] < node.len) {
                    node.iNode = i;
                    node.nSkips = j;
                    node.len = dij[i][j];
                }
            }
        }

        if (node.len == INF)
            break;

        dijb[node.iNode][node.nSkips] = true;

        // don't use magic boots
        for(int iNode=0; iNode<nNodes; iNode++) {
            dij[iNode][node.nSkips] = std::min( dij[iNode][node.nSkips], node.len + dist[node.iNode][iNode] );
        }

        // use magic boots
        if (node.nSkips > 0) {
            for(int iNode=0; iNode<nNodes; iNode++) {
                if (dist[node.iNode][iNode] <= nSkipLen)
                    dij[iNode][node.nSkips-1] = std::min( dij[iNode][node.nSkips-1], node.len);
            }
        }

        if (node.iNode == last)
            break;
    }

    return *std::min_element(dij[last], dij[last]+nSkips+1);
}


int dijkstra_pfs_stl(int first, int last, int nSkips, int nSkipLen) {
    for(int i=0; i<nNodes; i++) {
        for(int j=0; j<=nSkips; j++) {
            dij[i][j] = INF;
        }
    }

    std::priority_queue<Node> q;

    q.push(Node(first, nSkips, 0));

    while(! q.empty()) {
        Node node = q.top();
        q.pop();
        if (dij[node.iNode][node.nSkips] != INF)
            continue;

        dij[node.iNode][node.nSkips] = node.len;

        // don't use magic boots
        for(int iNode=0; iNode<nNodes; iNode++) {
            if (dist[node.iNode][iNode] != INF && dij[iNode][node.nSkips] == INF) {
                q.push(Node(iNode, node.nSkips, node.len+dist[node.iNode][iNode]));
            }
        }

        // use magic boots
        if (node.nSkips > 0) {
            for(int iNode=0; iNode<nNodes; iNode++) {
                if (dist[node.iNode][iNode] <= nSkipLen && dij[iNode][node.nSkips-1] == INF) {
                    q.push(Node(iNode, node.nSkips-1, node.len));
                }
            }
        }

        if (node.iNode == last)
            break;
    }

/*
    for(int i=0; i<nNodes; i++) {
        std::copy(dij[i], dij[i]+nSkips+1, std::ostream_iterator<int>(std::cerr, " "));
        std::cerr << std::endl;
    }
*/

    return *std::min_element(dij[last], dij[last]+nSkips+1);
}

#endif

int dijkstra(int first, int last, int nSkips, int nSkipLen) {
    for(int i=0; i<nNodes; i++) {
        for(int j=0; j<=nSkips; j++) {
            dij[i][j] = INF;
        }
    }

    int nPat = nNodes * (nSkips+1);

    FixedHeap<int> q(nPat);

    q.update(nPat-1, 0);

    while(! q.empty()) {
        int id = q.top().first;
        Node node(id%nNodes, id/nNodes, q.top().second);

        dij[node.iNode][node.nSkips] = node.len;
        q.pop();

        // don't use magic boots
        for(int iNode=0; iNode<nNodes; iNode++) {
            if (dij[iNode][node.nSkips] != INF)
                continue;
            int nid = node.nSkips*nNodes+iNode;
            int nd = ( q.contains(nid) ? q.get(nid) : INF);
            int nlen = node.len+dist[node.iNode][iNode];
            if (nlen < nd) {
                q.update(nid, nlen);
            }
        }

        // use magic boots
        if (node.nSkips > 0) {
            for(int iNode=0; iNode<nNodes; iNode++) {
                if (dij[iNode][node.nSkips-1] != INF)
                    continue;
                int nid = (node.nSkips-1)*nNodes+iNode;
                int nd = ( q.contains(nid) ? q.get(nid) : INF);
                if (dist[node.iNode][iNode] <= nSkipLen && node.len < nd) {
                    q.update(nid, node.len);
                }
            }
        }

        if (node.iNode == last)
            break;
    }

/*
    for(int i=0; i<nNodes; i++) {
        std::copy(dij[i], dij[i]+nSkips+1, std::ostream_iterator<int>(std::cerr, " "));
        std::cerr << std::endl;
    }
*/

    return *std::min_element(dij[last], dij[last]+nSkips+1);
}



int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        std::cin >> nNodes >> nCastles;
        nNodes += nCastles;

        int nRoads, nSkipLen, nSkips;
        std::cin >> nRoads >> nSkipLen >> nSkips;

        for(int i=0; i<nNodes; i++) {
            for(int j=0; j<nNodes; j++) {
                dist[i][j] = INF;
            }
        }

        for(int i=0; i<nRoads; i++) {
            int first, last, d;
            std::cin >> first >> last >> d;
            first--; last--;
            dist[first][last] = dist[last][first] = d;
        }

        floyd();

        std::cout << dijkstra(nNodes-1, 0, nSkips, nSkipLen) << std::endl;

    }

    return 0;
}

