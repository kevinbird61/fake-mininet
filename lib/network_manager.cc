#include "network_manager.h"

NetworkManager::NetworkManager()
{
    // init (default: 10)
    this->tablesize=10;
    this->vlist = (Vertex**)malloc(this->tablesize*sizeof(Vertex *));
    for(int i=0;i<this->tablesize;i++){
        this->vlist[i]=NULL;
    }
    this->elist=NULL;
}

NetworkManager::NetworkManager(int tablesize)
{
    // init 
    this->tablesize = tablesize;
    this->vlist = (Vertex**)malloc(tablesize*sizeof(Vertex *));
    for(int i=0;i<this->tablesize;i++){
        this->vlist[i]=NULL;
    }
    this->elist=NULL;
}

NetworkManager::~NetworkManager()
{

}

int NetworkManager::add_vertex(Vertex *v)
{
    // find the insert point
    // std::cout << v->name << std::endl;
    // std::cout << "[Debug] Hash index:" << djb2(v->name.c_str())%this->tablesize << std::endl;
    unsigned int index = djb2(v->name.c_str())%this->tablesize;
    Vertex *insert = this->vlist[index];

    if(insert==NULL){
        this->vlist[index]=v;
        this->vlist[index]->next=NULL;
        // std::cout << "Name:" << this->vlist[djb2(v->name.c_str())%this->tablesize]->name << std::endl;
    } else {
        // check 
        if(insert->name==v->name){
            std::cout << "Duplicated device name. Cancel insert process." << std::endl;
            return 1;
        }
        while(insert->next!=NULL){
            // check
            if(insert->name==v->name){
                std::cout << "Duplicated device name. Cancel insert process." << std::endl;
                return 1;
            }
            insert=insert->next;
        }
        insert->next=v;
        insert->next->next=NULL;
    }

    return 0;
}

void NetworkManager::add_edge(Edge *e)
{
    Edge *insert = this->elist;
    if(insert==NULL){
        this->elist = e;
    } else {
        while(insert->next!=NULL){
            insert=insert->next;
        }
        insert->next=e;
    }
}

void NetworkManager::print_all_v(){
    std::cout<< "======================================================" << std::endl;
    std::cout<< "Print all vertices:" << std::endl;
    std::cout<< "======================================================" << std::endl;
    for(int i=0;i<this->tablesize;i++){
        Vertex *header = this->vlist[i];
        std::cout << "VList[" << i << "]: ";
        if(header!=NULL){
            std::cout << header->name << "(" << header->type << ")";
            while(header->next!=NULL){
                header=header->next;
                std::cout << ", " << header->name << "(" << header->type << ")";
            }
        }
        std::cout << "\n";
    }
}

void NetworkManager::print_all_e(){
    std::cout<< "======================================================" << std::endl;
    std::cout<< "Print all edges:" << std::endl;
    std::cout<< "======================================================" << std::endl;
    Edge *traversal = this->elist;
    while(traversal!=NULL){
        std::cout << traversal->head->name << "(" << traversal->head->type << ") <-> " << traversal->tail->name << "(" << traversal->tail->type << ")" << std::endl;
        traversal=traversal->next;
    }
}

void NetworkManager::connect(std::string hname, std::string tname){
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL){
        if(check->name == hname){
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL){
        if(check->name == tname){
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2){
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // create edge, and link those 2 together
    Edge *e;
    e = new Edge();
    e->link(head, tail);
    // push into nm
    this->add_edge(e);

    std::cout << "Connect `" << hname << "` with `" << tname << "` successfully." << std::endl;
}

void NetworkManager::disconnect(std::string hname, std::string tname){
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL){
        if(check->name == hname){
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL){
        if(check->name == tname){
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2){
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // find edge, and then destroy
    Edge *traversal=this->elist,*prev=this->elist;
    while(traversal!=NULL){
        if(traversal->head->name==hname && traversal->tail->name==tname){
            std::cout << "Disconnect `" << hname << "` with `" << tname << "` successfully." << std::endl;
            if(prev==this->elist){
                this->elist=this->elist->next;
            } else {
                prev->next=traversal->next;
            }
            return;
        }
        prev=traversal;
        traversal=traversal->next;
    }

    std::cout << "Not found the connection between `" << hname << "` and `" << tname << "`. You can use `net` or `debug` to check the current status." << std::endl;
}

int NetworkManager::check_status(std::string hname, std::string tname){
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL){
        if(check->name == hname){
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL){
        if(check->name == tname){
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2){
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return 1;
    }

    // check all edges
    Edge *traversal = this->elist;
    if(traversal!=NULL){
        if((traversal->head->name==hname && traversal->tail->name==tname)||(traversal->head->name==tname && traversal->tail->name==hname)){
            // find 
            return 0;
        }
        while(traversal->next!=NULL){
            traversal=traversal->next;
        }
    }
    return 1;
}
