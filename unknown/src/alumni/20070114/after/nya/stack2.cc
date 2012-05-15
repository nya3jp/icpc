#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <iterator>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef vector<int> Tree;

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
        stack.reserve(2000);
        REP(iOper, nOpers) {
            string oper;
            cin >> oper;
            if (oper == "PUSH") {
                stack.push_back(Tree());
            }
            else if (oper == "DUP") {
                stack.push_back(stack.back());
            }
            else if (oper == "ADD") {
                int id = getid(stack.back());
                stack.pop_back();
                if (!binary_search(ALLOF(stack.back()), id))
                    stack.back().insert(lower_bound(ALLOF(stack.back()), id), id);
            }
            else if (oper == "UNION") {
                Tree& a = stack[stack.size()-2];
                Tree& b = stack[stack.size()-1];
                Tree tree;
                tree.reserve(a.size()+b.size());
                set_union(ALLOF(a), ALLOF(b), back_inserter(tree));
                stack.pop_back();
                stack.pop_back();
                stack.push_back(tree);
            }
            else if (oper == "INTERSECT") {
                Tree& a = stack[stack.size()-2];
                Tree& b = stack[stack.size()-1];
                Tree tree;
                tree.reserve(a.size()+b.size());
                set_intersection(ALLOF(a), ALLOF(b), back_inserter(tree));
                stack.pop_back();
                stack.pop_back();
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
