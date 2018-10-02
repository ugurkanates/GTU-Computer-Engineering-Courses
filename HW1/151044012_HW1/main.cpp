#include <iostream>
#include <fstream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

using namespace std;

int main(int argc, char **argv) {
    string filer = "exe.mem";
    ofstream writefile;
    uint64_t totalCycle = 0;
    memory mem;
    CPU8080 theCPU(&mem);
    GTUOS theOS;

    if (argc != 3) {
		cerr << "Usage: prog exeFile debugOption\n";
		exit(1);
	}
	int DEBUG = atoi(argv[2]);

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);

	writefile.open(filer.c_str()); //sonradan

        //sonradan
	if (!writefile.is_open()) {
		cerr << "Unable to open output file:" << filer << endl;
		return 1;
	}

    //bi kısmı bozukbugllu
	do {
		totalCycle += theCPU.Emulate8080p(DEBUG);

		if (theCPU.isSystemCall())
			totalCycle += theOS.handleCall(theCPU);

		if (DEBUG == 2)
			cin.get();

	} while (!theCPU.isHalted());

    cout << "Number of cycles:" << totalCycle << endl;
    //sonradan

	theOS.memoryBackup(theCPU,writefile); //DEBUG 0 DEBUG 1 DEBUG 2 BOTH SAME
	writefile.close(); //sonradan

	return 0;
}

