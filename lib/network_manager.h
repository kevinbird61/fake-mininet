#ifndef __NETWORK_MANAGER__
#define __NETWORK_MANAGER__

#include <iostream>

#include "vertex.h"
#include "edge.h"
#include "hash.h"

class NetworkManager {
public:
    NetworkManager();
    NetworkManager(int tablesize);
    ~NetworkManager();
    int add_vertex(Vertex *v);
    void add_edge(Edge *e);
    // print 
    void print_all_v(); // all vertices
    void print_all_e(); // all edges
    // link 2 vertex 
    void connect(std::string hname, std::string tname);
    void disconnect(std::string hname, std::string tname);
    int check_status(std::string hname, std::string tname);
    // member 
    Vertex **vlist;
    Edge *elist;
    int tablesize;
};

#endif 