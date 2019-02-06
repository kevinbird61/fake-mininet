#ifndef __EDGE__
#define __EDGE__

#include "vertex.h"

class Edge {
public:
    Edge();
    ~Edge();
    void link(Vertex *head, Vertex *tail);
    void set_cap(unsigned int cap);
    void set_flowval(unsigned int flowval);
    Vertex *head;
    Vertex *tail;
    unsigned int cap; // capacity of link (default: 2)
    unsigned int flowval; // flow value of link (default: 1)
    Edge *next;
};

#endif