#ifndef __GPLOT__
#define __GPLOT__

#include <fstream>
#include <string>
#include "vertex.h"
#include "edge.h"

class Gplot
{
public:
    Gplot();
    ~Gplot();
    int gp_add(Edge *e);           // add new branch into Gplot::dotfile 
    std::string gp_dump(bool flag);// if true, using digraph; otherwise using normal graph
    int gp_export(std::string filename);
private:
    std::string dotfile;
    std::string style;
    std::string body;
};

#endif