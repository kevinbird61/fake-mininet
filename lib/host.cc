#include "host.h"

Host::Host(){
    this->type = std::string("host"); 
    this->next = NULL;
}

Host::Host(std::string name){
    this->name = name;
    this->type = std::string("host"); 
    this->next = NULL;
}

Host::~Host(){}

void Host::set_name(std::string name){
    this->name = name;
}

std::string Host::get_name(){
    return this->name;
}