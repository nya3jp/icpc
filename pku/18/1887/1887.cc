#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;


int main() {

    int iCase = 0;
    while(true) {

        vector<int> lis;

        int h;
        scanf("%d", &h);
        if (h < 0)
            break;
        do {

            h = 40000 - h;
            vector<int>::iterator it = upper_bound(lis.begin(), lis.end(), h);
            if (it == lis.end())
                lis.push_back(h);
            else
                *it = h;
            
        } while(scanf("%d", &h), h != -1);

        if (iCase > 0)
            printf("\n");
        printf("Test #%d:\n  maximum possible interceptions: %d\n",
               iCase+1, (int)lis.size());

        iCase++;
    }

    return 0;
}

