#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){
    // build basic topo
    nm->add_switch("a");
    nm->add_switch("d");
    nm->add_host("b");
    nm->add_host("c");
    
    nm->add_switch("e");
    nm->add_switch("h");
    nm->add_host("g");
    nm->add_host("f");

    nm->connect("a", "e");
    nm->connect("a", "h");
    nm->connect("b", "a");
    nm->connect("b", "c");
    nm->connect("b", "d");
    nm->connect("d", "b");
    nm->connect("d", "c");
    nm->connect("d", "h");

    nm->connect("e", "f");
    nm->connect("e", "h");
    nm->connect("g", "e");
    nm->connect("f", "g");
    nm->connect("h", "g");

    // using gplot to export a dot file, and then using graphviz to generate the figure
    Gplot *gp = new Gplot();
    gp->gp_add(nm->elist);
    gp->gp_dump(true);
    gp->gp_export("plot");

    return 0;
}