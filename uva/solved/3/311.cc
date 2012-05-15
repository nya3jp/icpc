#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;


int main() {
    while(true) {
        int v[6+1];
        for(int i = 0; i < 6; i++)
            cin >> v[i+1];

        int n = 0;
        while(true) {
            if (accumulate(v+1, v+7, (int)0) == 0)
                break;
            if (v[6] > 0) {
                n += v[6];
                v[6] = 0;
            }
            else if (v[5] > 0) {
                v[5]--;
                v[1] -= min(v[1], 11);
                n++;
            }
            else if (v[4] > 0) {
                v[4]--;
                int k2 = min(v[2], 5);
                int k1 = min(v[1], 20-4*k2);
                v[2] -= k2;
                v[1] -= k1;
                n++;
            }
            else if (v[3] > 0) {
                int k3 = min(v[3], 4);
                int k2 = min(v[2], (k3 == 1 ? 5 :
                                    k3 == 2 ? 3 :
                                    k3 == 3 ? 1 :
                                    0));
                int k1 = min(v[1], 36 - k3*9 - k2*4);
                v[3] -= k3;
                v[2] -= k2;
                v[1] -= k1;
                n++;
            }
            else if (v[2] > 0) {
                int k2 = min(v[2], 9);
                int k1 = min(v[1], 36-k2*4);
                v[2] -= k2;
                v[1] -= k1;
                n++;
            }
            else if (v[1] > 0) {
                v[1] -= min(v[1], 36);
                n++;
            }
        }
        if (n == 0)
            break;

        cout << n << endl;
    }
    return 0;
}
