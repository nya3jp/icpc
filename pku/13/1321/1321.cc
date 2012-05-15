#include <iostream>
#include <vector>
#include <complex>

using namespace std;

typedef complex<int> Pt;

int search(vector<Pt>& points, int i, int u, int k, int n, vector<bool>& row, vector<bool>& col) {
    int m = points.size();
    if (u+(m-i) < k || u > k)
        return 0;
    if (i == m)
        return 1;
    Pt& pt = points[i];
    int sum = 0;
    if ((!row[pt.real()]) && (!col[pt.imag()])) {
        row[pt.real()] = true;
        col[pt.imag()] = true;
        sum += search(points, i+1, u+1, k, n, row, col);
        row[pt.real()] = false;
        col[pt.imag()] = false;
    }
    sum += search(points, i+1, u, k, n, row, col);
    return sum;
}

int main() {
    int n, k;
    while(cin >> n >> k && !(n == -1 && k == -1)) {
        vector<Pt> points;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for(int j = 0; j < n; j++) {
                if (s[j] == '#') {
                    points.push_back(Pt(i, j));
                }
            }
        }
        vector<bool> row(n, false), col(n, false);
        cout << search(points, 0, 0, k, n, row, col) << endl;
    }
    return 0;
}
