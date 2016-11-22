#include "a.h"
int main(int argc,char* argv[]) {
    Bank* bankList;
    loadFile(LOAD_FILENAME,&bankList);

    printAllList(bankList);
    return 0;
}
