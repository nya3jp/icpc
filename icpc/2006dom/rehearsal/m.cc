#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int main() {

    vector<int> v;

    for(int k; cin >> k && k > 0; )
        v.push_back(k);

    vector<int> u(v);
    sort(u.begin(), u.end());
    int n = u.size();

    int base;
    for(int i = 0; i < n-1; i++) {
        if (u[i+1]-u[i] == 2)
            base = u[i] + 1;
    }

    for(int i = 0; i < n; i++) {
        int k = 
        cout << (n < N ? "smaller" : "larger") << endl;
    }

    return 0;
}
