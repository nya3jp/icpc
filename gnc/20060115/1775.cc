#include <cstdio>
#include <vector>
#include <algorithm>

void make(std::vector<int>& u, const std::vector<int>& v, const int i, const int sum) {
    const int n = (int)v.size();
    if (i == n) {
        if (sum > 0)
            u.push_back(sum);
    }
    else {
        make(u, v, i+1, sum);
        make(u, v, i+1, sum+v[i]);
    }
}

int main() {
    std::vector<int> v;
    {
        v.push_back(1);
        int f = 1;
        int i = 1;
        while(f <= 1000000) {
            v.push_back(f);
            i++;
            f *= i;
        }
    }
    std::vector<int> u;
    make(u, v, 0, 0);
    std::sort(u.begin(), u.end());
    /*
    for(int i = 0; i < (int)u.size(); i++) {
        std::printf("%d\n", u[i]);
    }
    */
    while(true) {
        int k;
        std::scanf("%d", &k);
        if (k < 0)
            break;
        std::printf("%s\n",
                    std::binary_search(u.begin(), u.end(), k) ? "YES" : "NO");
    }
    return 0;
}
