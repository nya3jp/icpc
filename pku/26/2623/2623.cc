#include <algorithm>
#include <cstdio>
using namespace std;
int v[250000];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", v+i);
    nth_element(v, v+n/2, v+n);
    if (n%2 == 1) {
        printf("%d.0\n", v[n/2]);
    }
    else {
        nth_element(v, v+n/2-1, v+n);
        printf("%.1f\n", ((double)v[n/2]+v[n/2-1])/2);
    }
    return 0;
}
