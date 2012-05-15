#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;



typedef double Weight;

const Weight WEIGHT_INFTY = 1.0e100;//std::numeric_limits<Weight>::max();

// 許容誤差
#define EP 1.0e-8

// 誤差つき符号関数
inline int SGN(double a) { return abs(a) < EP ? 0 : a > 0 ? 1 : -1; }
#define EQ(a,b) (SGN((a)-(b)) == 0)    ///< equal
#define NE(a,b) (SGN((a)-(b)) != 0)    ///< not equal
#define LE(a,b) (SGN((a)-(b)) <= 0)    ///< less or equal
#define LT(a,b) (SGN((a)-(b)) < 0)     ///< less



// 点
typedef complex<double> P;

typedef vector<P> G;


/*
 * 線分、半直線、直線
 *  posとpos+dirを結ぶ線分、またはそれを延長した直線、半直線を表す。
 */
struct L {
    P pos, dir;

    L() {}
    L(const P& pos, const P& dir) : pos(pos), dir(dir) {}
};


// 内積を求める
inline double inp(const P& a, const P& b) {
    return (conj(a)*b).real();
}

// 外積を求める
inline double outp(const P& a, const P& b) {
    return (conj(a)*b).imag();
}


/* 射影ベクトルを求める
 *  p 射影元のベクトル
 *  b 射影先のベクトル
 */
inline P proj(const P& p, const P& b) {
    return b*inp(p,b)/norm(b);
}

// 点から直線に対して引いた垂線の足を求める
inline P perf(const L& l, const P& p) {
    L m(l.pos - p, l.dir);
    return (p + (m.pos - proj(m.pos, m.dir)));
}


/* 線分を直線に射影した線分を求める
 *  s 射影元の線分
 *  b 射影先の直線
 */
inline L proj(const L& s, const L& b) {
    return L(perf(b, s.pos), proj(s.dir, b.dir));
}



// 回転の方向を調べる(Sedgewickのおせっかい版)
inline int ccw(const P& p, const P& r, const P& s) {
    P a(r-p), b(s-p);
    int sgn = SGN(outp(a, b));
    if (sgn != 0)
        return sgn;
    if (LT(a.real()*b.real(), 0) || LT(a.imag()*b.imag(), 0))
        return -1;
    if (LT(norm(a), norm(b)))
        return 1;
    return 0;
}

// 回転の方向を調べる
inline int rot(const P& p, const P& r, const P& s) {
    return SGN(outp(r-p, s-p));
}


// 直線表現の正規化を行う
L normalize_line(const L& l) {
    return L(perf(l, P(0, 0)),
             ( (LT(l.dir.imag(), 0) ||
                (EQ(l.dir.imag(), 0) && LT(l.dir.real(), 0)) )
               ? -l.dir : l.dir ) / abs(l.dir) );
}



// 直線同士が交差するかどうか調べる
bool ll_intersects(const L& l, const L& m) {
    return NE(abs(normalize_line(l).dir - normalize_line(m).dir), 0);
}

// 直線と線分が交差するか調べる
bool ls_intersects(const L& l, const L& s) {
    return (ccw(l.pos, l.pos+l.dir, s.pos)
            *ccw(l.pos, l.pos+l.dir, s.pos+s.dir) <= 0);
}

// 線分同士が交差するか調べる
bool ss_intersects(const L& s, const L& t) {
    return (ls_intersects(s, t) &&
            ls_intersects(t, s));
}


// 直線同士が平行かどうか調べる
bool line_parallel(const L& l, const L& m) {
    return !ll_intersects(l, m);
}

// 直線同士が一致するか調べる
bool line_equals(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    return (EQ(abs(a.pos-b.pos), 0) && EQ(abs(a.dir-b.dir), 0));
}

// 直線同士の交点を求める
P line_cross(const L& l, const L& m) {
    double num = outp(m.dir, m.pos-l.pos);
    double denom = outp(m.dir, l.dir);
    if (EQ(denom, 0))
        throw 0; // 共有点が一つではない
    return P(l.pos + l.dir*num/denom);
}



// 点と点の距離
double pp_distance(const P& a, const P& b) {
    return abs(a - b);
}

// 直線と点の距離
double lp_distance(const L& l, const P& p) {
    return abs(perf(l, p) - p);
}

// 線分と点の距離
double sp_distance(const L& s, const P& p) {
    const P r = perf(s, p);
    const double pos = ((r-s.pos)/s.dir).real();
    if (LE(0, pos) && LE(pos, 1))
        return abs(r - p);
    return min(abs(s.pos - p),
               abs(s.pos+s.dir - p));
}

// 線分と線分の距離
double ss_distance(const L& s, const L& t) {
    if (ss_intersects(s, t))
        return 0;
    return min(sp_distance(s, t.pos),
           min(sp_distance(s, t.pos+t.dir),
           min(sp_distance(t, s.pos),
               sp_distance(t, s.pos+s.dir))));
}

// 直線と線分の距離
double ls_distance(const L& l, const L& s) {
    if (ls_intersects(l, s))
        return 0;
    return min(lp_distance(l, s.pos),
               lp_distance(l, s.pos+s.dir));
}

//直線と直線の距離
double ll_distance(const L& l, const L& m) {
    L a = normalize_line(l);
    L b = normalize_line(m);
    if (NE(abs(a.dir-b.dir), 0))
        return 0;
    return abs(a.pos/a.dir - b.pos/b.dir);
}

double nya_distance(const G& a, const G& b) {
    int n = a.size();
    int m = b.size();
    double d = WEIGHT_INFTY;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < m-1; j++) {
            d = min(d,
                    ss_distance(L(a[i], a[i+1]-a[i]),
                                L(b[j], b[j+1]-b[j])));
        }
    }
    return d;
}




Weight dijkstra(vector< vector<Weight> >& adj, int start, int goal)
{
    const int n = adj.size();

    vector<bool> visited(n, false);

    typedef pair<Weight, int> Edge;
    priority_queue<Edge, vector<Edge>, greater<Edge> > q;
    q.push(Edge(0, start));

    while(! q.empty()) {
        Edge e = q.top();
        q.pop();

        if (visited[e.second])
            continue;

        //printf("visiting %d with cost %.2f\n", e.second, e.first);
        visited[e.second] = true;

        if (e.second == goal)
            return e.first;

        for(int i = 0; i < n; i++) {
            if (!visited[i]) {
                q.push(Edge(e.first+adj[e.second][i], i));
            }
        }
    }

    return -1;
}



P readPoint() {
    double x, y;
    cin >> x >> y;
    return P(x, y);
}

L readLine() {
    P a, b;
    a = readPoint();
    b = readPoint();
    return L(a, b-a);
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0) {
        int r1, r2, n;
        cin >> r1 >> r2 >> n;
        n+=2;
        vector<G> v(n);
        for(int i = 0; i < r1; i++)
            v[0].push_back(readPoint());
        for(int i = 0; i < r2; i++)
            v[1].push_back(readPoint());
        for(int i = 2; i < n; i++) {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++)
                v[i].push_back(readPoint());
            P p = v[i].front();
            v[i].push_back(p);
        }

        vector< vector<double> > adj(n, vector<double>(n, WEIGHT_INFTY));

        for(int a = 0; a < n; a++) {
            adj[a][a] = 0;
            for(int b = a+1; b < n; b++) {
                double d = nya_distance(v[a], v[b]);
                adj[a][b] = adj[b][a] = d;
            }
        }

        /*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                printf("%.2f\t", adj[i][j]);
            }
            printf("\n");
        }
        */

        double result = dijkstra(adj, 0, 1);

        printf("%.3f\n", result);

    }
    return 0;
}
