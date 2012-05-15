#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Cow {
    int weight, strength;
};
bool operator<(const Cow& a, const Cow& b) {
    return (a.weight+a.strength < b.weight+b.strength);
}

int main() {

    int n;
    scanf("%d", &n);

    vector<Cow> cows(n);
    for(int i = 0; i < n; i++) {
        Cow& cow = cows[i];
        scanf("%d%d", &cow.weight, &cow.strength);
    }

    sort(cows.begin(), cows.end());

    int res = 0x80000000;
    int w = 0;
    for(int i = 0; i < n; i++) {
        res >?= w - cows[i].strength;
        w += cows[i].weight;
    }

    printf("%d\n", res);
    return 0;
}
