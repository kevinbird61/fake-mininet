#include "edge.h"

Edge::Edge()
    :cap(2),flowval(0)
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

void Edge::reverse()
{
    Vertex *tmp = this->tail;
    this->tail = this->head;
    this->head = tmp;
}

void Edge::link(Vertex *head, Vertex *tail)
{
    this->head = head;
    this->tail = tail;
}

void Edge::set_cap(int cap)
{
    this->cap = cap;
}

void Edge::set_flowval(int flowval)
{
    // normalize
    if(flowval > this->cap){
        this->cap = flowval;
    }
    this->flowval = flowval;
}