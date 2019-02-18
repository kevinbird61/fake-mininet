#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> bfs_paths;
vector<Vertex *> existed_vertices;
queue<Edge *> bfs_search;

void bfs(string src);

int main(int argc, char** argv){
    // build basic topo
    // sub1
    nm->add_switch("a");
    nm->add_switch("d");
    nm->add_switch("b");
    nm->add_switch("c");
    // sub2
    nm->add_switch("e");
    nm->add_switch("h");
    nm->add_switch("g");
    nm->add_switch("f");

    nm->connect("a", "e");
    nm->connect("a", "h");
    nm->connect("b", "a");
    nm->connect("b", "c");
    nm->connect("b", "d");
    nm->connect("d", "b");
    nm->connect("d", "c");
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

    // BFS
    existed_vertices.push_back(nm->get_node("b"));
    bfs("b");
    while(!bfs_search.empty()){
        bfs(bfs_search.front()->tail->name);
        bfs_search.pop();
    }

    Edge *bfs_elist=NULL, *tmp=bfs_elist;

    cout << "BFS: " << endl;
    for(int i=0;i<bfs_paths.size();i++){
        cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            bfs_elist = new Edge(bfs_paths.at(i));
            tmp = bfs_elist;
        } else {
            tmp->next = new Edge(bfs_paths.at(i));
            tmp = tmp->next;
        }
    }

    Gplot *gp = new Gplot();
    gp->gp_add(bfs_elist);
    gp->gp_dump(true);
    gp->gp_export("bfs/bfs");

    return 0;
}

void bfs(string src){
    for(int i=0;i<adv[src].size();i++){
        // cout << adv[src].at(i)->head->name << "=>" << adv[src].at(i)->tail->name << endl;
        // check the tail is in the existed_vertices or not
        if(find(bfs_paths.begin(), bfs_paths.end(), adv[src].at(i))==bfs_paths.end()){
            // if tail is not existed, then push into existed vertices
            if(find(existed_vertices.begin(), existed_vertices.end(), adv[src].at(i)->tail)==existed_vertices.end()){
                // and push this edge into bfs result
                bfs_paths.push_back(adv[src].at(i));
                // not existed, then push into existed
                existed_vertices.push_back(adv[src].at(i)->tail);
                // push
                bfs_search.push(adv[src].at(i));
            }
        }
    }
}