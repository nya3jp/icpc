#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using namespace std;

typedef pair<int,int> Point;

const int INF = 0x7fffffff;

struct Solver {
    int n;
    vector<Point> v;
    vector<Point> u;
    vector<char> trace;
    Point pos;

    Solver() {
        cin >> n;
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> y >> x;
            v.push_back(Point(x, y));
        }
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> y >> x;
            u.push_back(Point(x, y));
        }
        sort(v.begin(), v.end());
        sort(u.begin(), u.end());
    }

    void solve() {

        {
            Point m(INF, INF);
            for(int i = 0; i < n; i++) {
                m.first = min(m.first, u[i].first);
                m.second = min(m.second, u[i].second);
            }
            for(int i = 0; i < n; i++) {
                u[i].first = u[i].first - m.first - 9 - n - 3;
                u[i].second = u[i].second - m.second;
            }
        }

        pos = Point(0, 0);
        for(int i = 0; i < n; i++) {
            moveX(v[i].first+1);
            moveY(v[i].second);
            moveX(u[i].first+3);
            if (u[i].second < v[i].second) {
                moveY(v[i].second+1);
                moveX(u[i].first+2);
                moveY(u[i].second+1);
                moveX(u[i].first+3);
                moveY(u[i].second);
            }
            else if (u[i].second > v[i].second) {
                moveY(v[i].second-1);
                moveX(u[i].first+2);
                moveY(u[i].second-1);
                moveX(u[i].first+3);
                moveY(u[i].second);
            }
            else {
                // do nothing
            }
            moveX(u[i].first+1);
            moveX(u[i].first+3);
            moveY(0);
        }

        printTrace();
    }

    void moveX(int x) {
        int dx = x - pos.first;
        if (dx > 0) {
            for(int i = 0; i < dx; i++)
                trace.push_back('L');
        }
        else if (dx < 0) {
            for(int i = 0; i < -dx; i++)
                trace.push_back('R');
        }
        pos.first = x;
    }

    void moveY(int y) {
        int dy = y - pos.second;
        if (dy > 0) {
            for(int i = 0; i < dy; i++)
                trace.push_back('U');
        }
        else if (dy < 0) {
            for(int i = 0; i < -dy; i++)
                trace.push_back('D');
        }
        pos.second = y;
    }

    void printTrace() {
        cout << (int)trace.size() << endl;
        cout << string(trace.begin(), trace.end()) << endl;
        trace.clear();
    }

};

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0) {
        Solver s;
        s.solve();
    }
}
