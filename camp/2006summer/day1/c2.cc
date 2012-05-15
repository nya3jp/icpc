#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef long long integer;

int n;

struct State {
    int x[10];
    int q, a, b;

    State() {
    }
    State(const int* x0) {
        copy(x0, x0+n, x);
        q = n;
        a = b = 0;
    }
    integer toInteger() const {
        integer repr = 0;
        repr = repr * 100 + q;
        repr = repr * 100 + a;
        for(int i = 0; i < n; i++)
            repr = repr * 10 + x[i];
        //printf("%020lld\n", repr);
        return repr;
    }
    static State fromInteger(integer repr) {
        State s;
        for(int i = 0; i < n; i++) {
            s.x[n-1-i] = repr % 10;
            repr /= 10;
        }
        s.a = repr % 100;
        repr /= 100;
        s.q = repr % 100;
        repr /= 100;
        s.b = n - s.q - s.a;
        return s;
    }
    void qq(int k) {
        assert(k <= q);
        rotate(x, x+k, x+q);
    }
    void qa(int k) {
        assert(k <= q);
        rotate(x, x+k, x+q);
        reverse(x+k, x+q);
        q -= k;
        a += k;
    }
    void qb(int k) {
        assert(k <= q);
        rotate(x, x+k, x+n);
        q -= k;
        b += k;
    }
    void aq(int k) {
        assert(k <= a);
        q += k;
        a -= k;
    }
    void bq(int k) {
        assert(k <= b);
        rotate(x+q, x+n-k, x+n);
        reverse(x+q, x+q+k);
        q += k;
        b -= k;
    }
    void ab(int k) {
        assert(k <= a);
        rotate(x+q, x+q+k, x+n);
        a -= k;
        b += k;
    }
    void ba(int k) {
        assert(k <= b);
        rotate(x+q, x+n-k, x+n);
        a += k;
        b -= k;
    }
};

int init_queue[10];
queue<integer> q;
map<integer, int> dist;

void grow(integer repr, int d) {
    if (dist.count(repr) == 0) {
        dist[repr] = d;
        q.push(repr);
    }
    else if (dist[repr]*d < 0) {
        throw abs(d) + abs(dist[repr]) - 2;
    }
}

#define DO(c) s = so; \
              if (sgn<0) { reverse(s.x, s.x+s.q); } \
              s.c(k); \
              if (sgn<0) { reverse(s.x, s.x+s.q); } \
              grow(s.toInteger(), d+sgn);

bool branch(integer repr) {
    int d = dist[repr];
    int sgn = (d > 0 ? 1 : -1);
    State so = State::fromInteger(repr);
    State s;
    for(int k = 1; k <= so.q; k++) {
        DO(qq);
        DO(qa);
        DO(qb);
    }
    for(int k = 1; k <= so.a; k++) {
        DO(aq);
        DO(ab);
    }
    for(int k = 1; k <= so.b; k++) {
        DO(bq);
        DO(ba);
    }
    return false;
}

int solve() {
    integer initrepr = State(init_queue).toInteger();

    integer lastrepr;
    {
        int last[10];
        for(int i = 0; i < n; i++)
            last[i] = i;
        lastrepr = State(last).toInteger(); 
    }

    if (initrepr == lastrepr)
        return 0;

    q = queue<integer>();
    dist.clear();
    q.push(initrepr);
    dist[initrepr] = 1;
    q.push(lastrepr);
    dist[lastrepr] = -1;

    try {
        int last = 0;
        for(;;) {
            integer repr = q.front();
            q.pop();
            
            int d = dist[repr];
            if (last != abs(d)) {
                //cout << "depth=" << abs(d) << " : size=" << dist.size() << endl;
                last = abs(d);
            }
            
            branch(repr);
        }
    }
    catch(int result) {
        return result;
    }
    return -1;
}

int main() {

    /*
    n = 10;

    for(;;) {
        for(int i = 0; i < n; i++)
            init_queue[i] = i;
        for(int i = 0; i < n; i++)
            swap(init_queue[i], init_queue[rand()%(n-i)+i]);
        cout << "Input: ";
        for(int i = 0; i < n; i++)
            cout << init_queue[i] << ' ';
        cout << endl;
        cout << solve() << endl;
    }
    */

    ifstream cin("C.txt");

    while(cin >> n && n > 0) {

        for(int i = 0; i < n; i++)
            cin >> init_queue[i];

        cout << solve() << endl;

    }

    return 0;
}


