#include "edge.h"

Edge::Edge()
    :cap(2),flowval(1)
{
    this->next = NULL;
}

Edge::Edge(Edge *e)
{
    this->cap=e->cap;
    this->flowval=e->flowval;
    this->next=NULL;
    this->head=e->head;
    this->tail=e->tail;
}

Edge::~Edge() {}

void Edge::link(Vertex *head, Vertex *tail)
{
    this->head = head;
    this->tail = tail;
}