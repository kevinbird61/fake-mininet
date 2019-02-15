#ifndef __PATH__
#define __PATH__

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include "vertex.h"
#include "edge.h"
#include "hash.h"

// construct tree structure
class Path {
public:
    Path();
    ~Path();
    void append(Edge *elist); // construct tree from edge list
    std::vector<std::vector<Edge *>> find_paths(std::string src, std::string sink);
    int trav(std::string prev, std::string end, std::vector<Vertex *> existed_vertices);

    // debug
    void debug();

    std::map<std::string, std::vector<Edge *>> tree;  // multiple branch tree structure
    std::vector<Edge *> path;
    // std::vector<Vertex *> existed_vertices;
    std::vector<std::vector<Edge *>> paths;  // maintain several root of paths
    int tablesize;
};

#endif 