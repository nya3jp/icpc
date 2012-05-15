#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

#define N 1000

#define for if(0);else for
typedef __int64 integer;

int n, m, k;

int likes[N];
map<int, int> back;
set<int> visited;

int count_bits(int n) {
    n = ((n>>1 )&0x55555555) + (n&0x55555555);
    n = ((n>>2 )&0x33333333) + (n&0x33333333);
    n = ((n>>4 )&0x0f0f0f0f) + (n&0x0f0f0f0f);
    n = ((n>>8 )&0x00ff00ff) + (n&0x00ff00ff);
    n = ((n>>16)&0x0000ffff) + (n&0x0000ffff);
    return n;
}

bool generate_subset(int s, int t, int c, int i, int r, int m, int a, bool (*func)(int, int), int param) {
    if (r+a<c)
        return false;
    if (r == c)
        return func(t, param);
    if (i == m)
        return false;

    int b = 1<<i;
    int aa = a - ((s&b) != 0 ? 1 : 0);

    if ((s&b) == 0) {
        return generate_subset(s, t, c, i+1, r, m, aa, func, param);
    }
    else if (rand()&0x10000) {
        return generate_subset(s, t|b, c, i+1, r+1, m, aa, func, param) ||
            generate_subset(s, t, c, i+1, r, m, aa, func, param);
    }
    else {
        return generate_subset(s, t, c, i+1, r, m, aa, func, param) ||
            generate_subset(s, t|b, c, i+1, r+1, m, aa, func, param);
    }


    if ((s&b) != 0 && generate_subset(s, t|b, c, i+1, r+1, m, aa, func, param))
        return true;

    return generate_subset(s, t, c, i+1, r, m, aa, func, param);
}

bool augment(int left);

bool check1(int right, int left) {
    //printf("check left=%d right=%d\n", left, right);
    if (back.count(right) == 0) {
        back[right] = left;
        return true;
    }
    return false;
}

bool check2(int right, int left) {
    //printf("check left=%d right=%d\n", left, right);
    if (visited.count(right) > 0)
        return false;
    visited.insert(right);
    if (augment(back[right])) {
        back[right] = left;
        return true;
    }
    return false;
}
bool check0(int right, int left) {
    //printf("check left=%d right=%d\n", left, right);
    if (visited.count(right) > 0)
        return false;
    visited.insert(right);
    if (back.count(right) == 0 || augment(back[right])) {
        back[right] = left;
        return true;
    }
    return false;
}

bool augment(int left) {
    //printf("augment left=%d like=%d\n", left, likes[left]);
    //return generate_subset(likes[left], 0, k, 0, 0, m, count_bits(likes[left]), check0, left);
    return generate_subset(likes[left], 0, k, 0, 0, m, count_bits(likes[left]), check1, left) ||
        generate_subset(likes[left], 0, k, 0, 0, m, count_bits(likes[left]), check2, left);
}

bool bit_compare(int a, int b) {
    return (count_bits(a) < count_bits(b));
}

integer choose(int n, int r) {
    integer c = 1;
    for(int i = 1, j = 1; i <= n && j <= r; ) {
        if (j <= r && c%j == 0) {
            c /= j++;
        }
        else if (i <= n) {
            c *= i++;
        }
    }
    return c;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < n; i++) {
        int c;
        scanf("%d", &c);
        likes[i] = 0;
        for(int j = 0; j < c; j++) {
            int a;
            scanf("%d", &a);
            likes[i] |= 1<<(a-1);
        }
        if (c < k)
            likes[i] = 0;
    }
    sort(likes, likes+n, bit_compare);
    n = remove(likes, likes+n, 0) - likes;

    int failed = -1;
    int res = 0;
    for(int i = 0; i < n; i++) {
        if (likes[i] != failed) {
            if (choose(count_bits(likes[i]), k) >= n) {
                res++;
            }
            else {
                visited.clear();
                if (augment(i))
                    res++;
                else
                    failed = likes[i];
            }
        }
        //printf("%d\n", i);
        /*
        for(map<int,int>::iterator it = back.begin(); it != back.end(); ++it)
            printf("%d -> %d\n", it->second, it->first);
        printf("--------\n");
        //*/
    }

    printf("%d\n", res);
    return 0;
}

