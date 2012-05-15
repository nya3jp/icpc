#include <cstdio>
#include <limits>

int main() {
    int n;
    std::scanf("%d", &n);
    int iMinDiff = std::numeric_limits<int>::max();
    int iMinDiffEdge = -1;
    int iTotalLength = -1;
    {
        int ld = 0;
        for(int i=0; i<n-1; i++) {
            int nd;
            std::scanf("%d", &nd);
            int d = nd - ld;
            ld = nd;
            if (0 < i && i < n-2 && d < iMinDiff) {
                iMinDiff = d;
                iMinDiffEdge = i;
            }
        }
        iTotalLength = ld;
    }
    if (iMinDiffEdge == -1) {
        std::printf("0\n");
    }
    else {
        std::printf("%d\n", iTotalLength + iMinDiff);
        std::printf("%d %d %d %d\n", iMinDiffEdge+2, 1, n, iMinDiffEdge+1);
    }
    return 0;
}
