#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

struct Node {
    int order;
    int heap;
    int id;
    int parent, left, right;
};
bool byOrder(const Node& a, const Node& b) {
    return (a.order < b.order);
}
bool byID(const Node& a, const Node& b) {
    return (a.id < b.id);
}

std::vector<Node> v;
int root, right;

bool form_tree(int left, int heapLimit) {
    int n = v.size();

    if (v[left].heap < heapLimit) {
        root = right = left-1;
        return false;
    }

    int parent;
    if (left+1 < n && v[left].heap < v[left+1].heap) {
        form_tree(left+1, v[left].heap);
        v[root].parent = v[left].id;
        v[left].right = v[root].id;
        parent = right+1;
    }
    else {
        parent = left+1;
    }

    if (parent == n) {
        root = left;
        right = n-1;
    }
    else {
        if (v[parent].heap < v[left].heap && form_tree(parent, heapLimit)) {
            v[left].parent = v[parent].id;
            v[parent].left = v[left].id;
        }
        else {
            root = left;
            right = parent-1;
        }
    }

    return true;
}

int main() {

    int n;
    std::cin >> n;

    v.resize(n);
    REP(i, n) {
        Node& x = v[i];
        std::cin >> x.order >> x.heap;
        x.id = i;
        x.parent = x.left = x.right = -1;
    }

    std::sort(ALLOF(v), byOrder);

    form_tree(0, -100000);

    bool result = (right == n-1);

    std::cout << (result ? "YES" : "NO") << std::endl;
    if (result) {
        std::sort(ALLOF(v), byID);
        REP(i, n) {
            Node& x = v[i];
            std::cout << x.parent+1 << " " << x.left+1 << " " << x.right+1 << std::endl;
        }
    }
    

    return 0;
}
