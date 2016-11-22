#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NAME_SIZE               128
#define MAX_ACCOUNT_NUMBER_SIZE     128
#define MAX_DATE_SIZE               128
#define MAX_BUFFER_SIZE             256

#define BASE_BANK_AMOUNT            100000
#define BASE_LOAN_AMOUNT            0
#define BASE_LOAN_LIMIT             50000

#define LOAD_FILENAME               "input.txt"
#ifndef false
#define false 0
#endif
#ifndef true
#define true !(false)
#endif

#define PRINT_DOUBLE_LINE()         puts("==========================")


typedef struct AccountHistory {
    int     id;
    char    fromAccountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    char    toAccountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    double  amount;
    struct AccountHistory *next;
    struct Account* account;
} AccountHistory;
typedef struct Account {
    int     id;
    char    accountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    double  accountAmount;
    AccountHistory* accountHistoryList;
    struct Account* next;
    struct User* user;
} Account;
typedef struct User {
    int     id;
    char    userName[MAX_NAME_SIZE];
    double  loanAmount;
    double  loanLimit;
    Account* accountList;
    struct User* next;
    struct Bank* bank;
} User;
typedef struct Bank {
    int     id;
    char    bankName[MAX_NAME_SIZE];
    double  bankTotalAmount;
    User*   userList;
    struct Bank* next;
} Bank;

typedef AccountHistory* AccountHistoryList;
typedef Account* AccountList;
typedef User* UserList;
typedef Bank* BankList;

/*
 * print entry
 */
void printAccountHistory(AccountHistory *p) {
    printf("%d. [%s] [%s] amount: [%lf] \n",p->id,p->fromAccountNumber,p->toAccountNumber,p->amount);
}
void printAccount(Account* p){
    printf("%s\n%s\namount : %lf\n",p->user->userName,p->accountNumber,p->accountAmount);
}
void printAccountVersionAll(Account* p) {
    /* for debug */
    printf("id: [%d] accountNumber: [%s] accountAmount: [%lf]\n",p->id,p->accountNumber,p->accountAmount);
}
void printUser(User* p) {
    printf("%s\n",p->userName);
}
void printUserVersionAll(User* p) {
    printf("id: [%d] userName: [%s] loanAmount: [%lf] loanLimit: [%lf]\n",p->id,p->userName,p->loanAmount,p->loanLimit);
}
void printBank(Bank* p) {
    printf("id: [%d] bankName: [%s] bankTotalAmount: [%lf]\n",p->id,p->bankName,p->bankTotalAmount);
}
/*
 * print list
 */
void printAccountHistoryList(AccountHistoryList accountHistoryList) {
    AccountHistory* p = accountHistoryList;
    if ( p == NULL ) return;
    PRINT_DOUBLE_LINE();
    printf("accountNumber : %s\n",p->account->accountNumber);
    for ( ; p ; p=p->next ) 
        printAccountHistory(p);
    PRINT_DOUBLE_LINE();

}
void printAccountList(AccountList accountList) {
    Account* p = accountList;
    if ( p == NULL ) return;
    PRINT_DOUBLE_LINE();
    printf("userName : %s\n",p->user->userName);
    for ( ; p ; p=p->next ) 
        printAccount(p);
    PRINT_DOUBLE_LINE();
}
void printUserList(UserList userList) {
    User* p = userList;
    if ( p == NULL ) return;
    PRINT_DOUBLE_LINE();
    printf("%s\n\n",p->bank->bankName);
    for ( ; p ; p=p->next ) 
        printUser(p);
    PRINT_DOUBLE_LINE();
}
void printBankList(BankList bankList) {
    Bank* p = bankList;
    if ( p == NULL ) return;
    PRINT_DOUBLE_LINE();
    for ( ; p ; p=p->next ) 
        printBank(p);
    PRINT_DOUBLE_LINE();
}
void printAllList(BankList bankList) {
    Bank* bp;
    User* up;
    Account* ap;
    AccountHistory* ahp;

    for ( bp=bankList ; bp ; bp=bp->next ) {
        printBank(bp);
        for ( up=bp->userList ; up ; up=up->next ) {
            printf("\t");
            printUserVersionAll(up);
            for ( ap=up->accountList ; ap ; ap=ap->next ) {
                printf("\t\t");
                printAccountVersionAll(ap);
                for ( ahp=ap->accountHistoryList ; ahp ; ahp=ahp->next ) {
                    printf("\t\t\t");
                    printAccountHistory(ahp);
                }
            }
        }
    }
}

/*
 * get new node 
 */
AccountHistory* getNewAccountHistroy(char* _fromAccountNumber,\
                                     char* _toAccountNumber,\
                                     double _amount,\
                                     Account* _account) {
    AccountHistory* history = (AccountHistory*)malloc(sizeof(AccountHistory));
    strcpy(history->fromAccountNumber,_fromAccountNumber);
    strcpy(history->toAccountNumber,_toAccountNumber);
    history->amount = _amount;
    history->next   = NULL;
    history->account= _account;
    history->id     = 0;
    return history;
}
Account* getNewAccount(char* _accountNumber,\
                       double _accountAmount,\
                       User* _user) {
    Account* account = (Account*)malloc(sizeof(Account));
    strcpy(account->accountNumber,_accountNumber);
    account->accountAmount      = _accountAmount;
    account->accountHistoryList = NULL;
    account->next               = NULL;
    account->user               = _user;
    account->id                 = 0;
    return account;
}
User* getNewUser(char* _userName,\
                 double _loanAmount,\
                 double _loanLimit,\
                 Bank* _bank) {
    User* user = (User*)malloc(sizeof(User));
    strcpy(user->userName,_userName);
    user->loanAmount    = _loanAmount;
    user->loanLimit     = _loanLimit;
    user->accountList   = NULL;
    user->next          = NULL;
    user->bank          = _bank;
    user->id            = 0;
    return user;
}
Bank* getNewBank(char* _bankName,\
                 double _bankTotalAmount) {
    Bank* bank = (Bank*)malloc(sizeof(Bank));
    strcpy(bank->bankName,_bankName);
    bank->bankTotalAmount   = _bankTotalAmount;
    bank->userList          = NULL;
    bank->next              = NULL;
    bank->id                = 0;
    return bank;
}
/*
 * get last node at each list
 */
AccountHistory* getLastNodeAtAccountHistoryList(AccountHistoryList accountHistoryList) {
    AccountHistory* p = accountHistoryList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next );
    return p;
}
Account* getLastNodeAtAccountList(AccountList accountList) {
    Account* p = accountList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next );
    return p;
}
User* getLastNodeAtUserList(UserList userList) {
    User* p = userList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next ); 
    return p;
}
Bank* getLastNodeAtBankList(BankList bankList) {
    Bank* p = bankList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next);
    return p;
}
/*
 * list push back
 */
AccountHistory* pushBackAtAccountHistoryList(AccountHistoryList* accountHistoryList,\
                                             char* _fromAccountNumber,\
                                             char* _toAccountNumber,\
                                             double _amount,\
                                             Account* _account) {
    AccountHistory* newAccountHistory = getNewAccountHistroy(_fromAccountNumber,\
                                                             _toAccountNumber,\
                                                             _amount,\
                                                             _account);
    if ( *accountHistoryList == NULL ) {
        newAccountHistory->id   = 1;
        *accountHistoryList     = newAccountHistory;
    } else {
        AccountHistory* lastNode = getLastNodeAtAccountHistoryList(*accountHistoryList);
        assert(lastNode != NULL);
        newAccountHistory->id   = lastNode->id + 1;
        lastNode->next          = newAccountHistory;
    }
    return newAccountHistory;
}
Account* pushBackAtAccountList(AccountList* accountList,\
                               char *_accountNumber,\
                               double _accountAmount,\
                               User* _user) {
    Account* newAccount = getNewAccount(_accountNumber,\
                                        _accountAmount,\
                                        _user);
    if ( *accountList == NULL ) {
        newAccount->id  = 1;
        *accountList    = newAccount;
    } else {
        Account* lastNode = getLastNodeAtAccountList(*accountList);
        assert(lastNode != NULL);
        newAccount->id  = lastNode->id + 1;
        lastNode->next  = newAccount;
    }
    return newAccount;
}
User* pushBackAtUserList(UserList* userList,\
                         char* _userName,\
                         double _loanAmount,\
                         double _loanLimit,\
                         Bank* _bank) {
    User* newUser = getNewUser(_userName,\
                               _loanAmount,\
                               _loanLimit,\
                               _bank);
    if ( *userList == NULL ) {
        newUser->id = 1;
        *userList = newUser;
    } else {
        User* lastNode = getLastNodeAtUserList(*userList);
        assert(lastNode != NULL);
        newUser->id     = lastNode->id + 1;
        lastNode->next  = newUser;
    }
    return newUser;
}
Bank* pushBackAtBankList(BankList* bankList,\
                         char* _bankName,\
                         double _bankTotalAmount) {
    Bank* newBank = getNewBank(_bankName,\
                               _bankTotalAmount);
    if ( *bankList == NULL ) {
        newBank->id = 1;
        *bankList   = newBank;
    } else {
        Bank* lastNode = getLastNodeAtBankList(*bankList);
        assert(lastNode != NULL);
        newBank->id     = lastNode->id + 1;
        lastNode->next  = newBank;
    }
    return newBank;
}
/*
 * find node at list 
 */
Account* findAccountByAccountNumber(AccountList accountList,\
                                    char* _accountNumber) {
    Account* p;
    for ( p=accountList ; p ; p=p->next ) 
        if ( !strcmp(p->accountNumber,_accountNumber) ) 
            return p;
    return NULL;
}
Account* findAccountByAccountNumberAtAllBankList(BankList bankList,\
                                                 char* _accountNumber) {
    Bank* bp;
    User* up;
    Account* ap;
    for ( bp=bankList ; bp ; bp=bp->next ) 
        for ( up=bp->userList ; up ; up=up->next )
            for ( ap=up->accountList ; ap ; ap=ap->next ) 
                if ( !strcmp(ap->accountNumber,_accountNumber) ) 
                    return ap;
    return NULL;
}
User* findUserByUserName(UserList userList,\
                         char* _userName) {
    User* p;
    for ( p=userList ; p ; p=p->next ) 
        if ( !strcmp(p->userName,_userName) ) 
            return p;
    return NULL;
}
Bank* findBankByBankName(BankList bankList,\
                         char* _bankName) {
    Bank* p;
    for ( p=bankList ; p ; p=p->next ) 
        if ( !strcmp(p->bankName,_bankName) ) 
            return p;
    return NULL;
}
Bank* findBankByBankId(BankList bankList,\
                       int _id) {
    Bank* p;
    for ( p=bankList ; p ; p=p->next ) 
        if ( p->id == _id ) 
            return p;
    return NULL;
}
/*
 * remove Account and User
 */
Account* getPrevNodeAtAccountList(AccountList accountList,Account* cur) {
    Account* p = accountList;
    if ( p == cur ) return NULL; /* never */
    for ( ; p->next == cur ; p=p->next );
    return p;
}
Account* removeAccountByAccountNumber(AccountList* accountList,Account* ap) {
    if ( *accountList == NULL ) return NULL;
    if ( ap ) {
        if ( *accountList == ap ) {
            *accountList = ap->next;
        } else {
            Account* prev = getPrevNodeAtAccountList(*accountList,ap);
            prev->next = ap->next;
        }
        return ap;
    } else {
        return NULL;
    }
    return NULL;
}
User* getPrevNodeAtUserList(UserList userList,User* cur) {
    User* p = userList;
    if ( p == cur ) return NULL; /* never */
    for ( ; p->next == cur ; p=p->next );
    return p;
}
User* removeUser(UserList* userList,User* u) {
    if ( *userList == NULL ) return NULL; /* never */
    if ( *userList == u ) {
        *userList = u->next;
    } else {
        User* prev = getPrevNodeAtUserList(*userList,u);
        prev->next = u->next;
    }
    return u;
}
/*
 * update Amount
 */
int updateBankTotalAmount(Bank* bp,double _amount) {
    assert(bp != NULL); /* error: bank is not exists */
    bp->bankTotalAmount += _amount;
    return true;
}
int updateAccountAmount(Account* ap,double _amount) {
    if ( ap->accountAmount + _amount < 0 ) return false;
    ap->accountAmount += _amount;
    updateBankTotalAmount(ap->user->bank,_amount);
    return true;
}
/*
 * transfer
 */
int sendAmountFromUserToUser(Account* from,Account* to,double _amount) {
    if ( from->accountAmount - _amount < 0 ) return false;
    updateAccountAmount(from,-_amount);
    updateAccountAmount(to,_amount);
    return true;
}

/*
 * loan
 */
int updateUserLoan(User* up,double _amount) {
    up->loanAmount += _amount;
    return true;
}
double getBankLoanLimit(Bank* bank) {
    User* up;
    Account* ap;
    double amountSum = 0;
    for ( up=bank->userList ; up ; up=up->next ) 
        for ( ap=up->accountList ; ap ; ap=ap->next ) 
            amountSum += ap->accountAmount;
    return bank->bankTotalAmount - amountSum;
}
int loanAmountFromBank(Account* ap,Bank* bp,double _amount) {
    double bankLoanLimit = getBankLoanLimit(bp);
    if ( bankLoanLimit < _amount ) return false;
    updateAccountAmount(ap,_amount);
    updateBankTotalAmount(bp,-_amount);
    updateUserLoan(ap->user,_amount);
    return true;
}
/*
 * account termination
 */
int accountTermination(Account* ap,Bank* bp) {
    double bankLoanLimit = getBankLoanLimit(bp);
    if ( bankLoanLimit < ap->accountAmount ) return -13;
    if ( ap->accountAmount < 0 ) return -14;
    updateBankTotalAmount(bp,-ap->accountAmount);
    User* curUser = ap->user;
    removeAccountByAccountNumber(&(curUser->accountList),ap);
    if ( curUser->accountList == NULL ) {
        removeUser(&bp->userList,curUser);
        return 2;
    } else {
        return 3;
    }
    return true;
}
/*
 * load file
 */
void loadFile(char *filename,BankList* bankList) {
    FILE* fp = fopen(filename,"r");
    char buf[MAX_BUFFER_SIZE]={};
    while ( ~fscanf(fp,"%[^\n]\n",buf) ) {
        char _bankName[MAX_NAME_SIZE]={};
        char _userName[MAX_NAME_SIZE]={};
        char _accountNumber[MAX_ACCOUNT_NUMBER_SIZE]={};
        char _accountAmount[MAX_BUFFER_SIZE]={};
        char *tok = strtok(buf," \t");
        strcpy(_bankName,tok);
        tok = strtok(NULL," \t");
        strcpy(_userName,tok);
        tok = strtok(NULL," \t");
        strcpy(_accountNumber,tok);
        tok = strtok(NULL," \t");
        strcpy(_accountAmount,tok);
        double accountAmount;
        sscanf(_accountAmount,"%lf",&accountAmount);
        Bank* bp = findBankByBankName(*bankList,_bankName);
        if ( bp ) {
            User* up = findUserByUserName(bp->userList,_userName);
            if ( up ) {
                Account* ap = findAccountByAccountNumber(up->accountList,_accountNumber);
                assert(ap==NULL);
                /*
                 * error!
                 * same account information
                 */
                ap = pushBackAtAccountList(&(up->accountList),\
                                          _accountNumber,\
                                          accountAmount,\
                                          up);
                pushBackAtAccountHistoryList(&(ap->accountHistoryList),\
                                             "registration",\
                                             _accountNumber,\
                                             accountAmount,\
                                             ap);
                updateBankTotalAmount(bp,accountAmount);
            } else {
                User* user = pushBackAtUserList(&(bp->userList),\
                                                _userName,\
                                                BASE_LOAN_AMOUNT,\
                                                BASE_LOAN_LIMIT,\
                                                bp);
                Account* ap = pushBackAtAccountList(&(user->accountList),\
                                                    _accountNumber,\
                                                    accountAmount,\
                                                    user);
                pushBackAtAccountHistoryList(&(ap->accountHistoryList),\
                                             "registration",\
                                             _accountNumber,\
                                             accountAmount,\
                                             ap);
                updateBankTotalAmount(bp,accountAmount);
            }
        } else {
            Bank* bp = pushBackAtBankList(bankList,_bankName,BASE_BANK_AMOUNT);
            User* user = pushBackAtUserList(&(bp->userList),_userName,\
                                            BASE_LOAN_AMOUNT,BASE_LOAN_LIMIT,bp);
            Account* ap = pushBackAtAccountList(&(user->accountList),\
                                                _accountNumber,accountAmount,user);
            pushBackAtAccountHistoryList(&(ap->accountHistoryList),\
                                         "registration",\
                                         _accountNumber,\
                                         accountAmount,\
                                         ap);
            updateBankTotalAmount(bp,accountAmount);
        }
    }
    fclose(fp);
}
void printMenuScene1(BankList bankList) {
    puts("========== MENU ==========");
    puts("1. select bank");
    puts("2. bank user and user account list ");
    puts("3. quit");
    PRINT_DOUBLE_LINE();
}
void printMenuScene1_1(BankList bankList) {
    Bank* p;
    puts("====== SELECT BANK =======");
    for ( p=bankList ; p ; p=p->next ) {
        printf("%d. %s (total amount: %lf)\n",p->id,p->bankName,p->bankTotalAmount);
    }
    PRINT_DOUBLE_LINE();
}
void printMenuScene2(UserList userList) {
    puts("======= MENU (BANK) ======");
    puts("1. select user");
    puts("2. new user registration");
    puts("3. go to menu");
    PRINT_DOUBLE_LINE();
}
void printMenuScene2_1(UserList userList) {
    printUserList(userList);
}
void printMenuScene3(AccountList accountList) {
    puts("======= MENU (USER) ======");
    puts("1. new account registration");
    puts("2. deposits and withdrawals");
    puts("3. bank transfer");
    puts("4. loan");
    puts("5. transaction history");
    puts("6. account termination");
    puts("7. my account list");
    puts("8. go to bank menu");
    PRINT_DOUBLE_LINE();
}
void printMenuMessage(int s) {
    if ( s == 1 ) {
        printf("select menu : ");
    } else if ( s == 2 ) {
        printf("type user's name : ");
    } else if ( s == 3 ) {
        printf("type account number : ");
    } else if ( s == 4 ) {
        printf("type the amount : ");
    } else if ( s == 5 ) {
        printf("type send account number : ");
    } else if ( s == 6 ) {
        printf("type receive account number : ");
    }
}
void printErrorMessage(int e) {
    if ( e == -1 ) {
        printf("command not found\n");
    } else if ( e == -2 ) {
        printf("The bank does not exists\n");
    } else if ( e == -3 ) {
        printf("The user does not exists\n");
    } else if ( e == -4 ) {
        printf("The username aleady exists\n");
    } else if ( e == -5 ) {
        printf("The account number aleady exists\n");
    } else if ( e == -6 ) {
        printf("The account does not exists\n");
    } else if ( e == -7 ) {
        printf("There is not enough amount\n");
    } else if ( e == -8 ) {
        printf("The amount can not be 0\n");
    } else if ( e == -9 ) {
        printf("The amount must be greater than 0\n");
    } else if ( e == -10 ) {
        printf("The amount is insufficient and can not be transfered\n");
    } else if ( e == -11 ) {
        printf("There is not enough amount to loan\n");
    } else if ( e == -12 ) {
        printf("You can not loan beyond the limit of the loan\n");
    } else if ( e == -13 ) {
        printf("You can not terminate because the bank limit is less than 0\n");
    }
}
void printBankUserAccountInformation(Bank* p) {
    User* up;
    Account* ap;
    PRINT_DOUBLE_LINE();
    printf("%s\n\n",p->bankName);
    for ( up=p->userList ; up ; up=up->next ) {
        if ( up->accountList == NULL ) {
            printf("%s has not yet created an account\n\n",up->userName);
        }
        for ( ap=up->accountList ; ap ; ap=ap->next ) {
            printAccount(ap);
        }
    }
    printf("bankTotalAmount : %lf\n",getBankLoanLimit(p));
    PRINT_DOUBLE_LINE();
}
void printUserAccountInformation(User* p) {
    Account* ap;
    PRINT_DOUBLE_LINE();
    for ( ap=p->accountList ; ap ; ap=ap->next ) {
        printAccount(ap);
    }
    PRINT_DOUBLE_LINE();
}
void printAllUserAccountInformation(BankList bankList) {
    Bank* bp;
    User* up;
    Account* ap;
    PRINT_DOUBLE_LINE();
    for ( bp=bankList ; bp ; bp=bp->next ) 
        for ( up=bp->userList ; up ; up=up->next ) 
            for ( ap=up->accountList ; ap ; ap=ap->next ) 
                printAccount(ap);
    PRINT_DOUBLE_LINE();
}
void printBankLoanLimit(Bank* bank) {
    PRINT_DOUBLE_LINE();
    printf("%s\nloan limit : %lf\n",bank->bankName,getBankLoanLimit(bank));
    PRINT_DOUBLE_LINE();
}
void printAccountHistoryListReverse(AccountHistory* ahp) {
    if ( ahp == NULL ) return;
    printAccountHistoryListReverse(ahp->next);
    printAccountHistory(ahp);
}
