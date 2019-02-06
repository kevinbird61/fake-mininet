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
    // between 2 vertex 
    void connect(std::string hname, std::string tname);
    void disconnect(std::string hname, std::string tname);
    int connected(std::string hname, std::string tname);
    // setlink 
    void setlink(std::string hname, std::string tname, int mode, unsigned int val);
    // switch/host name (auto increment)
    std::string get_sw_name();
    std::string get_h_name();
    // member 
    Vertex **vlist;
    Edge *elist;
    int tablesize;
    int switch_num;
    int host_num;
};

#endif 