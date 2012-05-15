#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cmath>

using namespace std;

ifstream fin("c.in");
#define cin fin

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

const double PI = acos(0.0) * 2;

struct Node {
    double value;
    int divide;
};

bool operator<(const Node& a, const Node& b) {
    return (a.value/a.divide < b.value/b.divide);
}

int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int n, f;
        cin >> n >> f;

        priority_queue<Node> q;
        REP(i, n) {
            int x;
            cin >> x;
            q.push((Node){PI*x*x, 1});
        }

        REP(i, f) {
            Node node = q.top();
            q.pop();
            node.divide++;
            q.push(node);
        }

        Node node = q.top();
        printf("%.10f\n", node.value/node.divide);
    }
    return 0;
}


