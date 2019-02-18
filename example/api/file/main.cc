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

    return 0;
}