#include <iostream>
#include <unistd.h>
#include "network_manager.h"
#include "path.h"

int main(int argc, char** argv){
    // create NetworkManager first
    NetworkManager *nm;
    nm=new NetworkManager();

    // build basic topo
    nm->add_host(std::string("s"));
    nm->add_host(std::string("t"));
    nm->add_switch(std::string("u"));
    nm->add_switch(std::string("v"));
    nm->add_switch(std::string("x"));
    nm->add_switch(std::string("y"));
    nm->connect(std::string("s"), std::string("u"));
    nm->connect(std::string("s"), std::string("x"));
    nm->connect(std::string("u"), std::string("v"));
    nm->connect(std::string("v"), std::string("x"));
    nm->connect(std::string("v"), std::string("t"));
    nm->connect(std::string("x"), std::string("y"));
    nm->connect(std::string("y"), std::string("t"));
    // get the edge info by 2 vertices
    Edge *e = nm->get_edge(std::string("s"), std::string("u"));
    std::cout << "Edge `s<->u`=> [cap:" << e->cap << ", val:" << e->flowval << "]" << std::endl;
    // print current status
    nm->print_all_e();

    // create path
    Path *path;
    path=new Path();
    // create tree from edge list
    path->append(nm->elist);
    // find paths (will return std::vector<std::vector<Node *>> object)
    path->find_paths(std::string("s"), std::string("t"));
    // debug (show the paths found between 2 vertices that user specified)
    path->debug();

    return 0;
}