/*
 * UVA 10482 The Candyman Can
 * 2005-07-21
 * by nya
 */

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

void dfs(const std::vector<int>& candies,
         const int iCandy,
         const int larger,
         const int smaller,
         std::vector< std::set< std::pair<int,int> > >& mem)
{
    const int nCandies = candies.size();
    if (mem[iCandy].insert( std::make_pair(larger, smaller) ).second) {
        if (iCandy < nCandies) {
            int candy = candies[iCandy];
            dfs(candies,
                iCandy+1,
                larger+candy,
                smaller,
                mem);
            dfs(candies,
                iCandy+1,
                std::max(larger, smaller+candy),
                std::min(larger, smaller+candy),
                mem);
            if (smaller >= candy) {
                dfs(candies,
                    iCandy+1,
                    larger-candy,
                    smaller-candy,
                    mem);
            }
            else if (larger >= candy) {
                dfs(candies,
                    iCandy+1,
                    larger-smaller,
                    candy-smaller,
                    mem);
            }
            else {
                dfs(candies,
                    iCandy+1,
                    candy-smaller,
                    larger-smaller,
                    mem);
            }
        }
    }
}

int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        int nCandies;
        std::cin >> nCandies;
        std::vector<int> candies(nCandies);
        for(int i=0; i<nCandies; i++)
            std::cin >> candies[i];
        std::sort(candies.begin(), candies.end());
        std::vector< std::set< std::pair<int,int> > > mem(nCandies+1);
        dfs(candies, 0, 0, 0, mem);
        int ans = mem[nCandies].begin()->first;
        std::cout << "Case " << (iCase+1) << ": " << ans << std::endl;
    }
    return 0;
}
