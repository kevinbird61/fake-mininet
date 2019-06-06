#include <iostream>
#include <unistd.h>
#include "network_manager.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    // read from file
    nm->interpret("file/topo.txt");
    nm->print_all_e();

    nm->connect("a", "c");
    nm->connect("d", "e");

    nm->print_all_e();

    nm->disconnect("a", "b");
    nm->print_all_e();
    nm->disconnect("a", "c");
    nm->print_all_e();
    nm->disconnect("b", "c");
    nm->print_all_e();
    nm->disconnect("c", "d");
    nm->print_all_e();
    nm->disconnect("d", "e");
    nm->print_all_e();

    return 0;
}
