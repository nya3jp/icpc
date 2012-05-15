#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int pow(int e, vector<int>& x) {
    if (x.empty()) {
        return 1;
    }

    int k = x.back();
    x.pop_back();
    int t = pow(e, x);
    x.push_back(k);
    int y = 1;
    for(int i = 0; i < 10; i++)
        y = (y*t) % 10;
    for(int i = 0; i < k; i++)
        y = (y*e) % 10;
    return y;
}

int main() {

    for(;;) {

        string s1, s2;
        cin >> s1 >> s2;
        if (s1 == "0" && s2 == "0")
            break;

        int e = (int)(s1[s1.size()-1] - '0');
        int n = s2.size();
        vector<int> x(n);
        for(int i = 0; i < n; i++)
            x[i] = (int)(s2[i] - '0');

        cout << pow(e, x) << endl;

    }

    return 0;
}
