#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Range {
    int from, to;
};
struct EndPoint {
    int x;
    int id;
    bool begins;
};
bool operator<(const EndPoint& a, const EndPoint& b) {
    return make_pair(a.x, a.id) < make_pair(b.x, b.id);
}


int main() {

    int n;
    while(scanf("%d", &n) == 1 && n > 0) {

        vector<Range> ranges(n);
        vector<EndPoint> points(2*n);
        for(int i = 0; i < n; i++) {
            int f, t;
            scanf("%d%d", &f, &t);
            ranges[i] = (Range){f, t};
            points[2*i] = (EndPoint){f, i, true};
            points[2*i+1] = (EndPoint){t, i, false};
        }
        sort(points.begin(), points.end());

        vector<int> results(n);
        set<EndPoint> s;
        for(int i = 0; i < 2*n; i++) {
            EndPoint& e = points[i];
            if (e.begins) {
                s.insert(e);
            }
            else {
                int id = e.id;
                EndPoint b = {ranges[id].from, id, true};
                set<EndPoint>::iterator it = s.find(b);
                set<EndPoint>::iterator end = s.end();
                results[id] = end - it - 1;
                s.erase(it);
            }
        }

        printf("%d", results[0]);
        for(int i = 1; i < n; i++)
            printf(" %d", results[i]);
        printf("\n");

    }

    return 0;
}



