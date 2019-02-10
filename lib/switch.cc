#include "switch.h"

Switch::Switch()
{
    this->type = std::string("switch");
    this->next = NULL;
}

Switch::Switch(char *name)
{
    this->name = std::string(name);
    this->type = std::string("switch");
    this->next = NULL;
}

Switch::Switch(Switch *sw)
{
    this->name = sw->name;
    this->type = std::string("switch");
    this->next = NULL;
}

Switch::Switch(std::string name)
{
    this->name = name;
    this->type = std::string("switch");
    this->next = NULL;
}

Switch::~Switch()
{

}

void Switch::set_name(std::string name)
{
    this->name = name;
}

std::string Switch::get_name()
{
    return this->name;
}
