#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "path.h"

using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;

// declare your own function
vector<Edge *> find_path(string src, string sink, vector<Edge *> path);

int main(int argc, char** argv){
    // build basic topo
    nm->add_host(std::string("s"));
    nm->add_host(std::string("t"));
    nm->add_switch(std::string("u"));
    nm->add_switch(std::string("v"));
    nm->add_switch(std::string("x"));
    nm->add_switch(std::string("y"));
    nm->connect_r(std::string("s"), std::string("u"));
    nm->connect_r(std::string("s"), std::string("x"));
    nm->connect_r(std::string("u"), std::string("v"));
    nm->connect_r(std::string("v"), std::string("x"));
    nm->connect_r(std::string("v"), std::string("t"));
    nm->connect_r(std::string("x"), std::string("y"));
    nm->connect_r(std::string("y"), std::string("t"));
    // set the capacity & flowvalue of the link
    nm->setlink(std::string("s"), std::string("u"), 1, 0);  // set flow value
    nm->setlink(std::string("s"), std::string("x"), 1, 0);  
    nm->setlink(std::string("u"), std::string("v"), 1, 0);  
    nm->setlink(std::string("v"), std::string("x"), 1, 0);
    nm->setlink(std::string("v"), std::string("t"), 1, 0);
    nm->setlink(std::string("x"), std::string("y"), 1, 0);
    nm->setlink(std::string("y"), std::string("t"), 1, 0);
    nm->setlink(std::string("u"), std::string("v"), 0, 1);  // set capacity
    nm->setlink(std::string("v"), std::string("x"), 0, 1);
    nm->setlink(std::string("x"), std::string("y"), 0, 1);
    // reverse 
    nm->setlink(std::string("u"), std::string("s"), 0, 0);
    nm->setlink(std::string("x"), std::string("s"), 0, 0);
    nm->setlink(std::string("v"), std::string("u"), 0, 0);
    nm->setlink(std::string("x"), std::string("v"), 0, 0);
    nm->setlink(std::string("t"), std::string("v"), 0, 0);
    nm->setlink(std::string("y"), std::string("x"), 0, 0);
    nm->setlink(std::string("t"), std::string("y"), 0, 0);
    // print current status
    nm->print_all_e();

    // get all existed edges
    Edge *elist = nm->elist;

    // build 
    while(elist!=NULL){
        adv[elist->head->name].push_back(elist);
        elist=elist->next;
    }
    /*for(map<string, vector<Edge*>>::iterator it=adv.begin(); it!=adv.end(); it++){
        cout << it->first << endl;
        for(int i=0;i<it->second.size();i++){
            cout << it->second.at(i)->head->name << "<->" << it->second.at(i)->tail->name << endl;
        }
        cout << "\n";
    }*/

    // max flow
    vector<Edge *> result;
    result = find_path(string("s"), string("t"), result);
    while(!result.empty()){
        // find min-flow
        int min=9999;
        for(int i=0;i<result.size();i++){
            int residual=(result.at(i)->cap)-(result.at(i)->flowval);
            if(residual < min) min=residual;
        }
        // update flow value
        for(int i=0;i<result.size();i++){
            // find edge
            for(int ie=0; ie<adv[result.at(i)->head->name].size(); ie++){
                if((adv[result.at(i)->head->name].at(ie)->head->name == result.at(i)->head->name) && (adv[result.at(i)->head->name].at(ie)->tail->name == result.at(i)->tail->name)){
                    adv[result.at(i)->head->name].at(ie)->flowval += min;
                    break;
                }
            }
            // reverse
            for(int ie=0; ie<adv[result.at(i)->tail->name].size(); ie++){
                if((adv[result.at(i)->tail->name].at(ie)->head->name == result.at(i)->tail->name) && (adv[result.at(i)->tail->name].at(ie)->tail->name == result.at(i)->head->name)){
                    adv[result.at(i)->tail->name].at(ie)->flowval -= min;
                    break;
                }
            }
        }
        result.clear();
        result = find_path(string("s"), string("t"), result);
    }

    // sum 
    int maxflow=0;
    for(int i=0;i<adv[string("s")].size();i++){
        maxflow += adv[string("s")].at(i)->flowval;
    }

    cout << "Max flow value: " << maxflow << ". (between s and t)" << endl;

    return 0;
}

vector<Edge *> find_path(string src, string sink, vector<Edge *> path)
{
    if(src==sink){
        return path;
    }
    // for all the edge start from src
    for(int i=0; i<adv[src].size(); i++){
        int residual = adv[src].at(i)->cap - adv[src].at(i)->flowval;
        if(residual>0 && find(path.begin(), path.end(), adv[src].at(i))==path.end()){
            vector<Edge *> tmp(path.begin(), path.end());
            path.push_back(adv[src].at(i));
            tmp = find_path(adv[src].at(i)->tail->name, sink, path);
            if(!tmp.empty()){
                return tmp;
            } 
        }
    }

    // all not match, return empty 
    path.clear();
    return path;
}