#ifndef __VERTEX__
#define __VERTEX__

#include <string>

class Vertex
{
public:
    std::string name;
    std::string type;
    Vertex *next;
};

#endif