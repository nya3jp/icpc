#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    if (argc < 2)
        printf("%s n\n", argv[0]);
    printf("%d\n\n", argc-1);
    for(int a = 1; a < argc; a++) {
        int n;
        sscanf(argv[a], "%d", &n);
        printf("%d\n", n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                printf("%c", ((rand()&0xb000) != 0 ? '*' : '.'));
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
