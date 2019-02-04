#include "edge.h"

Edge::Edge(){
    this->next = NULL;
}

Edge::~Edge(){}

void Edge::link(Vertex *head, Vertex *tail){
    this->head = head;
    this->tail = tail;
}