#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order {
    int from, to, num;
};

int solve(int depth, int total, const vector<Order>& v, vector<int>& reserve, int capacity, int& best, const vector<int>& sums) {
    const int n = v.size();
    best = max(best, total);
    int x = 0;
    for(int i = depth; i < n; i++) {
        if (total + sums[i] > best) {
            const Order& o = v[i];
            for(int j = o.from; j < o.to; j++)
                reserve[j]+=o.num;
            if (*max_element(reserve.begin(), reserve.end()) <= capacity) {
                int earning = (o.to-o.from)*o.num;
                x = max(x, earning + solve(i+1, total+earning, v, reserve, capacity, best, sums));
            }
            for(int j = o.from; j < o.to; j++)
                reserve[j]-=o.num;
        }
    }
    return x;
}

int main() {
    int n, m, k;
    while(cin >> n >> m >> k && !(n == 0 && m == 0 && k == 0)) {
        vector<Order> v(k);
        for(int i = 0; i < k; i++) {
            Order& o = v[i];
            cin >> o.from >> o.to >> o.num;
        }
        vector<int> sums(k+1, 0);
        for(int i = k-1; i >= 0; i--) {
            Order& o = v[i];
            sums[i] = sums[i+1] + (o.to-o.from)*o.num;
        }
        vector<int> reserve(m, 0);
        int best = 0;
        cout << solve(0, 0, v, reserve, n, best, sums) << endl;
    }
    return 0;
}

