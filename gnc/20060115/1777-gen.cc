#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    for(int t = 0; t < 10; t++) {
        bool dests[30];
        int n = 0;
        for(int i = 0; i < 30; i++) {
            bool yes = ((rand() & 0x10000) != 0);
            dests[i] = yes;
            if (yes)
                n++;
        }
        std::printf("%d", n);
        for(int i = 0; i < 30; i++) {
            if (dests[i])
                std::printf(" %d", i+2);
        }
        std::printf("\n");
    }
    std::printf("0\n");
    return 0;
}
