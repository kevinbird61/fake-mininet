#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

/* SSSR: Single-Source Shortest Path */

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> bfs_paths;
vector<Vertex *> existed_vertices;
vector<Edge *> bfs_search;

bool compareWeight(Edge *e1, Edge *e2)
{
    return (e1->flowval < e2->flowval);
}

void sssp(string src);

int main(int argc, char** argv){
    // build basic topo
    nm->add_switch("a");
    nm->add_switch("d");
    nm->add_switch("b");
    nm->add_switch("c");
    nm->add_switch("e");
    nm->add_switch("h");
    nm->add_switch("g");
    nm->add_switch("f");
    nm->add_switch("i");

    nm->connect("a", "b");
    nm->connect("a", "d");
    nm->connect("a", "f");
    nm->connect("b", "c");
    nm->connect("c", "e");
    nm->connect("d", "g");
    nm->connect("e", "f");
    nm->connect("f", "a");
    nm->connect("f", "g");
    nm->connect("i", "g");
    nm->connect("g", "h");
    nm->connect("h", "e");

    // set weight (flowvale)
    nm->setlink("a", "b", 1, 3);
    nm->setlink("a", "d", 1, 5);
    nm->setlink("a", "f", 1, 2);
    nm->setlink("b", "c", 1, 5);
    nm->setlink("c", "e", 1, 3);
    nm->setlink("d", "g", 1, 3);
    nm->setlink("e", "f", 1, 1);
    nm->setlink("f", "a", 1, 1);
    nm->setlink("f", "g", 1, 0);
    nm->setlink("i", "g", 1, 1);
    nm->setlink("g", "h", 1, 5);
    nm->setlink("h", "e", 1, 4);

    Edge *elist = nm->elist;

    Gplot *gp = new Gplot();
    gp->gp_add(elist);
    gp->gp_dump(true);
    gp->gp_export("sssp/sssp-origin");

    // build the edges belong to vertex 
    while(elist!=NULL){
        adv[elist->head->name].push_back(elist);
        elist=elist->next;
    }

    // BFS
    existed_vertices.push_back(nm->get_node("a"));
    sssp("a");
    while(!bfs_search.empty()){
        cout << "Waiting queue: " << endl;
        for(int i=0;i<bfs_search.size();i++){
            cout << bfs_search.at(i)->head->name << "->" << bfs_search.at(i)->tail->name << ", ";
        }
        cout << endl;
        cout << "Next starting point: " << bfs_search.front()->tail->name << endl;

        Edge *e = bfs_search.front();
        bfs_search.erase(bfs_search.begin());
        sssp(e->tail->name);
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

    gp->gp_add(bfs_elist);
    gp->gp_dump(true);
    gp->gp_export("sssp/sssp");

    return 0;
}

void sssp(string src){
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
                // push front
                bfs_search.insert(bfs_search.begin(),adv[src].at(i));
            }
        }
    }
    // sort 
    sort(bfs_search.begin(), bfs_search.end(), compareWeight);
}