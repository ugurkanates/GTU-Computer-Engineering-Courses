#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include "memory.h"
#include <string>




#define MAX_THREAD_NUMBER 5
#define ROBIN 100

using namespace std;



typedef enum {
    READY = 0,
    RUNNING = 1,
    BLOCKED = 2
} Thread_Status;

typedef struct {
    State8080 savedState;    // new -> saved registers like a,b,c,sp,pc
    int threadID; // NEW ->  • The thread ID
    int cycleStart; // new -> starting time of process, the cycle number of the CPU
    int cycleUsed; // new -> how many cycle the process hadd used so far
    Thread_Status  threadStatusCurrent; // new -> ready, blocked, running
    int StartAddress;   // new -> physical addres of the memory location of process
    bool activated; // 0 not activated , 1 activated yes thread is alive !
} ThreadTable;

class GTUOS{

	public:
        GTUOS(const CPU8080& obje);
        ~GTUOS();

    void demoFunction(const CPU8080 &obje);

        uint64_t handleCall(const CPU8080& cpu8080);
        void memoryBackup(const CPU8080& obje,ofstream& writefile);
        int theMain(CPU8080& obje,char **argv); // Returns number of cycles so far in program's life.

    private:
        int whichFunctionToCall(uint8_t myRegister,const CPU8080& obje);
        int print_B(const CPU8080& obje);
        int print_Mem(const CPU8080& obje);
        int read_B(const CPU8080& obje);
        int read_Mem(const CPU8080& obje);
        int print_Str(const CPU8080& obje);
        int read_Str(const CPU8080& obje);
        int get_Rnd(const CPU8080& obje);
        int tCreate(const CPU8080& obje,ThreadTable& threadList);
        int tExit(const CPU8080& obje,ThreadTable& threadList);
        int tJoin(const CPU8080& obje,ThreadTable& threadList);
        int tYield(const CPU8080& obje,ThreadTable& threadList);

        int getNextThread();
        bool allThreadsDone();
        void contextSwitch(int current, int next,CPU8080& obje);


        //for checking which sysCall made from in SwitchCase
         const int sPRINT_B=1;
         const int sPRINT_MEM=2;
         const int sREAD_B=3;
         const int sREAD_MEM=4;
         const int sPRINT_STR=5;
         const int sREAD_STR=6;
         const int sGET_RND=7;
         const int sT_CREATE=8;
         const int sT_EXIT=9;
         const int sT_JOIN=10;
         const int sT_YIELD=11;

        // list  of cycles to return and collect from functinos
        const int PRINT_B =10;
        const int PRINT_MEM =10;
        const int READ_B =10;
        const int READ_MEM =10;
        const int PRINT_STR =100;
        const int READ_STR =100;
        const int GET_RND =5;
        const int T_CREATE =80;
        const int T_EXIT = 50;
        const int T_JOIN = 40;
        const int T_YIELD = 40;


        const int ADRRBYTE = 10;
        const int sizeOftestBuffer = 5 ;

        //
        ThreadTable *threadList;
        int currentThreadIndex;



};

#endif
