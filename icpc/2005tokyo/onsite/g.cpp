#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <iterator>

typedef std::vector< std::list<int> > Graph;

template<class T>
struct matrix {
  T* data;
  const int n, m;
  matrix(int n, int m, const T& def = T())
    : data(new T[n*m]), n(n), m(m) {
  }
  virtual ~matrix() {
    delete[] data;
  }
  T* operator[](int i) {
    return data+(i*m);
  }
  const T* operator[](int i) const {
    return data+(i*m);
  }
private:
  matrix(const matrix<T>&) {
  }
  matrix<T>& operator=(const matrix<T>&) {
    return 0;
  }
};

void print(const Graph& g) {
  return;
  std::cerr << "Graph (" << (int)g.size() << "):" << std::endl;
  for(int i=0; i<(int)g.size(); i++) {
    std::copy(g[i].begin(), g[i].end(), std::ostream_iterator<int>(std::cerr, " "));
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
}

void fill_hops_sub(int iNode, int currentHops, const Graph& g, std::vector<int>& hops, const std::vector<int>& nodes, std::vector<bool>& visited) {
  if (!visited[iNode]) {
    visited[iNode] = true;
    //if (std::find(nodes.begin(), nodes.end(), iNode) == nodes.end()) {
      //int iPC = std::find(nodes.begin(), nodes.end(), iNode) - nodes.begin();
      /*
      if (hops[iPC] < 0 || hops[iPC] == currentHops) {
	hops[iPC] = currentHops;
      }
      else {
	hops[iPC] = 0;
      }
      */
      if (hops[iNode] < 0 || hops[iNode] == currentHops) {
	hops[iNode] = currentHops;
      }
      else {
	hops[iNode] = 0;
      }
      //}
    for(Graph::value_type::const_iterator it = g[iNode].begin(); it != g[iNode].end(); ++it) {
      //std::cerr << iNode << " to " << *it << std::endl;
      fill_hops_sub(*it, currentHops-1, g, hops, nodes, visited);
    }
  }
}


void fill_hops(const Graph& g, std::vector<int>& hops, const std::vector<int>& nodes, const int* chops) {
  int n = nodes.size();
  int m = g.size();
  for(int i=0; i<n; i++) {
    std::vector<bool> visited(m, false);
    //std::cerr << "fill_hops_sub(" << nodes[i] << "," << chops[i] << std::endl;
    fill_hops_sub(nodes[i], chops[i], g, hops, nodes, visited);
  }
}


int main() {
  std::ifstream fin("G.txt");

  int n;
  while(fin >> n && n != 0) {

    Graph g;
    std::vector<int> nodes;
    matrix<int> adj(n, n);
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
	fin >> adj[i][j];

    g.resize(1);
    nodes.push_back(0);

    for(int iAdd=1; iAdd<n; iAdd++) {
      //std::cerr << "adding " << iAdd << std::endl;
      int m = g.size();
      std::vector<int> hops(m, -1);
      fill_hops(g, hops, nodes, adj[iAdd]);
      //std::cerr << "hops: ";
      //std::copy(hops.begin(), hops.end(), std::ostream_iterator<int>(std::cerr, " "));
      //std::cerr << std::endl;
      int iConnect = -1;
      for(int i=0; i<m; i++) {
	if (hops[i] > 0) {
	  if (iConnect < 0) {
	    iConnect = i;
	    break;
	  }
	  else {
	    iConnect = -1;
	    break;
	  }
	}
      }
      assert(iConnect >= 0);
      int nMiddles = hops[iConnect]-1;
      g.resize(m+nMiddles+1);
      g[iConnect].push_back(m);
      g[m].push_back(iConnect);
      for(int i=0; i<nMiddles; i++) {
	g[m+i].push_back(m+i+1);
	g[m+i+1].push_back(m+i);
      }
      nodes.push_back(m+nMiddles);
      print(g);
    }

    std::multiset<int> ms;
    for(int i=0; i<(int)g.size(); i++) {
      if (std::find(nodes.begin(), nodes.end(), i) == nodes.end()) {
	ms.insert( (int)g[i].size() );
      }
    }

    for(std::multiset<int>::const_iterator it = ms.begin(); it != ms.end(); ++it) {
      if (it != ms.begin())
	std::cout << ' ';
      std::cout << *it;
    }
    std::cout << std::endl;

  }

  return 0;
}

