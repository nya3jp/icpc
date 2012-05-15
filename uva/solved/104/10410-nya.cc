/*
 * UVA 10410 Tree Reconstruction
 * 2005-08-08
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>

struct tree {
    int id;
    tree* parent;
    std::vector<tree*> children;

    tree(int id, tree* parent) : id(id), parent(parent) {
    }
    ~tree() {
    }
    void destroy() {
        for(int i=0; i<(int)children.size(); i++) {
            children[i]->destroy();
        }
        delete this;
    }
};

void traverse_tree(tree* pos, std::vector< std::vector<int> >& children) {
    std::vector<int>& v = children[pos->id];
    for(int i=0; i<(int)pos->children.size(); i++) {
        tree* child = pos->children[i];
        traverse_tree(child, children);
        v.push_back( child->id );
    }
    std::sort(v.begin(), v.end());
}

int main() {
    int n;
    while(std::cin >> n) {
        std::vector<int> bfs(n);
        std::vector<int> dfs(n);
        for(int i=0; i<n; i++) {
            std::cin >> bfs[i];
            bfs[i]--;
        }
        for(int i=0; i<n; i++) {
            std::cin >> dfs[i];
            dfs[i]--;
        }
        std::vector<int> bfsmap(n);
        for(int i=0; i<n; i++) {
            bfsmap[bfs[i]] = i;
        }
        tree* root = new tree(dfs[0], 0);
        tree* pos = root;
        //std::cerr << (dfs[0]+1) << std::endl;
        for(int i=1; i<n; i++) {
            int id = dfs[i];
            if (i != 1 && bfsmap[id] == bfsmap[pos->id]+1) {
                pos = pos->parent;
            }
            else if (bfsmap[id] < bfsmap[pos->id]) {
                while(!(bfsmap[pos->id] < bfsmap[id])) {
                    pos = pos->parent;
                    //std::cerr << "-> ";
                }
                pos = pos->parent;
            }
            //std::cerr << (id+1) << std::endl;
            tree* child = new tree(id, pos);
            pos->children.push_back(child);
            pos = child;
        }
        std::vector< std::vector<int> > children(n);
        traverse_tree(root, children);
        root->destroy();

        for(int i=0; i<n; i++) {
            const std::vector<int>& v = children[i];
            std::cout << (i+1) << ':';
            for(int j=0; j<(int)v.size(); j++) {
                std::cout << ' ' << (v[j]+1);
            }
            std::cout << std::endl;
        }
        //std::cout << std::endl;
    }
    return 0;
}
