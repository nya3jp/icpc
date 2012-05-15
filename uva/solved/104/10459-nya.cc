/*
 * UVA 10459 The Tree Root
 * 2005-05-21
 * by nya
 */

#define NDEBUG

#include <iostream>
#include <algorithm>
#include <utility>
#include <map>

typedef std::map<int,int> Edges;
typedef std::map<int,Edges> Tree;


int calc_height(int iFrom, int iNode, Tree& tree) {

    int& height = tree[iFrom][iNode];
    if (height >= 0)
        return height;

    height = 1;

    Edges& edges = tree[iNode];
    for(Edges::iterator it = edges.begin(); it != edges.end(); ++it) {
        int jNode = it->first;
        if (jNode == iFrom)
            continue;
        height = std::max(height, calc_height(iNode, jNode, tree)+1);
    }

    return height;
}


void calc_height(Tree& tree) {
    for(Tree::iterator it = tree.begin(); it != tree.end(); ++it) {
        int iNode = it->first;
        Edges& edges = it->second;
        for(Edges::iterator jt = edges.begin(); jt != edges.end(); ++jt) {
            int jNode = jt->first;
            int& height = jt->second;
            if (height < 0) {
                height = calc_height(iNode, jNode, tree);
            }
        }
    }
}

void debug_show_height(Tree& tree) {
#ifndef NDEBUG
    for(Tree::iterator it = tree.begin(); it != tree.end(); ++it) {
        int iNode = it->first;
        Edges& edges = it->second;
        for(Edges::iterator jt = edges.begin(); jt != edges.end(); ++jt) {
            int jNode = jt->first;
            int height = jt->second;
            std::cout << "(" << iNode << "," << jNode << ") = " << height << std::endl;
        }
    }
#endif
}


    
    

int main() {

    while(true) {
        int nNodes;

        std::cin >> nNodes;
        if (! std::cin)
            break;

        Tree tree;

        for(int iNode=0; iNode<nNodes; iNode++) {
            int nEdges;
            std::cin >> nEdges;
            for(int iEdge=0; iEdge<nEdges; iEdge++) {
                int jNode;
                std::cin >> jNode;
                jNode--;
                tree[iNode][jNode] = -1;
                tree[jNode][iNode] = -1;
            }
        }

        calc_height(tree);

        debug_show_height(tree);

        std::map<int,int> heights;
        int min_height = nNodes;
        int max_height = 0;
        for(int iNode=0; iNode<nNodes; iNode++) {
            int& height = heights[iNode];
            Edges& edges = tree[iNode];
            heights[iNode] = 0;
            for(Edges::iterator it = edges.begin(); it != edges.end(); ++it) {
                height = std::max(height, it->second);
            }
            min_height = std::min(min_height, height);
            max_height = std::max(max_height, height);
        }

        std::cout << "Best Roots  :";
        for(int iNode=0; iNode<nNodes; iNode++) {
            if (heights[iNode] == min_height)
                std::cout << ' ' << (iNode+1);
        }
        std::cout << std::endl;


        std::cout << "Worst Roots :";
        for(int iNode=0; iNode<nNodes; iNode++) {
            if (heights[iNode] == max_height)
                std::cout << ' ' << (iNode+1);
        }
        std::cout << std::endl;
    }

    return 0;
}
