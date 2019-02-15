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
    // set the capacity & flowvalue of the link
    nm->setlink(std::string("s"), std::string("x"), 1, 0);
    nm->setlink(std::string("u"), std::string("v"), 0, 1);
    nm->setlink(std::string("v"), std::string("x"), 0, 1);
    nm->setlink(std::string("x"), std::string("y"), 0, 1);
    nm->setlink(std::string("v"), std::string("t"), 1, 0);
    // print current status
    nm->print_all_e();

    // create path
    Path *path;
    path=new Path();
    // create tree from edge list
    path->append(nm->elist);
    // find paths (will return std::vector<std::vector<Node *>> object)
    std::vector<std::vector<Edge *>> avail_paths = path->find_paths(std::string("s"), std::string("t"));
    // debug (show the paths found between 2 vertices that user specified)
    path->debug();

    // get shortest
    int MIN=~0;
    for(int i=0;i<avail_paths.size();i++){
        if(avail_paths.at(i).size()<MIN){MIN=avail_paths.at(i).size();}
    }

    // find feasible flow
    for(int i=0;i<avail_paths.size();i++){
        int weight=0;
        if(avail_paths.at(i).size()==MIN){
            std::cout << "Path: ";
            for(int x=0;x<avail_paths.at(i).size();x++){
                // inc 
                if(x+1<avail_paths.at(i).size())
                    weight += nm->get_edge(avail_paths.at(i).at(x)->head->name, avail_paths.at(i).at(x)->tail->name)->flowval;
                std::cout << avail_paths.at(i).at(x)->head->name << " ";
            }
            std::cout << "\n";
            std::cout << "Capacity of current flow: " << weight << std::endl;
        }
    }

    // 

    return 0;
}