#include "shell.h"
#include "gplot.h"

// global variables
NetworkManager nm;
Gplot gp;

int sh_loop()
{
    // variables
    vector<string> args;
    int status=0;

    // loop first
    do {
        cout << "fakeCLI@cyu> ";
        args = sh_readline();
        status = sh_execute(args);
    } while(status);
}

vector<string> sh_readline()
{
    string raw,tmp;
    vector<string> args_token;
    // get oneline 
    getline(std::cin, raw);
    // split into several token
    stringstream ssin(raw);
    while(ssin.good()){
        ssin >> tmp;
        args_token.push_back(tmp);
    }

    return args_token;
}

int sh_execute(vector<string> args)
{
    if(args.at(0)=="exit"){
        cout << "Bye, see you next time!" << endl;
        return 0;
    }
    else if(args.at(0)=="help"){
        print_help();
        return 1;
    }
    else if(args.at(0)=="create"||args.at(0)=="c"){
        // create 
        if(args.size() > 2){
            // create - switch 
            if(args.at(1)=="switch" || args.at(1)=="sw"){
                Switch *sw;
                sw = new Switch();
                if(args.size()>=3){
                    // specify name by user
                    sw->set_name(args.at(2));
                } else {
                    // TODO: set by NetworkManager 
                    //  - will have an automatically increase number, like s1,s2,s3 ...
                }

                if(!nm.add_vertex(sw)){
                    // print success
                    cout << "Create new switch, name: " << sw->get_name() << endl;
                }
            }
            // create - host 
            else if(args.at(1)=="host" || args.at(1)=="h"){
                Host *h;
                h = new Host();
                if(args.size()>=3){
                    // specify name by user
                    h->set_name(args.at(2));
                } else {
                    // TODO: set by NetworkManager 
                    //  - will have an automatically increase number, like h1,h2,h3 ...
                }

                if(!nm.add_vertex(h)){
                    // print success
                    cout << "Create new Host, name: " << h->get_name() << endl;
                }
            }
            // other
            else {
                cout << "Error format, please using `help` command to check the detail information." << endl;
            }
        }
        else {
            // create nothing
            cout << "Please specify your object, like `create sw myswitch` or `create h myhost` ... etc. Type `help` command to see more." << endl;
        }
        return 1;
    }
    else if(args.at(0)=="link"){
        // link
        if(args.size() >= 3){
            // find two node in network manager
            // args[1]: head, args[2]: tail
            nm.connect(args.at(1), args.at(2));
        }
        else {
            cout << "Please specify 2 objects, like `link s1 s2` or `link h1 s2` ... etc. Type `help` command to see more." << endl;
        }
        return 1;
    }
    else if(args.size() >= 3){
        if(args.at(1)=="ping"){
            // A ping B
            // check edges 
            if(!nm.check_status(args.at(0), args.at(2))){
                cout << "Connected: " << args[0] << " is connected with " << args[2] << endl;
            } else {
                cout << "Disconnected." << endl;
            }
        }
    }
    else if(args.at(0)=="pingAll"){
        // show all the connected status
        nm.print_all_e();
        return 1;
    }
    else if(args.at(0)=="debug"){
        // print all vertices
        nm.print_all_v();
        // print all edges
        nm.print_all_e();
        return 1;
    }
    else if(args.at(0)=="plot"){
        // send the edge list 
        gp.gp_add(nm.elist);
        cout<< "======================================================" << endl;
        cout << gp.gp_dump(true) << endl;
        cout<< "======================================================" << endl;
        return 1;
    }
    else if(args.at(0)=="export"){
        // dump the gplot content into a dotfile
        // args.at(1): filename. If not existed, then use default setting
        if(args.size() < 2){
            // default
            gp.gp_export(string("fake-mininet-gplot"));
        } else {
            // user's filename
            gp.gp_export(string(args.at(1)));
        }
        cout << "Dotfile successfully exported." << endl;
        return 1;
    }
    else if(args.size()==1 && args.at(0)== ""){
        // nothing, just enter
        return 1;
    }
    /* New command add using "ELSE IF" */
    else {
        cout << "Not support yet, please using `help` to print helping message." << endl;
        return 1;
    }
}

void print_help(){
    cout << "\nWelcome to use fakeCLI!" << "\n"
        << "Support commands:" << "\n"
        << "-----------------------------------------------------------------------------------------" << "\n"
        << " help: print this helping message, to illustrate user how to use our service." << "\n" 
        << " exit: close this fake CLI elegantly." << "\n"
        << " debug: show the current status of network manager." << "\n"
        << "-----------------------------------------------------------------------------------------" << "\n"
        << " create [host|switch] <device name>: create virtual device." << "\n"
        << " link <device #1> <device #2>: connect 2 virtual devices." << "\n"
        << " <device #1> ping <device #2>: check whether those devices are connected or not." << "\n"
        << "-----------------------------------------------------------------------------------------" << "\n"
        << endl;

    cout << "If you have counter any problem, feel free to contact me: \n"
        << " Email: kevinbird61@gmail.com\n" 
        << endl;
}