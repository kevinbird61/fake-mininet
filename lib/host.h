#ifndef __HOST__
#define __HOST__

#include "vertex.h"

class Host: public Vertex
{
public:
    Host();
    Host(Host *h);
    Host(char *name);
    Host(std::string name);
    ~Host();
    void set_name(std::string name);
    std::string get_name();
};

#endif