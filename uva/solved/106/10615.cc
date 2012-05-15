#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


enum Const { UNMATCHED = -3, NONE = -2, WHITE = -1 };

struct BipartiteGraph {
    const int lefts, rights;
    vector< vector<int> > edges;        // left->right->color
    vector< vector<int> > left_colors;  // left->color->right
    vector< vector<int> > right_colors; // right->color->left
    vector<int> left_degrees;
    vector<int> right_degrees;

    vector<bool> visited;

    BipartiteGraph(int lefts, int rights)
        : lefts(lefts), rights(rights), edges(lefts, vector<int>(rights, NONE)) {
    }

    void insert_edge(int left, int right) {
        edges[left][right] = WHITE;
    }

    bool augment_left(int left, int color) {
        for(int right = 0; right < rights; right++) {
            if (edges[left][right] == WHITE && !visited[right]) {
                visited[right] = true;
                int matching = right_colors[right][color];
                if (matching == UNMATCHED || augment_left(matching, color)) {
                    edges[left][right] = color;
                    if (left_colors[left][color] == UNMATCHED)
                        left_degrees[left]--;
                    if (right_colors[right][color] == UNMATCHED)
                        right_degrees[right]--;
                    left_colors[left][color] = right;
                    right_colors[right][color] = left;
                    if (matching != UNMATCHED)
                        edges[matching][right] = WHITE;
                    return true;
                }
            }
        }
        return false;
    }

    bool augment_right(int right, int color) {
        for(int left = 0; left < lefts; left++) {
            if (edges[left][right] == WHITE && !visited[left]) {
                visited[left] = true;
                int matching = left_colors[left][color];
                if (matching == UNMATCHED || augment_right(matching, color)) {
                    edges[left][right] = color;
                    if (right_colors[right][color] == UNMATCHED)
                        right_degrees[right]--;
                    if (left_colors[left][color] == UNMATCHED)
                        left_degrees[left]--;
                    right_colors[right][color] = left;
                    left_colors[left][color] = right;
                    if (matching != UNMATCHED)
                        edges[left][matching] = WHITE;
                    return true;
                }
            }
        }
        return false;
    }

    void print() {
        for(int i = 0; i < lefts; i++) {
            for(int j = 0; j < rights; j++) {
                int color = edges[i][j];
                if (color == NONE)
                    printf("0");
                else if (color == WHITE)
                    printf("?");
                else
                    printf("%d", color+1);
                printf((j < rights-1 ? " " : "\n"));
            }
        }
        /*
        for(int i = 0; i < lefts; i++) {
            printf("L%d(%d):", i, left_degrees[i]);
            for(int j = 0; j < max(lefts, rights); j++) {
                printf(" %2d", left_colors[i][j]);
            }
            printf("\n");
        }
        for(int i = 0; i < rights; i++) {
            printf("R%d(%d):", i, right_degrees[i]);
            for(int j = 0; j < max(lefts, rights); j++) {
                printf(" %2d", right_colors[i][j]);
            }
            printf("\n");
        }
        printf("--------------------------------\n");
        */
    }

    int paint_edges() {

        left_degrees.assign(lefts, 0);
        right_degrees.assign(rights, 0);

        for(int i = 0; i < lefts; i++) {
            int degree = 0;
            for(int j = 0; j < rights; j++) {
                if (edges[i][j] != NONE)
                    degree++;
            }
            left_degrees[i] = degree;
        }
        for(int j = 0; j < rights; j++) {
            int degree = 0;
            for(int i = 0; i < lefts; i++) {
                if (edges[i][j] != NONE)
                    degree++;
            }
            right_degrees[j] = degree;
        }

        int colors = max(*max_element(left_degrees.begin(), left_degrees.end()),
                         *max_element(right_degrees.begin(), right_degrees.end()));

        left_colors.assign(lefts, vector<int>(colors, UNMATCHED));
        right_colors.assign(rights, vector<int>(colors, UNMATCHED));

        /*
        printf("startup:\n");
        print();
        */

        for(int color = 0; color < colors; color++) {
            for(int i = 0; i < lefts; i++) {
                visited.assign(rights, false);
                augment_left(i, color);
            }
            for(int i = 0; i < rights; i++) {
                visited.assign(lefts, false);
                augment_right(i, color);
            }
            /*
            int degree = colors - color;
            for(int i = 0; i < lefts; i++) {
                if (left_degrees[i] == degree) {
                    //printf("L%d augment:\n", i);
                    visited.assign(rights, false);
                    bool b = augment_left(i, color);
                    //print();
                    assert(b);
                }
            }
            for(int i = 0; i < rights; i++) {
                if (right_degrees[i] == degree) {
                    //printf("R%d augment:\n", i);
                    visited.assign(lefts, false);
                    bool b = augment_right(i, color);
                    //print();
                    assert(b);
                }
            }
            */
        }

        for(int i = 0; i < lefts; i++) {
            for(int j = 0; j < rights; j++) {
                assert(edges[i][j] != WHITE);
            }
        }

        return colors;
    }
};



int main() {
    int nCases;
    scanf("%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {
        int n;
        scanf("%d", &n);
        BipartiteGraph g(n, n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                char c;
                scanf(" %c", &c);
                if (c == '*')
                    g.insert_edge(i, j);
            }
        }
        int colors = g.paint_edges();
        printf("%d\n", colors);
        g.print();
    }
    return 0;
}

