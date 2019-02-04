#ifndef __FAKE_SHELL__
#define __FAKE_SHELL__

#include "network_manager.h"
#include "switch.h"
#include "host.h"
#include "edge.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// methods
int sh_loop();
vector<string> sh_readline();
int sh_execute(vector<string> args);

// log, helper function
void print_help();

#endif