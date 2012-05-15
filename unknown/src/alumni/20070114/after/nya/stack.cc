#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <iterator>

using namespace std;

ifstream fin("b.in");
#define cin fin

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef set<int> Tree;

map<Tree, int> treeids;

int getid(const Tree& tree) {
    if (treeids.count(tree) == 0)
        treeids.insert(make_pair(tree, treeids.size()));
    return treeids[tree];
}

int main() {
    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        int nOpers;
        cin >> nOpers;
        vector<Tree> stack;
        REP(iOper, nOpers) {
            string oper;
            cin >> oper;
            if (oper == "PUSH") {
                stack.push_back(Tree());
            }
            else if (oper == "DUP") {
                Tree top = stack.back();
                stack.push_back(top);
            }
            else if (oper == "ADD") {
                Tree top = stack.back(); stack.pop_back();
                stack.back().insert(getid(top));
            }
            else if (oper == "UNION") {
                Tree a = stack.back(); stack.pop_back();
                Tree b = stack.back(); stack.pop_back();
                Tree tree;
                set_union(ALLOF(a), ALLOF(b), insert_iterator<Tree>(tree, tree.end()));
                stack.push_back(tree);
            }
            else if (oper == "INTERSECT") {
                Tree a = stack.back(); stack.pop_back();
                Tree b = stack.back(); stack.pop_back();
                Tree tree;
                set_intersection(ALLOF(a), ALLOF(b), insert_iterator<Tree>(tree, tree.end()));
                stack.push_back(tree);
            }
            else {
                assert(false);
            }
            cout << stack.back().size() << endl;
        }
        cout << "***" << endl;
    }
    return 0;
}
