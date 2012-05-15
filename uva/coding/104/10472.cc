#include <iostream>
#include <cstdio>
#include <queue>

#define N 100
#define INF 10000

const double SPEED[] = {10.0/60.0, 30.0/60.0, 50.0/60.0, 40.0/60.0};
const double AVAIL[] = {2.0, 3.0, 10.0, 30.0};

template<class T>
struct Matrix {
    const int n, m;
    T* data;
    Matrix(int n, int m) : n(n), m(m), data(new T[n*m]) {
        clear();
    }
    ~Matrix() {
        delete[] data;
    }
    void clear(const T& def = T()) {
        std::fill(data, data+n*m, def);
    }
    inline T* operator[](int i) {
        return data+i*m;
    }
    inline const T* operator[](int i) const {
        return data+i*m;
    }
    inline int size() const {
        return n;
    }
};

template<class T>
struct Vector {
    const int n;
    T* data;
    Vector(int n) : n(n), data(new T[n]) {
        clear();
    }
    ~Vector() {
        delete[] data;
    }
    void clear(const T& def = T()) {
        std::fill(data, data+n, def);
    }
    inline T& operator[](int i) {
        return data[i];
    }
    inline const T& operator[](int i) const {
        return data[i];
    }
    inline int size() const {
        return n;
    }
};

struct Link {
    int ncost;
    int mcost;
    Link() {
        ncost = mcost = INF;
    }
};

struct Node {
    int iNode;
    int iState;
    int fare;
    double time;
    Node(int iNode=-1, int iState=-1, int fare=0, double time=0)
        : iNode(iNode), iState(iState), fare(fare), time(time) {
    }
};

struct TimeFirstComparator {
    inline bool operator()(const Node& a, const Node& b) {
        return (a.time > b.time);
    }
};
struct FareFirstComparator {
    inline bool operator()(const Node& a, const Node& b) {
        return (a.fare > b.fare);
    }
};


Node timeFirstSearch(const Matrix<Link>& adj, const int iSource, const int iDest) {
    const int n = adj.size();

    std::priority_queue<Node, std::vector<Node>, TimeFirstComparator> q;
    Matrix<Node> nodes(n, 4);
    q.push( Node(iSource, -1, 0, 0) );

    Node result;

    while(! q.empty()) {
        Node node = q.top();
        q.pop();

        int iNode = node.iNode;
        int iState = node.iState;

        if (node.iState < 0 || nodes[iNode][iState].iNode == -1) {
            std::printf("Node(%d,%d,%d,%lf)\n", node.iNode, node.iState, node.fare, node.time);
            if (iState >= 0)
                nodes[iNode][iState] = node;
            for(int jNode=0; jNode<n; jNode++) {
                for(int iMean=0; iMean<4; iMean++) {
                    int iDist = (iMean == 0 ? adj[iNode][jNode].ncost : adj[iNode][jNode].mcost);
                    if (iDist < INF) {
                        q.push( Node(jNode,
                                     iMean,
                                     node.fare,
                                     node.time + (double)iDist/SPEED[iMean]
                                     + (iMean != iState ? AVAIL[iMean] : 0) ) );
                    }
                }
            }
            if (iNode == iDest) {
                result = node;
                break;
            }
        }
    }
    return result;
}


int main() {
    int iCase = 0;
    int nNodes, nLinks;
    while(std::cin >> nNodes >> nLinks) {
        Matrix<Link> adj(nNodes, nNodes);
        int iSource, iDest;
        std::cin >> iSource >> iDest;
        for(int i=0; i<nLinks; i++) {
            int iNode, jNode, iDist;
            char cType;
            std::cin >> iNode >> jNode >> iDist >> cType;
            if (cType == 'N' || cType == 'A') {
                adj[iNode][jNode].ncost <?= iDist;
                adj[jNode][iNode].ncost <?= iDist;
            }
            if (cType == 'M' || cType == 'A') {
                adj[iNode][jNode].mcost <?= iDist;
                adj[jNode][iNode].mcost <?= iDist;
            }
        }
        Node timeFirst = timeFirstSearch(adj, iSource, iDest);
        //Node fareFirst = fareFirstSearch(adj, iSource, iDest);
        std::printf("Case#%d\n", ++iCase);
        std::printf("%d %.2lf\n", timeFirst.fare, timeFirst.time);
    }
    return 0;
}
