#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Edge {
  int id;
  int dest;
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

int main(void)
{
  int nEdges, nNodes;
  cin >> nEdges >> nNodes;

  Graph g(nNodes);
  REP(i, nEdges) {
    int from, to;
    cin >> from >> to;
    from --;
    to --;

    Edge edge;
    edge.id = i;
    edge.dest = to;

    g[from].push_back(edge);
  }

  vector< pair<int, int> > trace(nNodes, make_pair(-1, -1));
  queue<int> q;
  q.push(0);
  trace[0] = make_pair(0, -1);
  while(!q.empty()) {
    int node = q.front();
    q.pop();

    REP(i, g[node].size()) {
      int nextNode = g[node][i].dest;
      if (trace[nextNode].first == -1) {
        trace[nextNode] = make_pair(node, g[node][i].id);
        q.push(nextNode);
      }
    }
  }

  vector<int> ret;
  int endNode = nNodes - 1;
  ret.push_back(endNode);
  if (trace[endNode].first == -1) {
    cout << -1 << endl;
  } else {
    while (endNode != 0) {
      int prevNode = trace[endNode].first;
      int prevEdgeId = trace[endNode].second;
      ret.push_back(prevNode);
      endNode = prevNode;
    }

    reverse(ret.begin(), ret.end());

    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++)
      cout << ret[i] + 1 << endl;
  }
  return 0;
}
