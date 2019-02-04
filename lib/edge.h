#ifndef __EDGE__
#define __EDGE__

#include "vertex.h"

class Edge {
public:
    Edge();
    ~Edge();
    void link(Vertex *head, Vertex *tail);
    Vertex *head;
    Vertex *tail;
    Edge *next;
};

#endif