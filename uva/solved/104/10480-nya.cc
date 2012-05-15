/*
 * UVA 10480 Sabotage
 * 2005-09-28
 * by nya
 */

// そのまんまライブラリ化

/*
 * Ford-Fulkerson法によるネットワーク流最大化
 *
 * 2005-09-28 First Version by nya
 *
 */

#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cassert>


#define BIDIRECTIONAL_NETWORK   // 無向グラフの場合


template<class T>
struct Matrix {
    const int n;
    T* data;
    Matrix(int n) : n(n) {
        data = new T[n*n];
    }
    ~Matrix() {
        delete[] data;
    }
    inline T* operator[](int i) {
        return data+i*n;
    }
    inline const T* operator[](int i) const {
        return data+i*n;
    }
    inline int size() const {
        return n;
    }
};

class Network {

private:

    typedef int integer;
    static const integer INF = 0x7fffffff;

    struct Edge {
        integer size, flow;
        Edge() : size(0), flow(0) {}
    };
    struct FF {
        int id, prev, dist;
        integer inc;
        FF(int id=-1, int prev=-1, integer inc=0, int dist=INF)
            : id(id), prev(prev), dist(dist), inc(inc) {
        }
        friend bool operator<(const FF& a, const FF& b) {
            if (a.dist != b.dist)
                return (a.dist > b.dist);
            return (a.inc < b.inc);
        }
    };

    const int n;
    std::vector<FF> ff;
    const int iSource, iSink;

public:
    Matrix<Edge> net;
    typedef std::vector< std::pair<int,int> > Cut;

    Network(int n, int iSource, int iSink)
        : n(n), ff(n), iSource(iSource), iSink(iSink), net(n) {
    }

    void setEdge(int i, int j, integer size) {
        net[i][j].size = size;
        net[j][i].size = -size;
    }

    void maximizeFlow() {
        doFF();
    }

    Cut getMinimumCut() {
        Cut cut;
        clearFF();
        fillSinker(iSink);
        searchCut(iSource, cut);
        return cut;
    }

    integer getMaximumFlow() {
        integer iFlow = 0;
        for(int i=0; i<n; i++) {
            iFlow += net[iSource][i].flow;
        }
        return iFlow;
    }


private:

    void clearFF() {
        ff.clear();
        ff.resize(n);
    }

    void doFF() {
        while(true) {
            clearFF();
            if (!doFFSearch())
                break;
            integer inc = ff[iSink].inc;
            for(int j = iSink; ff[j].prev >= 0; j = ff[j].prev) {
                int i = ff[j].prev;
                net[i][j].flow += inc;
                net[j][i].flow = -net[i][j].flow;
                assert(abs(net[i][j].flow) <= abs(net[i][j].size));
#ifndef BIDIRECTIONAL_NETWORK
                assert(sgn(net[i][j].flow)*sgn(net[i][j].size) >= 0);
#endif
            }
        }
    }

    bool doFFSearch() {
        std::priority_queue<FF> q;
        q.push( FF(iSource, -1, INF, 0) );
        while(! q.empty()) {
            FF f = q.top();
            q.pop();
            int id = f.id;
            if (ff[id].dist == INF) {
                ff[id] = f;
                if (id == iSink)
                    break;
                for(int i=0; i<n; i++) {
                    if (net[id][i].size != 0 && ff[i].dist == INF) {
                        integer inc = std::min(f.inc,
#ifndef BIDIRECTIONAL_NETWORK
                                               (net[id][i].size > 0 ? net[id][i].size : 0) - net[id][i].flow 
#else
                                               abs(net[id][i].size) - net[id][i].flow
#endif
                            );
                                                                       
                        if (inc > 0) {
                            q.push( FF(i,
                                       id,
                                       inc,
                                       f.dist+1) );
                        }
                    }
                }
            }
        }
        
        return (ff[iSink].dist != INF);
    }

    void fillSinker(int i) {
        if (ff[i].dist == INF) {
            ff[i] = FF(i, iSink, 0, 0);
            for(int j=0; j<n; j++) {
                if (abs(net[i][j].flow) < abs(net[i][j].size))
                    fillSinker(j);
            }
        }
    }
    void searchCut(int i, Cut& cut) {
        if (ff[i].dist == INF) {
            ff[i] = FF(i, 0, 0, 0);
            for(int j=0; j<n; j++) {
                if (net[i][j].size != 0) {
                    if (ff[j].prev == iSink)
                        cut.push_back( std::make_pair(i, j) );
                    else
                        searchCut(j, cut);
                }
            }
        }
    }

    inline integer abs(integer n) {
        return (n < 0 ? -n : n);
    }
    inline int sgn(integer n) {
        return (n == 0 ? 0 : n > 0 ? 1 : -1);
    }
};



/*
 * テストドライバ
 *
 * source=0, sink=1の時のminimum cutを求める 
 * (無向グラフの場合は UVA 10480 Sabotage)
 *
 */

int main() {

    int nNodes, nLinks;
    while(std::cin >> nNodes >> nLinks && !(nNodes == 0 && nLinks == 0)) {

        Network net(nNodes, 0, 1);

        for(int iLink=0; iLink<nLinks; iLink++) {
            int i, j, s;
            std::cin >> i >> j >> s;
            i--; j--;
            net.setEdge(i, j, s);
        }

        net.maximizeFlow();
        Network::Cut cut = net.getMinimumCut();

        for(int i=0; i<(int)cut.size(); i++) {
            std::cout << (cut[i].first+1) << ' ' << (cut[i].second+1) << std::endl;
        }
        std::cout << std::endl;

    }

    return 0;
}
