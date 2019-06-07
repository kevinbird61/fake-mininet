#include "network_manager.h"

NetworkManager::NetworkManager()
    :tablesize(10), switch_num(0), host_num(0)
{
    this->vlist = (Vertex**)malloc(this->tablesize*sizeof(Vertex *));
    for(int i=0; i<this->tablesize; i++) {
        this->vlist[i]=NULL;
    }
    this->elist=NULL;
}

NetworkManager::NetworkManager(int tablesize)
    :switch_num(0), host_num(0)
{
    // init
    this->tablesize = tablesize;
    this->vlist = (Vertex**)malloc(tablesize*sizeof(Vertex *));
    for(int i=0; i<this->tablesize; i++) {
        this->vlist[i]=NULL;
    }
    this->elist=NULL;
}

NetworkManager::~NetworkManager()
{

}

int NetworkManager::interpret(std::string filename)
{
    std::string raw;
    std::ifstream fin(filename);
    std::vector<std::string> args;
    int status=0;

    // read 
    if(fin.is_open()){
        while(getline(fin, raw)){
            args = this->readline(raw);
            status = this->execute(args);
        }
    } else {
        std::cout << "Illegal input command file." << std::endl;
    }
}

std::vector<std::string> NetworkManager::readline(std::string raw)
{
    std::string tmp;
    std::vector<std::string> args_token;
    // split into several token
    std::stringstream ssin(raw);
    while(ssin.good()) {
        ssin >> tmp;
        args_token.push_back(tmp);
    }
    return args_token;
}

int NetworkManager::execute(std::vector<std::string> args)
{
    // FIXME: currently all node will use Switch class 
    // args[0], args[1] : vertex 1, vertex 2
    // args[2] : capacity
    // args[3] : flowval
    if(args.size()<2){
        // error
        std::cout << "Need to specify at least 2 elements (e.g. `a b`) to represent the connection." << std::endl;
        return 1;
    } else if(args.size()==2){
        // a <---default---> b
        std::cout << "Set the link." << std::endl;
        this->add_switch(args[0]);
        this->add_switch(args[1]);
        this->connect(args[0], args[1]);
        return 1;
    } else if(args.size()==3){
        // a <---set cap---> b
        std::cout << "Set the link + capacity." << std::endl;
        this->add_switch(args[0]);
        this->add_switch(args[1]);
        this->connect_with_val(args[0], args[1], std::atoi(args[2].c_str()), 0);
        // this->setlink(args[0], args[1], 0, std::atoi(args[2].c_str()));
        return 1;
    } else if(args.size()==4){
        // a <---set cap,val---> b
        std::cout << "Set the link + capacity + flow value." << std::endl;
        this->add_switch(args[0]);
        this->add_switch(args[1]);
        this->connect_with_val(args[0], args[1], std::atoi(args[2].c_str()), std::atoi(args[3].c_str()));
        //this->setlink(args[0], args[1], 0, std::atoi(args[2].c_str()));
        //this->setlink(args[0], args[1], 1, std::atoi(args[3].c_str()));
        return 1;
    } else {
        // error
        std::cout << "Too many arguments, please check the manual first." << std::endl;
        return 1;
    }
}

int NetworkManager::add_vertex(Vertex *v)
{
    // find the insert point
    // std::cout << v->name << std::endl;
    // std::cout << "[Debug] Hash index:" << djb2(v->name.c_str())%this->tablesize << std::endl;
    unsigned int index = djb2(v->name.c_str())%this->tablesize;
    Vertex *insert = this->vlist[index];

    if(insert==NULL) {
        this->vlist[index]=v;
        this->vlist[index]->next=NULL;
        // std::cout << "Name:" << this->vlist[djb2(v->name.c_str())%this->tablesize]->name << std::endl;
    } else {
        // check
        if(insert->name==v->name) {
            std::cout << "Duplicated device name. Cancel insert process." << std::endl;
            return 1;
        }
        while(insert->next!=NULL) {
            // check
            if(insert->name==v->name) {
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

int NetworkManager::add_switch()
{
    Switch *sw;
    sw = new Switch(this->get_sw_name());
    this->add_vertex(sw);
}

int NetworkManager::add_switch(std::string name)
{
    Switch *sw;
    sw = new Switch(name);
    this->add_vertex(sw);
}

Switch *NetworkManager::create_switch()
{
    return new Switch(this->get_sw_name());
}

Switch *NetworkManager::create_switch(std::string name)
{
    return new Switch(name);
}

int NetworkManager::add_host()
{
    Host *h;
    h = new Host(this->get_h_name());
    this->add_vertex(h);
}

int NetworkManager::add_host(std::string name)
{
    Host *h;
    h = new Host(name);
    this->add_vertex(h);
}

Host *NetworkManager::create_host()
{
    return new Host(this->get_h_name());
}

Host *NetworkManager::create_host(std::string name)
{
    return new Host(name);
}

void NetworkManager::add_edge(Edge *e)
{
    Edge *insert = this->elist;
    if(insert==NULL) {
        this->elist = e;
    } else {
        while(insert->next!=NULL) {
            insert=insert->next;
        }
        insert->next=e;
    }
}

void NetworkManager::print_all_v()
{
    std::cout<< "======================================================" << std::endl;
    std::cout<< "Print all vertices:" << std::endl;
    std::cout<< "======================================================" << std::endl;
    for(int i=0; i<this->tablesize; i++) {
        Vertex *header = this->vlist[i];
        std::cout << "VList[" << i << "]: ";
        if(header!=NULL) {
            std::cout << header->name << "(" << header->type << ")";
            while(header->next!=NULL) {
                header=header->next;
                std::cout << ", " << header->name << "(" << header->type << ")";
            }
        }
        std::cout << "\n";
    }
}

void NetworkManager::print_all_e()
{
    std::cout<< "======================================================" << std::endl;
    std::cout<< "Print all edges:" << std::endl;
    std::cout<< "======================================================" << std::endl;
    Edge *traversal = this->elist;
    while(traversal!=NULL) {
        std::cout << traversal->head->name << "(" << traversal->head->type << ") <--[cap:"<< traversal->cap << "|val:" << traversal->flowval <<"]--> " << traversal->tail->name << "(" << traversal->tail->type << ")" << std::endl;
        traversal=traversal->next;
    }
}

void NetworkManager::connect(std::string hname, std::string tname)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
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

void NetworkManager::connect_with_val(std::string hname, std::string tname, int cap, int flowval)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // create edge, and link those 2 together
    Edge *e;
    e = new Edge();
    // set cap/flowval
    if(cap>0)
        e->set_cap(cap);
    if(flowval>0)
        e->set_flowval(flowval);
    // link
    e->link(head, tail);
    // push into nm
    this->add_edge(e);

    std::cout << "Connect `" << hname << "` with `" << tname << "` successfully." << std::endl;
}

void NetworkManager::connect_r(std::string hname, std::string tname)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // create edge, and link those 2 together
    Edge *e, *re;
    e = new Edge();
    re = new Edge();
    e->link(head, tail);
    re->link(tail, head);
    // push into nm
    this->add_edge(e);
    this->add_edge(re);

    std::cout << "Connect `" << hname << "` with `" << tname << "` successfully." << std::endl;
    std::cout << "Reversely Connect `" << tname << "` with `" << hname << "` successfully." << std::endl;
}

void NetworkManager::linkup(Vertex *head, Vertex *tail)
{
    // add vertex first
    this->add_vertex(head);
    this->add_vertex(tail);

    // create edge, and link those 2 together
    Edge *e;
    e = new Edge();
    e->link(head, tail);
    // push into nm
    this->add_edge(e);

    std::cout << "Connect `" << head->name << "` with `" << tail->name << "` successfully." << std::endl;
}

void NetworkManager::disconnect(std::string hname, std::string tname)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // find edge, and then destroy
    Edge *traversal=this->elist,*prev=this->elist;
    while(traversal!=NULL) {
        // std::cout << "traverse: " << traversal->head->name << " - " << traversal->tail->name << std::endl;
        if(traversal->head->name==hname && traversal->tail->name==tname) {
            std::cout << "Disconnect `" << hname << "` with `" << tname << "` successfully." << std::endl;
            if(prev==traversal) {
                this->elist=traversal->next;
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

void NetworkManager::linkdown(Vertex *head, Vertex *tail)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(head->name.c_str())%this->tablesize;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == head->name) {
            cnt++;
            break;
        }
    }
    index = djb2(tail->name.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tail->name) {
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // find edge, and then destroy
    Edge *traversal=this->elist,*prev=this->elist;
    while(traversal!=NULL) {
        if(traversal->head->name==head->name && traversal->tail->name==tail->name) {
            std::cout << "Disconnect `" << head->name << "` with `" << tail->name << "` successfully." << std::endl;
            if(prev==traversal) {
                this->elist=traversal->next;
            } else {
                prev->next=traversal->next;
            }
            return;
        }
        prev=traversal;
        traversal=traversal->next;
    }

    std::cout << "Not found the connection between `" << head->name << "` and `" << tail->name << "`. You can use `net` or `debug` to check the current status." << std::endl;
}

Vertex *NetworkManager::get_all_nodes()
{
    Vertex *rlist=NULL, *tmp;

    for(int i=0; i<this->tablesize; i++) {
        Vertex *header = this->vlist[i];
        while(header!=NULL) {
            if(rlist==NULL) {
                /*if(header->type==std::string("switch")) {
                    rlist = new Switch((Switch *)header);
                } else if(header->type==std::string("host")) {
                    rlist = new Host((Host *)header);
                }*/
                rlist=header;
                tmp=rlist;
            } else {
                /*if(header->type==std::string("switch")) {
                    tmp->next = new Switch((Switch *)header);
                } else if(header->type==std::string("host")) {
                    tmp->next = new Host((Host *)header);
                }*/
                tmp->next=header;
                tmp=tmp->next;
            }
            header=header->next;
        }
    }

    return rlist;
}

Vertex *NetworkManager::get_node(std::string name)
{
    unsigned int index=djb2(name.c_str())%this->tablesize;
    Vertex *header = this->vlist[index];
    while(header!=NULL) {
        if(header->name == name) {
            /*if(header->type==std::string("switch")) {
                rnode = new Switch((Switch *)header);
            } else if(header->type==std::string("host")) {
                rnode = new Host((Host *)header);
            }*/
            return header;
        }
        header=header->next;
    }

    return NULL;
}

Edge *NetworkManager::get_edge(Vertex *head, Vertex *tail)
{
    Edge *trav = this->elist;
    while(trav!=NULL){
        if((trav->head->name==head->name)&&(trav->tail->name==tail->name)){
            return trav;
        }
        trav=trav->next;
    }
    return NULL;
}

Edge *NetworkManager::get_edge(std::string hname, std::string tname)
{
    Edge *trav = this->elist;
    while(trav!=NULL){
        if((trav->head->name==hname)&&(trav->tail->name==tname)){
            return trav;
        }
        trav=trav->next;
    }
    return NULL;
}

void NetworkManager::setlink(std::string hname, std::string tname, int mode, int val)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return;
    }

    // check all edges
    Edge *traversal = this->elist;
    while(traversal!=NULL) {
        if((traversal->head->name==hname && traversal->tail->name==tname)) {
            // setlink
            if(mode==0) {
                traversal->set_cap(val);
                std::cout << "Set the capacity of link `" << hname << "` with `" << tname << "` to " << val << " successfully." << std::endl;
            } else if(mode==1) {
                traversal->set_flowval(val);
                std::cout << "Set the flow value of link `" << hname << "` with `" << tname << "` to " << val << " successfully." << std::endl;
            } else {
                std::cout << "Not support this link mode yet." << std::endl;
            }
            return ;
        }
        traversal=traversal->next;
    }

    std::cout << "Not found current link: " << hname << "<->" << tname << std::endl;
    return;
}

int NetworkManager::connected(std::string hname, std::string tname)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return 1;
    }

    // check all edges
    Edge *traversal = this->elist;
    while(traversal!=NULL) {
        if((traversal->head->name==hname && traversal->tail->name==tname)||(traversal->head->name==tname && traversal->tail->name==hname)) {
            // find
            return 0;
        }
        traversal=traversal->next;
    }
    return 1;
}

int NetworkManager::connected_d(std::string hname, std::string tname)
{
    // check if hname(head) and tname(tail) existed or not
    unsigned int index = djb2(hname.c_str())%this->tablesize;
    Vertex *head, *tail;
    Vertex *check = this->vlist[index];
    int cnt=0;
    while(check!=NULL) {
        if(check->name == hname) {
            head=check;
            cnt++;
            break;
        }
    }
    index = djb2(tname.c_str())%this->tablesize;
    check = this->vlist[index];
    while(check!=NULL) {
        if(check->name == tname) {
            tail=check;
            cnt++;
            break;
        }
    }

    if(cnt != 2) {
        std::cout << "Illegal name of vertex, please using print/debug command to check current topo." << std::endl;
        return 1;
    }

    // check all edges
    Edge *traversal = this->elist;
    while(traversal!=NULL) {
        if((traversal->head->name==hname && traversal->tail->name==tname)) {
            // find
            return 0;
        }
        traversal=traversal->next;
    }
    return 1;
}

std::string NetworkManager::get_sw_name()
{
    return std::string("s"+std::to_string(this->switch_num++));
}

std::string NetworkManager::get_h_name()
{
    return std::string("h"+std::to_string(this->host_num++));
}

void NetworkManager::clear()
{
    for(int i=0; i<this->tablesize; i++) {
        free(this->vlist[i]);
        this->vlist[i]=NULL;
    }
    free(this->elist);
    this->elist=NULL;
    switch_num=0;
    host_num=0;
    std::cout << "******************************************" << std::endl;
    std::cout << "Clear all virtual devices in fake-mininet." << std::endl;
    std::cout << "******************************************" << std::endl;
}