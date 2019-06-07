#ifndef __NETWORK_MANAGER__
#define __NETWORK_MANAGER__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "vertex.h"
#include "switch.h"
#include "host.h"
#include "edge.h"
#include "hash.h"

class NetworkManager
{
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
    void connect_with_val(std::string hname, std::string tname, int cap, int flowval);
    void connect_r(std::string hname, std::string tname); // also add reverse connection
    void disconnect(std::string hname, std::string tname);
    int connected(std::string hname, std::string tname);
    int connected_d(std::string hname, std::string tname); // directed
    // setlink
    void setlink(std::string hname, std::string tname, int mode, int val);
    // switch/host name (auto increment)
    std::string get_sw_name();
    std::string get_h_name();
    // clear
    void clear();

    // For API
    int interpret(std::string filename); // read topology file 
    int add_switch(std::string name);
    int add_switch();   // using get_sw_name method
    Switch *create_switch();
    Switch *create_switch(std::string name);
    int add_host(std::string name);
    int add_host();
    Host *create_host();
    Host *create_host(std::string name);
    void linkup(Vertex *head, Vertex *tail);
    void linkdown(Vertex *head, Vertex *tail);
    Vertex *get_all_nodes();
    Vertex *get_node(std::string name);
    Edge *get_edge(Vertex *head, Vertex *tail);
    Edge *get_edge(std::string hname, std::string tname);

    // member
    Vertex **vlist;
    Edge *elist;
    int tablesize;
    int switch_num;
    int host_num;

private: 
    std::vector<std::string> readline(std::string raw);
    int execute(std::vector<std::string> args);
};

#endif