#ifndef __EDGE__
#define __EDGE__

#include "vertex.h"

class Edge
{
public:
    Edge();
    Edge(Edge *e);
    ~Edge();
    void link(Vertex *head, Vertex *tail);
    void reverse();
    void set_cap(int cap);
    void set_flowval(int flowval);
    Vertex *head;
    Vertex *tail;
    int cap; // capacity of link (default: 2)
    int flowval; // flow value of link
    std::string tag; // user-defined tag
    Edge *next;
};

#endif