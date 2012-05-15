#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef long long integer;

int n;

template<class Iter>
void unrotate(Iter first, Iter mid, Iter last) {
    rotate(first, first+(last-mid), last);
}

/*
 * Q(0) ... Q(q-1) A(0) ... A(a-1) B(0) ... B(b-1)
 */
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
    void qq(int k, bool rev) {
        //assert(k <= q);
        if (!rev) {
            rotate(x, x+k, x+q);
        }
        else {
            unrotate(x, x+k, x+q);
        }
    }
    void qa(int k, bool rev) {
        //assert(k <= q);
        if (!rev) {
            rotate(x, x+k, x+q);
            reverse(x+k, x+q);
            q -= k;
            a += k;
        }
        else {
            a -= k;
            q += k;
            reverse(x+k, x+q);
            unrotate(x, x+k, x+q);
        }
    }
    void qb(int k, bool rev) {
        //assert(k <= q);
        if (!rev) {
            rotate(x, x+k, x+n);
            q -= k;
            b += k;
        }
        else {
            b -= k;
            q += k;
            unrotate(x, x+k, x+n);
        }
    }
    void aq(int k, bool rev) {
        //assert(k <= a);
        if (!rev) {
            q += k;
            a -= k;
        }
        else {
            a += k;
            q -= k;
        }
    }
    void bq(int k, bool rev) {
        //assert(k <= b);
        if (!rev) {
            rotate(x+q, x+n-k, x+n);
            reverse(x+q, x+q+k);
            q += k;
            b -= k;
        }
        else {
            b += k;
            q -= k;
            reverse(x+q, x+q+k);
            unrotate(x+q, x+n-k, x+n);
        }
    }
    void ab(int k, bool rev) {
        //assert(k <= a);
        if (!rev) {
            rotate(x+q, x+q+k, x+n);
            a -= k;
            b += k;
        }
        else {
            b -= k;
            a += k;
            unrotate(x+q, x+q+k, x+n);
        }
    }
    void ba(int k, bool rev) {
        //assert(k <= b);
        if (!rev) {
            rotate(x+q, x+n-k, x+n);
            a += k;
            b -= k;
        }
        else {
            b += k;
            a -= k;
            unrotate(x+q, x+n-k, x+n);
        }
    }
};

int init_queue[10];
queue<integer> q;
map<integer, int> dist;
int result;

bool grow(integer repr, int d) {
    if (dist.count(repr) == 0) {
        dist[repr] = d;
        q.push(repr);
    }
    else if (dist[repr]*d < 0) {
        result = abs(d) + abs(dist[repr]);
        return true;
    }
    return false;
}

bool branch(integer repr) {
    int d = dist[repr];
    int sgn = (d > 0 ? 1 : -1);
    bool rev = sgn < 0;
    State so = State::fromInteger(repr);
    State s;
    if (!rev) {
        for(int k = 1; k <= so.q; k++) {
            s = so; s.qq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.qa(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.qb(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
        for(int k = 1; k <= so.a; k++) {
            s = so; s.aq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.ab(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
        for(int k = 1; k <= so.b; k++) {
            s = so; s.bq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.ba(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
    }
    else {
        for(int k = 1; k <= so.q; k++) {
            s = so; s.qq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.aq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.bq(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
        for(int k = 1; k <= so.a; k++) {
            s = so; s.qa(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.ba(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
        for(int k = 1; k <= so.b; k++) {
            s = so; s.qb(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
            s = so; s.ab(k, rev);
            if (grow(s.toInteger(), d+sgn))
                return true;
        }
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

    int last = 0;
    while(!q.empty()) {
        integer repr = q.front();
        q.pop();

        int d = dist[repr];
        if (last != abs(d)) {
            //cout << "depth=" << abs(d) << " : size=" << dist.size() << endl;
            last = abs(d);
        }

        if (branch(repr))
            break;
    }

    return result-2;
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


