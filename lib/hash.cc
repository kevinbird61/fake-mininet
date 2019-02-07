#include "hash.h"

unsigned int djb2(const char *str)
{
    unsigned int hash = 5381;
    int c;
    while(c=*str++) {
        hash = ((hash << 5)+hash)+c;
    }
    return hash;
}

unsigned int jenkins(unsigned char *str)
{
    unsigned int hash = 0;
    while(*str) {
        hash += *str;
        hash += (hash << 10);
        hash ^= (hash >> 6);
        str++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}