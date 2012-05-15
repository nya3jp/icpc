#include <iostream>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


int main() {

    for(;;) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        int previous = 0;
        int next;
        cin >> next;
        next--;

        bool rights[30];

        REP(i, n) {
            char c;
            cin >> c;
            rights[i] = (c == 'R');
        }

        int remain = n;
        bool catched[30] = {};

        int t = 0;
        for(;;) {
            //cout << next+1 << " ";
            if (!catched[next]) {
                catched[next] = true;
                remain--;
            }
            t++;
            swap(previous, next);
            if (remain == 0)
                break;
            int dir = (rights[previous] ? 1 : n-1);
            rights[previous] = !rights[previous];
            next = (next + dir) % n;
            if (next == previous)
                next = (next + dir) % n;
        }

        cout << "Classmate " << previous+1 << " got the ball last after " << t << " tosses." << endl;

    }

    return 0;
}
