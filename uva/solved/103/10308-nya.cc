/*
 * UVA 10308 Roads in the North
 * 2005-07-06
 * by nya
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <algorithm>

typedef std::vector< std::list< std::pair<int, int> > > adjacent_list;

typedef std::vector< std::map<int, int> > memory;

int calc_height(const adjacent_list& adj, int parent, int root, int d, memory& m) {
    std::map<int, int>::const_iterator it = m[parent].find(root);
    if (it != m[parent].end())
        return it->second;

    int& h = m[parent][root];
    h = d;
    for(std::list< std::pair<int, int> >::const_iterator it = adj[root].begin();
            it != adj[root].end(); ++it) {
        if (it->first != parent) {
            h = std::max(h, d + calc_height(adj, root, it->first, it->second, m));
        }
    }

    //std::fprintf(stderr, "calc_height(%d, %d) = %d\n", parent, root, h);

    return h;
}

int solve(const adjacent_list& adj) {

    memory m;
    m.resize(adj.size());

    int max_height = 0;

    for(int i=0; i<adj.size(); i++) {
        for(std::list< std::pair<int, int> >::const_iterator it = adj[i].begin();
                it != adj[i].end(); ++it) {
            int j = it->first;
            int h = calc_height(adj, i, j, it->second, m);
            max_height = std::max(max_height, h);
        }
    }

    //std::fprintf(stderr, "solve() finished\n");

    return max_height;
}


int main() {

    while(!std::feof(stdin)) {

        adjacent_list adj;

        while(true) {
            char buf[1024];
            buf[0] = '\0';
            std::fgets(buf, sizeof(buf), stdin);

            int a, b, d;
            int r = std::sscanf(buf, "%d%d%d", &a, &b, &d);
            if (r != 3)
                break;

            a--; b--;
            if (adj.size() <= std::max(a, b)) {
                adj.resize(std::max(a, b)+1);
            }

            adj[a].push_back(std::make_pair(b, d));
            adj[b].push_back(std::make_pair(a, d));
        }

        //std::fprintf(stderr, "Input finished\n");

        std::printf("%d\n", solve(adj));

    }

    return 0;
}
