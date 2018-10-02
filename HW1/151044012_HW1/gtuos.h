#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include "memory.h"
#include <string>

using namespace std;
class GTUOS{

	public:

		uint64_t handleCall(const CPU8080& cpu8080);
        void memoryBackup(const CPU8080& obje,ofstream& writefile);
        void demoFunction(const CPU8080& obje);

    private:
        int whichFunctionToCall(uint8_t myRegister,const CPU8080& obje);
        int print_B(const CPU8080& obje);
        int print_Mem(const CPU8080& obje);
        int read_B(const CPU8080& obje);
        int read_Mem(const CPU8080& obje);
        int print_Str(const CPU8080& obje);
        int read_Str(const CPU8080& obje);
        int get_Rnd(const CPU8080& obje);

        //for checking which sysCall made from in SwitchCase
         const int sPRINT_B=1;
         const int sPRINT_MEM=2;
         const int sREAD_B=3;
         const int sREAD_MEM=4;
         const int sPRINT_STR=5;
         const int sREAD_STR=6;
         const int sGET_RND=7;
        // list  of cycles to return and collect from functinos
        const int PRINT_B =10;
        const int PRINT_MEM =10;
        const int READ_B =10;
        const int READ_MEM =10;
        const int PRINT_STR =100;
        const int READ_STR =100;
        const int GET_RND =5;

        const int ADRRBYTE = 10;
        const int sizeOftestBuffer = 5 ;

};

#endif
