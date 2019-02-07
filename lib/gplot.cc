#include "gplot.h"

Gplot::Gplot()
{
    this->style =
        std::string("rankdir=LR;\n")+
        std::string("node [shape=record];\n")
        ;
}

Gplot::~Gplot()
{}

int Gplot::gp_add(Edge *elist)
{
    // reset (Is this a good choice?)
    this->body="";
    // construct
    Edge *trav = elist;
    while(trav!=NULL) {
        // add the node into this->body
        this->body += (trav->head->name)+" [label=\""+ trav->head->name + "(" + trav->head->type + ")\"];\n";
        this->body += (trav->tail->name)+" [label=\""+ trav->tail->name + "(" + trav->tail->type + ")\"];\n";
        this->body += (trav->head->name + "->" + trav->tail->name + "[label=\"(" + std::to_string(trav->flowval) + ") " + std::to_string(trav->cap) + "\"];\n");
        trav=trav->next;
    }
}

std::string Gplot::gp_dump(bool flag)
{
    // reset
    this->dotfile="";
    // then concate again
    if(flag==true) {
        // dia
        this->dotfile = "digraph G{\n" + this->style + "\n" + this->body + "\n}";
    } else {
        // graph
        this->dotfile = "graph G{\n" + this->style + "\n" + this->body + "\n}";
    }

    return this->dotfile;
}

int Gplot::gp_export(std::string filename)
{
    std::ofstream fout;
    fout.open (filename+".dot");
    fout << this->dotfile;
    fout.close();

    return 0;
}