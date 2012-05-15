#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef int Order[26][26];

struct Inconsistent {};

bool set_order(Order& order, int a, int b) {
    if (a == b)
        throw Inconsistent();
    bool changed = false;
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            if ((order[i][a] < 0 || i == a) && (order[b][j] < 0 || j == b)) {
                if (order[i][j] == 1)
                    throw Inconsistent();
                if (order[i][j] == 0)
                    changed = true;
                order[i][j] = -1;
                order[j][i] = 1;
            }
        }
    }
    return changed;
}

bool fullorder(Order& order, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (i != j && order[i][j] == 0)
                return false;
    return true;
}

void print_order(Order& order, int n) {
    vector< pair<int,char> > v(n);
    for(int i = 0; i < n; i++)
        v[i] = make_pair(count(order[i], order[i]+n, 1), (char)('A' + i));
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++)
        printf("%c", v[i].second);
}

void print_table(Order& order, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%2d ", order[i][j]);
        printf("\n");
    }
}

int main() {

    while(true) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;

        int order[26][26];
        for(int i = 0; i < 26; i++)
            for(int j = 0; j < 26; j++)
                order[i][j] = 0;

        int last = -1;
        bool determined = false;
        bool inconsistent = false;
        for(int q = 0; q < m; q++) {
            char c1, c2;
            scanf(" %c < %c", &c1, &c2);
            int a, b;
            a = c1 - 'A';
            b = c2 - 'A';
            if (!inconsistent && !determined) {
                try {
                    if (set_order(order, a, b)) {
                        last = q;
                        determined = fullorder(order, n);
                    }
                }
                catch(Inconsistent) {
                    inconsistent = true;
                    last = q;
                }
            }
            //print_table(order, n);
        }

        if (inconsistent) {
            printf("Inconsistency found after %d relations.\n", last+1);
        }
        else if (determined) {
            printf("Sorted sequence determined after %d relations: ", last+1);
            print_order(order, n);
            printf(".\n");
        }
        else {
            printf("Sorted sequence cannot be determined.\n");
        }



    }


    return 0;
}

