#include <cstdio>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main() {

    int nCases;
    scanf("%d", &nCases);

    REP(iCase, nCases) {

        int n;
        scanf("%d", &n);

        priority_queue<int, vector<int>, greater<int> > q;

        REP(i, n) {
            int x;
            scanf("%d", &x);
            q.push(x);
        }

        int res = 0;
        for(;;) {
            if (q.empty())
                break;
            int a = q.top();
            q.pop();
            if (q.empty())
                break;
            int b = q.top();
            q.pop();
            res += a + b;
            q.push(a+b);
        }

        printf("%d\n", res);

    }

    return 0;
}

