#include "path.h"

Path::Path()
{}

Path::~Path()
{}

void Path::append(Edge *elist)
{
    Edge *trav = elist;
    while(trav!=NULL){
        // find 2 vertex, and add them into tree 
        // add if not existed
        if(this->tree.find(trav->head->name)==this->tree.end()){
            this->tree[trav->head->name] = new Node(trav->head);
        }
        if(this->tree.find(trav->tail->name)==this->tree.end()){
            this->tree[trav->tail->name] = new Node(trav->tail);
        }
        // and using br link then together
        this->tree[trav->head->name]->br[trav->tail->name]=this->tree.at(trav->tail->name);
        // this->tree[trav->tail->name]->br[trav->head->name]=this->tree[trav->head->name];

        // std::cout << trav->head->name << "<->" << trav->tail->name << " :" << this->tree[trav->head->name]->br.size() << std::endl;
        trav=trav->next;
    }
}

std::vector<std::vector<Node *>> Path::find_paths(std::string src, std::string sink)
{
    // trav through the branches
    this->path.push_back(this->tree[src]);
    this->trav(src, sink);
    return this->paths;
}

int Path::trav(std::string prev, std::string end){
    // push the root into path
    // this->path.push_back(this->tree[prev]);
    // trav through the branches
    for(std::map<std::string, Node *>::iterator iter=this->tree[prev]->br.begin();
        iter!=this->tree[prev]->br.end(); iter++)
        {
            // std::cout << this->tree[prev]->br.size() << " " << prev << ":" << iter->first << std::endl;
            // check if iter->first is already in path
            bool flag=true;
            for(int i=0;i<this->path.size();i++){
                if(this->path.at(i)->name==iter->first){
                    flag=false;
                    break;
                }
            }
            if(flag){
                this->path.push_back(iter->second);
                if(iter->first==end){
                    // reach the end
                    std::vector<Node *> newPath;
                    newPath = this->path;
                    this->paths.push_back(newPath);
                } else {
                    // not end, continue
                    this->trav(iter->first, end);
                }
                // pop back
                this->path.pop_back();
            }
        }
}

void Path::debug()
{
    std::cout<< "======================================================" << std::endl;
    for(std::map<std::string, Node *>::iterator iter=this->tree.begin();
        iter!=this->tree.end(); iter++)
        {
            std::cout << "Node: " << iter->first << std::endl;
            std::cout << "Number of branches: " << iter->second->br.size() << std::endl;
        }
    std::cout<< "======================================================" << std::endl;
    std::cout << "Number of found paths: " << this->paths.size() << std::endl;
    for(int i=0;i<this->paths.size();i++)
    {
        for(int x=0;x<this->paths.at(i).size();x++)
        {
            std::cout << this->paths.at(i).at(x)->name << " ";
        }
        std::cout << "\n";
    }
    std::cout<< "======================================================" << std::endl;
}