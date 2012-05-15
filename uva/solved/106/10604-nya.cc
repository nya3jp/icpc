/*
 * UVA 10604 - CHEMICAL REACTION
 * 2005-12-10
 * by nya
 *
 * Be careful: The result of mixing chemical A with chemical B
 *             may differ from that of chemical B with chemical A.
 */


#define NDEBUG

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>

class Solver {
public:
    Solver(int nTypes, const std::vector< std::vector< std::pair<int, int> > >& reaction)
        : nTypes(nTypes), reaction(reaction) {
        assert(1 <= nTypes && nTypes <= 6);
        memory.clear();
        {
            std::vector<int> v(nTypes, 0);
            memory[vectorToId(v)] = 0;
            for(int iType = 0; iType < nTypes; iType++) {
                v[iType]++;
                memory[vectorToId(v)] = 0;
                v[iType]--;
            }
        }
    }

    int solve(const std::vector<int>& v) {
        int id = vectorToId(v);
        if (memory.find(id) == memory.end()) {
            int iMinCost = 0x7fffffff; // std::numeric_limits<int>::max();
            std::vector<int> u(v);
            for(int iType = 0; iType < nTypes; iType++) {
                for(int jType = 0; jType < nTypes; jType++) {
                    u[iType]--; u[jType]--;
                    if (u[iType] >= 0 && u[jType] >= 0) {
                        int iNewType = reaction[iType][jType].first;
                        int iReactionHeat = reaction[iType][jType].second;
                        u[iNewType]++;
                        int iCost = solve(u) + iReactionHeat;
                        iMinCost = std::min(iMinCost, iCost);
                        u[iNewType]--;
                    }
                    u[iType]++; u[jType]++;
                }
            }
#ifndef NDEBUG
            {
                for(int i = 0; i < nTypes; i++)
                    std::cout << v[i] << ' ';
                std::cout << ": " << iMinCost << std::endl;
            }
#endif
            memory[id] = iMinCost;
        }
        return memory[id];
    }

private:
    static inline int vectorToId(const std::vector<int>& v) {
        int id = 0;
        for(int i = 0; i < (int)v.size(); i++)
            id = id*16 + v[i];
        return id;
    }

private:
    const int nTypes;
    std::map<int, int> memory;
    std::vector< std::vector< std::pair<int, int> > > reaction;
};



int main() {
    int nCases;
    std::cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {
        int nTypes;
        std::cin >> nTypes;
        std::vector< std::vector< std::pair<int,int> > > reaction(nTypes, std::vector< std::pair<int,int> >(nTypes));
        for(int iType = 0; iType < nTypes; iType++) {
            for(int jType = 0; jType < nTypes; jType++) {
                std::pair<int,int>& pair = reaction[iType][jType];
                std::cin >> pair.first >> pair.second;
                pair.first--;
            }
        }
        std::vector<int> chemicals(nTypes, 0);
        {
            int nChemicals;
            std::cin >> nChemicals;
            for(int i = 0; i < nChemicals; i++) {
                int iType;
                std::cin >> iType;
                iType--;
                chemicals[iType]++;
            }
        }
        { char c; std::cin >> c; }
        Solver solver(nTypes, reaction);
        std::cout << solver.solve(chemicals) << std::endl;
    }

    return 0;
}


