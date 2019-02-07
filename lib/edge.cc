#include "edge.h"

Edge::Edge()
    :cap(2),flowval(1)
{
    this->next = NULL;
}

Edge::~Edge() {}

void Edge::link(Vertex *head, Vertex *tail)
{
    this->head = head;
    this->tail = tail;
}