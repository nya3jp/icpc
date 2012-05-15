#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string pivot;
bool pivot_less(const string& a, const string& b) {
    int n = a.size();
    int ka = 0, kb = 0;
    for(int i = 0; i < n; i++)
        if (a[i] != pivot[i])
            ka++;
    for(int i = 0; i < n; i++)
        if (b[i] != pivot[i])
            kb++;
    return (ka < kb);
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        vector<string> v(n);
        for(int i = 0; i < n; i++)
            cin >> v[i];
        pivot = v[0];
        sort(v.begin()+1, v.end(), pivot_less);
        for(int i = 0; i < n; i++)
            cout << v[i] << endl;
    }
    return 0;
}
