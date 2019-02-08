#include <iostream>
#include <unistd.h>
#include <map>
#include "network_manager.h"
#include "path.h"

using namespace std;

int main(int argc, char** argv){
    // create NetworkManager first
    NetworkManager *nm;
    nm=new NetworkManager();

    // build basic topo
    nm->add_host(std::string("s"));
    nm->add_host(std::string("t"));
    nm->add_switch(std::string("u"));
    nm->add_switch(std::string("v"));
    nm->add_switch(std::string("x"));
    nm->add_switch(std::string("y"));
    nm->connect(std::string("s"), std::string("u"));
    nm->connect(std::string("s"), std::string("x"));
    nm->connect(std::string("u"), std::string("v"));
    nm->connect(std::string("v"), std::string("x"));
    nm->connect(std::string("v"), std::string("t"));
    nm->connect(std::string("x"), std::string("y"));
    nm->connect(std::string("y"), std::string("t"));
    // set the capacity & flowvalue of the link
    nm->setlink(std::string("s"), std::string("x"), 1, 0);
    nm->setlink(std::string("u"), std::string("v"), 0, 1);
    nm->setlink(std::string("v"), std::string("x"), 0, 1);
    nm->setlink(std::string("x"), std::string("y"), 0, 1);
    nm->setlink(std::string("v"), std::string("t"), 1, 0);
    // print current status
    nm->print_all_e();

    // get all existed edges
    Edge *elist = nm->elist;

    map<string, vector<Edge*>> forward, backward;
    while(elist!=NULL){
        forward[elist->head->name].push_back(new Edge(elist));
        backward[elist->tail->name].push_back(new Edge(elist));
        elist=elist->next;
    }

    // define Searched and Reached set
    map<string, Vertex *> S, R;
    // Init
    string source("s"), sink("t");
    // R={s}, S=∅
    R[string("s")]=nm->get_node(source); 

    // Ford-Fulkerson labeling algorithm
    for(map<string,Vertex*>::iterator i=R.begin();
        i!=R.end();i++)
    {
        cout << i->first << endl;
        // if not found in S
        if(S.find(i->first)==S.end()){
            // trav all forward edge
            for(int fi=0; fi<forward[i->first].size(); fi++){
                cout << "Forward: " << forward[i->first].at(fi)->head->name << "<->" << forward[i->first].at(fi)->tail->name << endl;
                // forward rules 
                if(forward[i->first].at(fi)->flowval < forward[i->first].at(fi)->cap){
                    // push into R
                    R[forward[i->first].at(fi)->tail->name]=forward[i->first].at(fi)->tail;
                }
            }
            // trav all backward edge
            for(int bi=0; bi<backward[i->first].size(); bi++){
                cout << "Backward: " << backward[i->first].at(bi)->tail->name << "<->" << backward[i->first].at(bi)->head->name << endl;
                // backward rules
                if(backward[i->first].at(bi)->flowval > 0){
                    // push into R
                    R[backward[i->first].at(bi)->head->name]=backward[i->first].at(bi)->head;
                }
            }
            // after traversal all existed edge, then push into S
            S[i->first]=i->second;

            cout << "R: ";
            for(map<string,Vertex*>::iterator i=R.begin();
                i!=R.end();i++)
                {
                    cout<< i->first << " ";
                }
            cout << "\nS: ";
            for(map<string,Vertex*>::iterator i=S.begin();
                i!=S.end();i++)
                {
                    cout<< i->first << " ";
                }
            cout << "\n";
        }
    }

    cout << "R-S =>" << endl;
    // Find out the rest of R-S
    // FIXME: this part should be placed in the iterative function/loop, possibly need to be done more than one time!
    for(map<string,Vertex*>::iterator i=R.begin();
        i!=R.end();i++)
    {
        // not found in S
        if(S.find(i->first)==S.end()){
            cout << "Find node: " << i->first << endl;
            cout << "Augment Path: " << endl;
            // trace from the sink to source
            string head=i->first, tail=sink;
            bool direction=false; // true: forward, false: backward. Default is backward (because we start from the sink)
            // FIXME:
            // current solution is dirty. need to find a complete solution
            int cnt=0;
            while(head!=source){
                if(direction){
                    // forward
                    for(int fi=0; fi<forward[head].size(); fi++){
                        // FIXME:
                        // use first one
                        if(forward[head].at(fi)->tail->name!=sink){
                            cout << head << "->" << tail << endl;
                            tail = forward[head].at(fi)->tail->name;
                            break;
                        }
                    }
                    direction=!direction;
                } else {
                    // backward
                    for(int bi=0; bi<backward[tail].size(); bi++){
                        if(tail==sink) break;
                        if(backward[tail].at(bi)->head->name==source){
                            cout << head << "->" << tail << endl;
                            head = backward[tail].at(bi)->head->name;
                            break;
                        }
                    }
                    direction=!direction;
                }
            }
            cout << head << "->" << tail << endl;
        }

    }
    
    return 0;
}