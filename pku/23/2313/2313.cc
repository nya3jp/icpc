#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cin >> n;

    int bottom, top;
    {
        int a1;
        cin >> a1;
        bottom = top = a1;
    }

    int cost = 0;
    for(int i = 1; i < n; i++) {

        int a;
        cin >> a;

        int newBottom = min(a, top);
        int newTop = max(a, bottom);

        cost += newTop-newBottom;

        bottom = newBottom;
        top = newTop;

    }

    cout << cost << endl;

    
    return 0;
}
