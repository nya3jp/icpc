#include <vector>
#include <limits>
#include <cstdio>

using namespace std;

struct UnionFind {
    struct Node {
        int left, right;
        vector<int> v;
        Node* next;
        Node* last;
        Node() : left(-1), right(-1), v(), next(0), last(0) {
            last = this;
        }
    };
    vector<int> roots;
    vector<Node*> nodes;
    const int n;

    UnionFind(int n) : roots(n, -1), nodes(n, (Node*)0), n(n) {
    }
    ~UnionFind() {
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        for(int i = 0; i < (int)nodes.size(); i++) {
            if (nodes[i])
                delete nodes[i];
        }
    }
    void put(int a, int k) {
        int root = find_root(a);
        if (!nodes[root]) {
            Node* node = nodes[root] = new Node();
            node->left = node->right = a;
            node.v.push_back(k);
        }
        else {
            Node* node = nodes[root];
            link(root, node.right+1);
            root = find_root(root);
            nodes[root] = node;
            node.right++;
            node.v.push_back(k);
        }
        int next_root = find_root(nodes[root]->right+1);
        if (nodes[next_root]) {
            
            nodes[root]->last->next = nodes[next_root];
            nodes[root]->last = nodes[next_root]->last;
            Node* node = nodes[root];
            link(root, next_root);
            nodes[root] = node;
        }
    }
    void serialize(vector<int>& v) {
        for(int i = 0; i < n; i++) {
            
        }
    }
    
    bool link(int a, int b) {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra != rb) {
            if (roots[rb] < roots[ra])
                swap(ra, rb);
            roots[ra] += roots[rb];
            roots[rb] = ra;
        }
        return (ra != rb);
    }
    bool check(int a, int b) {
        return (find_root(a) == find_root(b));
    }

    int find_root(int a) {
        return ((roots[a] < 0) ? a : (roots[a] = find_root(roots[a])));
    }
};


int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    UnionFind uf(m+2);
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    vector<int> u(m+2+n+3, 0);
    int upper = 0;
    for(int i = n-1; i >= 0; i--) {
        int pos = uf.put(v[i]);
        printf("%d -> %d\n", i+1, pos);
        u[pos] = i+1;
        upper = max(upper, pos);
    }
    printf("%d\n%d", upper, u[1]);
    for(int i = 2; i <= upper; i++) {
        printf(" %d", u[i]);
    }
    printf("\n");
    return 0;
}

