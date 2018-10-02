#include <iostream>
#include <fstream>
#include "8080emuCPP.h"
#include "gtuos.h"
using namespace std;

/*
 *
 * UGURKAN ATES 151044012
 * HW 01 Operating System Software 312
 * INTEL 8080 emulation  with operating system
 * basic syscalls
 * listed
 * 1-printb = Prints the contents of register B on
the screen as a decimal number.
 * 2-print_mem=
 * Prints the contents of the memory
pointed by registers B and C as a
decimal number.
 * 3-readb=
 * Reads an integer from the keyboard
and puts it in register B.
 * 4-read_mem=
 * Reads an integer from the keyboard
and puts it in the memory location
pointed by registers B and C
 * 5-print_str=
 * Prints the null terminated string at
the memory location pointed by B
and C
 * 6-read_str=
 * Reads the null terminated string
from the keyboard and puts the
result at the memory location
pointed by B and C
 * 7-get_rnd=
 * Produces a random byte and puts in
register B
 */
/*
 *
 * Will use default Constructor();
 * no data Initialization are made from GTUOS header.
 *
 */
/*
 * This below function taken from
 * https://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
 * Without this or sleep random function would work too fast and even with
 * seed as time(NULL)it did return same numbers
 * this method uses 3 input to create psuedorandom numbers for most part
 * -> time,pid,clock are inputs
 *
 */
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

void GTUOS::memoryBackup(const CPU8080& obje,ofstream& writefile){

    for(int i=0;i<0x1000;++i){
        char test[sizeOftestBuffer];
        sprintf(test,"%04x",i*16);
        writefile<<test<<" ";
        for(int j=0;j<0x10;++j) {
            sprintf(test,"%02x",obje.memory->at((i*16+j)));
            writefile << test << " ";
        }
        writefile<<endl;
    }
}

int GTUOS::whichFunctionToCall(uint8_t myRegister, const CPU8080 &obje) {
    int willReturn = 0;
    switch (myRegister){
        case (uint8_t) 1:
            willReturn= print_B(obje);
            break;
        case (uint8_t) 2:
            willReturn = print_Mem(obje);
            break;
        case (uint8_t) 3:
            willReturn = read_B(obje);
            break;
        case (uint8_t) 4:
            willReturn = read_Mem(obje);
            break;
        case (uint8_t) 5:
            willReturn = print_Str(obje);
            break;
        case (uint8_t) 6:
            willReturn = read_Str(obje);
            break;
        case (uint8_t) 7:
            willReturn = get_Rnd(obje);
            break;
        default:
            cerr<<"Error on operation"<<endl;
            exit(-1);
    }
    return willReturn;

}
uint64_t GTUOS::handleCall(const CPU8080& obje){
    uint8_t  myRegister = obje.state->a;
    uint64_t cTime=0;
    cTime+=whichFunctionToCall(myRegister,obje);

    return cTime;
}

/*
 * Print content of register B + returns cycle num;
 */

int GTUOS::print_B(const CPU8080& obje){
    cout<<"print_b ; register B ="<<int(obje.state->b)<<endl;
    return PRINT_B;
}
/*
 * gets integer range of 0-255 if wrong puts 255 to input
 * then assign integer from cin to register b
 * with state->b
 * return cycle num;
 */


int GTUOS::read_B(const CPU8080 &obje) {
    int input;
    cout<<"read_B ; Please enter input integer for register B:"<<endl;
    cin>>input;

    if(input>=0 && input<=255){
        obje.state->b=input;
    }else {
        obje.state->b = 255;
        cout<<"8 Bit integer overflowed.255 assigned to register B"<<endl;
    }
    // no need to cast input (uin8t) we checked already.
    return READ_B;
}
/*
 * Print null terminaed string with standart ooutput+ returns cycle num;
 */

int GTUOS::print_Str(const CPU8080 &obje) {
    cout<<"print_Str ;"<<endl;

    uint16_t address = (obje.state->b << 8) | obje.state->c;
    address = (obje.state->c) | (obje.state->b << 8);
    for(;;){
        if(obje.memory->at(address)=='\0'){
            break;
        }
        cout<<obje.memory->at(address);
        ++address;
    }
    return PRINT_STR;
}
/*
 * get string from user and put to test
 * put that string register B-C with 000000000 left shifting b and or'ing with C
 * + returns cycle num;
 */

int GTUOS::read_Str(const CPU8080 &obje) {
    string test;
    uint16_t address;
    cout<<"read_Str ; "<<endl;
    getline(cin,test);

    address = (obje.state->b << 8) | obje.state->c;

    for(int i=0;i<test.length();++i){
        obje.memory->at(address+i) = (uint8_t) test[i];
    }
    obje.memory->at((address++)+test.length()-1)='\n';
    obje.memory->at(address+test.length()-1)='\0';
    cout<<"Adress:"<<unsigned(address)<<endl;
    return READ_STR;
}

/*
 * print adress of B leftshifted+c to see adress of BC and memory of BC+ returns cycle num;
 */

int GTUOS::print_Mem(const CPU8080& obje){
    uint16_t address;
    cout<<"print_Mem ; "<<endl;
    address = (obje.state->b << 8) | obje.state->c;
    cout<<"Adress BC: "<<address<<endl;
    cout<<"Memory BC:"<<(int)obje.memory->at(address)<<endl;
    return PRINT_MEM;
}

/*
 * get 0-255 input integer from user
 * if error put 255 to integer and put that to memory BC
 *
 * + returns cycle num;
 */
int GTUOS::read_Mem(const CPU8080 &obje) {

    int input;
    uint16_t address;
    cout<<"read_Mem ; "<<endl;
    cout<<"Please enter input for Memory BC:";
    cin>>input;
    address = (obje.state->b << 8) | obje.state->c;

    if(input>=0 && input<=255){
        obje.memory->at(address) = (uint8_t) input;
        obje.memory->at(address)=0;
    }else {
        obje.memory->at(address) = 255;
        cout <<"8 Bit integer overflowed.255 assigned to memoryBC";
    }
    cout<<"number memoryBC:"<<unsigned(address)<<endl;
}
/*
 *  init seed with time
 *  get random withing 8bit
 *  modulo ->
 *  put into register B and return cycle num;
 *
 */
int GTUOS::get_Rnd(const CPU8080 &obje) {
    unsigned long seed = mix(clock(), time(NULL), clock());
    srand (seed);
    uint8_t  randomByte;
    randomByte = rand()%256;
    obje.state->b = randomByte;
    return GET_RND;
}




void GTUOS::demoFunction(const CPU8080 &obje){

    char adress[ADRRBYTE];
    obje.state->b=0x00;
    obje.state->c=0x40;
    read_Mem(obje);
    print_Mem(obje);

    sprintf(adress,"0x%x%x",obje.state->b,obje.state->c);
    cout<<adress;
    read_Str(obje);
    print_Str(obje);
}





