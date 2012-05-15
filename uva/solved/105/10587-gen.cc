#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    int t = 100;
    std::printf("%d\n", t);
    for(int j = 0; j < t; j++) {
        int n = 10000;
        std::printf("%d\n", n);
        for(int i = 0; i < n; i++) {
            std::printf("%d %d\n", std::rand()%10000000, std::rand()%10000000);
        }
    }
    return 0;
}
