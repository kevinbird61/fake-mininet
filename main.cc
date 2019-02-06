#include <iostream>
#include <unistd.h>
#include "shell.h"

int main(int argc, char** argv){
    int ch;
    string fin("");
    // parameter configure
    while((ch=getopt(argc, argv, "f:"))!=-1)
    {
        switch(ch)
        {
            case 'f':
                fin = string(optarg);
                break;
        }
    }

    if(fin!=string("")){
        // interpret first
        sh_interpret(fin);
    }

    // enter CLI 
    sh_loop();

    return 0;
}