/*
 * UVA 10400 Game Show Math
 * 2005-07-20
 * by nya
 */

#include <iostream>
#include <vector>
#include <bitset>


struct Found {};

inline bool inrange(int n) {
    return (-32000 <= n && n <= 32000);
}

void dfs(const std::vector<int>& v,
         const int ans,
         int depth,
         int cur,
         std::vector<char>& op,
         std::vector< std::bitset<64001> >& mem)
{
    const int n = v.size();

    if (depth == n) {
        if (cur == ans)
            throw Found();
    }
    else {
        if (! mem[depth][cur+32000]) {
            mem[depth][cur+32000] = true;
            const int k = v[depth];
            if (inrange(cur+k)) {
                op.push_back('+');
                dfs(v, ans, depth+1, cur+k, op, mem);
                op.pop_back();
            }
            if (inrange(cur-k)) {
                op.push_back('-');
                dfs(v, ans, depth+1, cur-k, op, mem);
                op.pop_back();
            }
            if (inrange(cur*k)) {
                op.push_back('*');
                dfs(v, ans, depth+1, cur*k, op, mem);
                op.pop_back();
            }
            if (k != 0 && cur%k == 0) {
                op.push_back('/');
                dfs(v, ans, depth+1, cur/k, op, mem);
                op.pop_back();
            }
        }
    }
}

int main()
{
    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int n;
        std::cin >> n;

        std::vector<int> v(n);
        for(int i=0; i<n; i++)
            std::cin >> v[i];
        int ans;
        std::cin >> ans;

        std::vector< std::bitset<64001> > mem(n);
        std::vector<char> op;

        try {
            dfs(v, ans, 1, v[0], op, mem);
            std::cout << "NO EXPRESSION" << std::endl;
        }
        catch(Found) {
            op.push_back('=');
            for(int i=0; i<n; i++) {
                std::cout << v[i] << op[i];
            }
            std::cout << ans << std::endl;
        }

    }

    return 0;
}


