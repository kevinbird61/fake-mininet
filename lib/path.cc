#include "path.h"

Path::Path()
{}

Path::~Path()
{}

void Path::append(Edge *elist)
{
    Edge *trav = elist;
    while(trav!=NULL){
        this->tree[trav->head->name].push_back(trav);
        trav=trav->next;
    }
}

std::vector<std::vector<Edge *>> Path::find_paths(std::string src, std::string sink)
{
    // trav through the branches
    this->path.clear();
    this->paths.clear();
    std::vector<Vertex *> empty;
    this->trav(src, sink, empty);
    return this->paths;
}

int Path::trav(std::string prev, std::string end, std::vector<Vertex *> existed_vertices){
    // Existed, push head node 
    if(this->tree[prev].size() > 0 && (std::find(existed_vertices.begin(), existed_vertices.end(), this->tree[prev].at(0)->head)==existed_vertices.end())){
        existed_vertices.push_back(this->tree[prev].at(0)->head);
    }

    if(prev==end){
        // END
        this->paths.push_back(this->path);
        return 0;
    }

    // push the root into path
    for(int i=0;i<this->tree[prev].size();i++){
        // check edge is already existed or not
        if(find(this->path.begin(), this->path.end(), this->tree[prev].at(i))==this->path.end()){
            // check the tail is in the existed_vertices or not
            if(std::find(existed_vertices.begin(), existed_vertices.end(), this->tree[prev].at(i)->tail)==existed_vertices.end()){
                // and push this edge into dfs result
                this->path.push_back(this->tree[prev].at(i));
                // not existed, then push into existed
                existed_vertices.push_back(this->tree[prev].at(i)->tail);
                // recursive
                if(!this->trav(this->tree[prev].at(i)->tail->name, end, existed_vertices)){
                    this->path.pop_back();
                }
            }
        }
    }

    return 0;
}

void Path::debug()
{
    std::cout<< "======================================================" << std::endl;
    std::cout << "Number of found paths: " << this->paths.size() << std::endl;
    for(int i=0;i<this->paths.size();i++)
    {
        for(int x=0;x<this->paths.at(i).size();x++)
        {
            std::cout << this->paths.at(i).at(x)->head->name << "->" << this->paths.at(i).at(x)->tail->name << " ";
        }
        std::cout << "\n";
    }
    std::cout<< "======================================================" << std::endl;
}