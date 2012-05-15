#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long int integer;

integer choose(const int* nums, int n, int r) {
    integer c = 0;
    for(int i = 0; i <= r; i++) {
        c += choose(nums, n-1, r);
    }
    return c;
}




int main() {
    int iCase = 0;
    int n, m;
    while(cin >> n >> m && !(n == 0)) {
        vector<int> nums;
        {
            map<int,int> cnt;
            for(int i = 0; i < n; i++) {
                int k;
                cin >> k;
                if (cnt.find(k) == cnt.end())
                    cnt[k] = 0;
                cnt[k]++;
            }
            for(map<int,int>::iterator it = cnt.begin(); it != cnt.end(); ++it)
                nums.push_back(it->second);
        }
        int s = nums.size();
        vector< vector<integer> > v(s+1, vector<integer>(n+1, 0));
        v[0][0] = 1;
        for(int i = 1; i <= s; i++) {
            for(int j = 0; j <= n; j++) {
                for(int k = 0; k <= nums[i-1]; k++) {
                    if (j-k >= 0)
                        v[i][j] += v[i-1][j-k];
                }
            }
        }
        printf("Case %d:\n", iCase+1);
        for(int i = 0; i < m; i++) {
            int r;
            cin >> r;
            cout << v[s][r] << endl;
        }
        iCase++;
    }
    return 0;
}
