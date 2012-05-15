/*
 * UVA 10412 Big Big Trees
 * 2005-09-27
 * by nya
 */

#define NDEBUG
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#define MAX_HEIGHT 20

const double EP = 1.0e-6;

#define LE(x, y) ( (x)+EP < (y) )

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

double theta(int y, int x) {
    int ax, ay;
    ax = abs(x);
    ay = abs(y);
    double th = (ax==0 && ay == 0) ? 0.0 : (double)y/(ay+ax);
    if (x < 0) {
        if (y >= 0)
            th = 2.0 - th;
        else
            th = -2.0 - th;
    }
    return th/2;
}

struct Leaf {
    int len;
    double lowerth, upperth;
};

int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int nTrees, iTreeInterval, iJumpDistance;
        std::cin >> nTrees >> iTreeInterval >> iJumpDistance;

        std::vector< std::vector<Leaf> > trees(nTrees);

        for(int iTree=0; iTree<nTrees; iTree++) {

            std::vector<Leaf>& tree = trees[iTree];
            int nLeaves;
            std::cin >> nLeaves;

            // read tree data
            tree.resize(nLeaves);
            for(int iLeaf=0; iLeaf<nLeaves; iLeaf++) {
                std::cin >> tree[iLeaf].len;
            }

            // calc possible lower&upper angle
            for(int i=0; i<nLeaves; i++) {
                Leaf& leaf = tree[i];
                leaf.lowerth = -1.0;
                leaf.upperth = 1.0;
                for(int j=i-1; j>=0; j--) {
                    int dx = tree[j].len - leaf.len;
                    int dy = j - i;
                    double th = theta(dy, dx);
                    leaf.lowerth = std::max(leaf.lowerth, th);
                }
                for(int j=i+1; j<nLeaves; j++) {
                    int dx = tree[j].len - leaf.len;
                    int dy = j - i;
                    double th = theta(dy, dx);
                    leaf.upperth = std::min(leaf.upperth, th);
                }
            }
        }

        int iWalkDistance = 0;
        for(int iTree=0; iTree<nTrees-1; iTree++) {
#ifndef NDEBUG
            std::printf("Jump %d:\n", iTree);
#endif
            int iBestSkip = 0;
            const std::vector<Leaf>& tree1 = trees[iTree];
            const std::vector<Leaf>& tree2 = trees[iTree+1];

            for(int i=0; i<(int)tree1.size(); i++) {
                for(int j=0; j<(int)tree2.size(); j++) {
#ifndef NDEBUG
                    std::printf("%2d - %2d: ", i, j);
#endif
                    const Leaf& leaf1 = tree1[i];
                    const Leaf& leaf2 = tree2[j];

                    int dx = iTreeInterval - leaf1.len - leaf2.len;
                    int dy = j - i;
#ifndef NDEBUG
                    std::printf("d=(%d,%d) a=%.3lf\n", dx, dy, theta(dy,dx));
#endif
                    if (dx > iBestSkip) { // worth to check?

                        if (dx*dx + dy*dy <= iJumpDistance*iJumpDistance) { // possible to jump?

                            double th = theta(dy, dx);

                            if (LE(leaf1.lowerth, th) && LE(th, leaf1.upperth) &&
                                LE(leaf2.lowerth, -th) && LE(-th, leaf2.upperth)) { // no object?
#ifndef NDEBUG
                                std::printf("possible to jump.\n");
#endif
                                iBestSkip = dx;
                            }

                        }
                    }
                }
            }

            iWalkDistance += iTreeInterval - iBestSkip;

        }

        std::cout << iWalkDistance << std::endl;

    }
    return 0;
}
