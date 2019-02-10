#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> dfs_paths;
vector<Vertex *> existed_vertices;

void dfs(string src);

int main(int argc, char** argv){
    // build basic topo
    // sub1
    nm->add_switch("a");
    nm->add_switch("d");
    nm->add_host("b");
    nm->add_host("c");
    // sub2
    nm->add_switch("e");
    nm->add_switch("h");
    nm->add_host("g");
    nm->add_host("f");

    nm->connect("a", "e");
    nm->connect("a", "h");
    nm->connect("b", "a");
    nm->connect("b", "c");
    nm->connect("b", "d");
    nm->connect("d", "b");
    nm->connect("d", "h");

    nm->connect("e", "f");
    nm->connect("e", "h");
    nm->connect("g", "e");
    nm->connect("f", "g");
    nm->connect("h", "g");

    Edge *elist = nm->elist;

    // build the edges belong to vertex 
    while(elist!=NULL){
        adv[elist->head->name].push_back(elist);
        elist=elist->next;
    }

    // DFS, start from "a"
    dfs("a");

    Edge *dfs_elist=NULL, *tmp=dfs_elist;

    cout << "DFS: " << endl;
    for(int i=0;i<dfs_paths.size();i++){
        cout << dfs_paths.at(i)->head->name << "->" << dfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            dfs_elist = new Edge(dfs_paths.at(i));
            tmp = dfs_elist;
        } else {
            tmp->next = new Edge(dfs_paths.at(i));
            tmp = tmp->next;
        }
    }

    Gplot *gp = new Gplot();
    gp->gp_add(dfs_elist);
    gp->gp_dump(true);
    gp->gp_export("dfs");

    return 0;
}

void dfs(string src){
    // push this node into existed list
    existed_vertices.push_back(nm->get_node(src));
    for(int i=0;i<adv[src].size();i++){
        // cout << adv[src].at(i)->head->name << "=>" << adv[src].at(i)->tail->name << endl;
        // check the tail is in the existed_vertices or not
        if(find(dfs_paths.begin(), dfs_paths.end(), adv[src].at(i))==dfs_paths.end()){
            // not existed, then push into existed
            existed_vertices.push_back(adv[src].at(i)->tail);
            // and push this edge into dfs result
            dfs_paths.push_back(adv[src].at(i));
            // recursive
            dfs(adv[src].at(i)->tail->name);
        }
    }
}