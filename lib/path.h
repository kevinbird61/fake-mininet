#ifndef __PATH__
#define __PATH__

#include <iostream>
#include <vector>
#include <map>
#include "vertex.h"
#include "edge.h"
#include "hash.h"

// node
class Node: public Vertex {
public:
    Node(){};
    Node(Vertex *v){
        this->name=v->name;
        this->type=v->type;
        this->next=NULL;
    };
    std::map<std::string, Node *> br; // multiple branch to other node
};

// construct tree structure
class Path {
public:
    Path();
    ~Path();
    void append(Edge *elist); // construct tree from edge list
    std::vector<std::vector<Node *>> find_paths(std::string src, std::string sink);
    int trav(std::string prev, std::string end);

    // debug
    void debug();

    std::map<std::string, Node *> tree;  // multiple branch tree structure
    std::vector<Node *> path;
    std::vector<std::vector<Node *>> paths;  // maintain several root of paths
    int tablesize;
};

#endif 