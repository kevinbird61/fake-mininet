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
    string raw;
    // loop first
    do {
        cout << "fakeCLI@cyu> ";
        getline(std::cin, raw);
        args = sh_readline(raw);
        status = sh_execute(args);
    } while(status);
}

int sh_interpret(string filename)
{
    string raw;
    ifstream fin(filename);
    vector<string> args;
    int status=0;

    // read
    if(fin.is_open()) {
        while(getline(fin, raw)) {
            args = sh_readline(raw);
            status = sh_execute(args);
        }
    } else {
        cout << "Illegal input command file." << endl;
    }

    return 0;
}

vector<string> sh_readline(string raw)
{
    string tmp;
    vector<string> args_token;
    // split into several token
    stringstream ssin(raw);
    while(ssin.good()) {
        ssin >> tmp;
        args_token.push_back(tmp);
    }

    return args_token;
}

int sh_execute(vector<string> args)
{
    if(args.at(0)=="exit") {
        cout << "Bye, see you next time!" << endl;
        return 0;
    } else if(args.at(0)=="help") {
        print_help();
        return 1;
    } else if(args.at(0)=="create"||args.at(0)=="c") {
        // create
        if(args.size() >= 2) {
            // create - switch
            if(args.at(1)=="switch" || args.at(1)=="sw") {
                Switch *sw;
                sw = new Switch();
                if(args.size()>=3) {
                    // specify name by user
                    sw->set_name(args.at(2));
                } else {
                    // set by NetworkManager
                    //  - will have an automatically increase number, like s1,s2,s3 ...
                    sw->set_name(nm.get_sw_name());
                }

                if(!nm.add_vertex(sw)) {
                    // print success
                    cout << "Create new switch, name: " << sw->get_name() << endl;
                }
            }
            // create - host
            else if(args.at(1)=="host" || args.at(1)=="h") {
                Host *h;
                h = new Host();
                if(args.size()>=3) {
                    // specify name by user
                    h->set_name(args.at(2));
                } else {
                    // set by NetworkManager
                    //  - will have an automatically increase number, like h1,h2,h3 ...
                    h->set_name(nm.get_h_name());
                }

                if(!nm.add_vertex(h)) {
                    // print success
                    cout << "Create new Host, name: " << h->get_name() << endl;
                }
            }
            // other
            else {
                cout << "Error format, please using `help` command to check the detail information." << endl;
            }
        } else {
            // create nothing
            cout << "Please specify your object, like `create sw myswitch` or `create h myhost` ... etc. Type `help` command to see more." << endl;
        }
        return 1;
    } else if(args.at(0)=="link"||args.at(0)=="l") {
        // link
        if(args.size() >= 4) {
            // find two node in network manager
            // args[1]: head, args[2]: tail
            if(args.at(3)=="up") {
                // create edge
                nm.connect(args.at(1), args.at(2));
            } else if(args.at(3)=="down") {
                // delete edge
                nm.disconnect(args.at(1), args.at(2));
            }
        } else {
            cout << "Please comply with the link command, like `link s1 s2 up` or `link h1 s2 down` ... etc. Type `help` command to see more." << endl;
        }
        return 1;
    } else if(args.at(0)=="setlink" || args.at(0)=="sl") {
        // `setlink v1 v2 cap #`
        // `setlink v1 v2 val #`
        if(args.size()>=4) {
            if(args.at(3)=="cap"||args.at(3)=="c") {
                // setlink capacity
                nm.setlink(args.at(1), args.at(2), 0, stoi(args.at(4)));
            } else if(args.at(3)=="val"||args.at(3)=="v") {
                // setlink flowval
                nm.setlink(args.at(1), args.at(2), 1, stoi(args.at(4)));
            }
        } else {
            cout << "Please comply with the `setlink` command, like `setlink s1 s2 cap 10` or `link h1 s2 val 5` ... etc. Type `help` command to see more." << endl;
        }

        return 1;
    } else if(args.size() >= 3) {
        if(args.at(1)=="ping") {
            // A ping B
            // check edges
            if(!nm.connected(args.at(0), args.at(2))) {
                cout << "Connected: " << args[0] << " is connected with " << args[2] << endl;
            } else {
                cout << "Disconnected." << endl;
            }
        }
    } else if(args.at(0)=="net") {
        // Display links
        nm.print_all_e();
        return 1;
    } else if(args.at(0)=="nodes") {
        // Display nodes
        nm.print_all_v();
        return 1;
    } else if(args.at(0)=="clear") {
        // clear and reset
        nm.clear();
        return 1;
    } else if(args.at(0)=="debug") {
        // print all vertices
        nm.print_all_v();
        // print all edges
        nm.print_all_e();
        return 1;
    } else if(args.at(0)=="plot") {
        // send the edge list
        gp.gp_add(nm.elist);
        cout<< "======================================================" << endl;
        cout << gp.gp_dump(true) << endl;
        cout<< "======================================================" << endl;
        return 1;
    } else if(args.at(0)=="export") {
        // dump the gplot content into a dotfile
        // args.at(1): filename. If not existed, then use default setting
        if(args.size() < 2) {
            // default
            gp.gp_export(string("fake-mininet-gplot"));
        } else {
            // user's filename
            gp.gp_export(string(args.at(1)));
        }
        cout << "Dotfile successfully exported." << endl;
        return 1;
    } else if(args.size()==1 && args.at(0)== "") {
        // nothing, just enter
        return 1;
    }
    /* New command add using "ELSE IF" */
    else {
        cout << "Not support yet, please using `help` to print helping message." << endl;
        return 1;
    }
}

void print_help()
{
    cout << "\nWelcome to use fakeCLI!" << "\n"
         << "Support commands:" << "\n"
         << "-----------------------------------------------------------------------------------------" << "\n"
         << " \033[1;31m help \033[0m: print this helping message, to illustrate user how to use our service." << "\n"
         << " \033[1;31m exit \033[0m: close this fake CLI elegantly." << "\n"
         << " \033[1;31m clear \033[0m: clear and reset the network status (like `mn -c`)." << "\n"
         << " \033[1;31m debug \033[0m: show the current status of network manager." << "\n"
         << "-----------------------------------------------------------------------------------------" << "\n"
         << " \033[1;36m create\033[0m \033[33m[host|switch]\033[0m \033[92m<device name>\033[0m: create virtual device." << "\n"
         << " \033[1;36m link\033[0m \033[92m<device #1> <device #2>\033[0m \033[33m[up|down]\033[0m: connect/disconnect 2 virtual devices." << "\n"
         << " \033[92m <device #1>\033[0m \033[1;36mping\033[0m \033[92m<device #2>\033[0m: check whether those devices are connected or not." << "\n"
         << " \033[1;36m setlink\033[0m \033[92m<device #1> <device #2>\033[0m \033[33m[cap|val]\033[0m \033[92m<value>\033[0m: set the capacity/flow value of the link between 2 specified vertices." << "\n"
         << " \033[1;36m net \033[0m: display links." << "\n"
         << " \033[1;36m nodes \033[0m: display nodes (switch, host)." << "\n"
         << " \033[1;36m plot \033[0m: show the current content of topology. (in dotfile format) " << "\n"
         << " \033[1;36m export \033[0m\033[33m[filename]\033[0m: export the dotfile. (If you don't specify the filename, then will generate the dotfile with default setting)" << "\n"
         << "-----------------------------------------------------------------------------------------" << "\n"
         << endl;

    cout << "If you have counter any problem, feel free to contact me: \n"
         << " Email: kevinbird61@gmail.com\n"
         << " Github: github.com/kevinbird61\n"
         << endl;
}