#include <iostream>
#include <string>

// Required by for routine
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int globalVariable = 2;

int main()
{
    string sIdentifier;
    int    iStackVariable = 20;
    pid_t childPid, parentPid;

    pid_t pID = fork();

    if (pID < 0) {
	    cerr << "Failed to fork" << endl;
	    return 1;
	}

	if (pID == 0) {                // child, code only executed by child process
	    sIdentifier = "Child  ";
	    globalVariable++;
	    iStackVariable++;
	}
    else {      // parent,Code only executed by parent process
        sIdentifier = "Parent ";
    }

    // Code executed by both parent and child.
    cout << sIdentifier<<"pid: "<<getpid();
    cout << " Global variable: " << globalVariable;
    cout << " Stack variable: "  << iStackVariable << endl;

    return 0 ;
}

