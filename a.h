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

typedef struct AccountHistory {
    char    fromAccountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    char    toAccountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    double  amount;
    char    date[MAX_DATE_SIZE];
    struct AccountHistory *next;
} AccountHistory;
typedef struct Account {
    char    accountNumber[MAX_ACCOUNT_NUMBER_SIZE];
    double  accountAmount;
    AccountHistory* accountHistoryList;
    struct Account* next;
} Account;
typedef struct User {
    char    userName[MAX_NAME_SIZE];
    double  loanAmount;
    double  loanLimit;
    Account* accountList;
    struct User* next;
} User;
typedef struct Bank {
    char    bankName[MAX_NAME_SIZE];
    double  bankTotalAmount;
    User*   userList;
    struct Bank* next;
} Bank;

/*
 * print entry
 */
void printAccountHistory(AccountHistory *p) {
    printf("from: [%s] to: [%s] amount: [%lf] date: [%s]\n",p->fromAccountNumber,p->toAccountNumber,p->amount,p->date);
}
void printAccount(Account* p){
    printf("accountNumber: [%s] accountAmount: [%lf]\n",p->accountNumber,p->accountAmount);
}
void printUser(User* p) {
    printf("userName: [%s] loanAmount: [%lf] loanLimit: [%lf]\n",p->userName,p->loanAmount,p->loanLimit);
}
void printBank(Bank* p) {
    printf("bankName: [%s] bankTotalAmount: [%lf]\n",p->bankName,p->bankTotalAmount);
}
/*
 * print list
 */
void printAccountHistoryList(AccountHistory* accountHistoryList) {
    AccountHistory* p = accountHistoryList;
    if ( p == NULL ) return;
    printf("------ACCOUNT-HISTORY------\n");
    for ( ; p ; p=p->next ) 
        printAccountHistory(p);
    printf("---------------------------\n");

}
void printAccountList(Account* accountList) {
    Account* p = accountList;
    if ( p == NULL ) return;
    printf("------ACCOUNT-LIST---------\n");
    for ( ; p ; p=p->next ) 
        printAccount(p);
    printf("---------------------------\n");

}
void printUserList(User* userList) {
    User* p = userList;
    if ( p == NULL ) return;
    printf("------------USER-----------\n");
    for ( ; p ; p=p->next ) 
        printUser(p);
    printf("---------------------------\n");
}
void printBankList(Bank* bankList) {
    Bank* p = bankList;
    if ( p == NULL ) return;
    printf("------------BANK-----------\n");
    for ( ; p ; p=p->next ) 
        printBank(p);
    printf("---------------------------\n");
}
void printAllList(Bank* bankList) {
    Bank* bp;
    User* up;
    Account* ap;
    AccountHistory* ahp;

    for ( bp=bankList ; bp ; bp=bp->next ) {
        printBank(bp);
        for ( up=bp->userList ; up ; up=up->next ) {
            printf("\t");
            printUser(up);
            for ( ap=up->accountList ; ap ; ap=ap->next ) {
                printf("\t\t");
                printAccount(ap);
                for ( ahp=ap->accountHistoryList ; ahp ; ahp=ahp->next ) {
                    printf("\t\t");
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
                                     char* _date) {
    AccountHistory* history = (AccountHistory*)malloc(sizeof(AccountHistory));
    strcpy(history->fromAccountNumber,_fromAccountNumber);
    strcpy(history->toAccountNumber,_toAccountNumber);
    strcpy(history->date,_date);
    history->amount = _amount;
    history->next   = NULL;
    return history;
}
Account* getNewAccount(char* _accountNumber,\
                       double _accountAmount) {
    Account* account = (Account*)malloc(sizeof(Account));
    strcpy(account->accountNumber,_accountNumber);
    account->accountAmount      = _accountAmount;
    account->accountHistoryList = NULL;
    account->next               = NULL;
    return account;
}
User* getNewUser(char* _userName,\
                 double _loanAmount,\
                 double _loanLimit) {
    User* user = (User*)malloc(sizeof(User));
    strcpy(user->userName,_userName);
    user->loanAmount    = _loanAmount;
    user->loanLimit     = _loanLimit;
    user->accountList   = NULL;
    user->next          = NULL;
    return user;
}
Bank* getNewBank(char* _bankName,\
                 double _bankTotalAmount) {
    Bank* bank = (Bank*)malloc(sizeof(Bank));
    strcpy(bank->bankName,_bankName);
    bank->bankTotalAmount   = _bankTotalAmount;
    bank->userList          = NULL;
    bank->next              = NULL;
    return bank;
}
/*
 * get last node at each list
 */
AccountHistory* getLastNodeAtAccountHistoryList(AccountHistory* accountHistoryList) {
    AccountHistory* p = accountHistoryList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next );
    return p;
}
Account* getLastNodeAtAccountList(Account* accountList) {
    Account* p = accountList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next );
    return p;
}
User* getLastNodeAtUserList(User* userList) {
    User* p = userList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next ); 
    return p;
}
Bank* getLastNodeAtBankList(Bank* bankList) {
    Bank* p = bankList;
    if ( p == NULL ) return NULL;
    for ( ; p->next ; p=p->next);
    return p;
}
/*
 * list push back
 */
AccountHistory* pushBackAtAccountHistoryList(AccountHistory** accountHistoryList,\
                                             char* _fromAccountNumber,\
                                             char* _toAccountNumber,\
                                             double _amount,\
                                             char* _date) {
    AccountHistory* newAccountHistory = getNewAccountHistroy(_fromAccountNumber,\
                                                             _toAccountNumber,\
                                                             _amount,\
                                                             _date);
    if ( *accountHistoryList == NULL ) {
        *accountHistoryList = newAccountHistory;
    } else {
        AccountHistory* lastNode = getLastNodeAtAccountHistoryList(*accountHistoryList);
        assert(lastNode != NULL);
        lastNode->next = newAccountHistory;
    }
    return newAccountHistory;
}
Account* pushBackAtAccountList(Account** accountList,\
                               char *_accountNumber,\
                               double _accountAmount) {
    Account* newAccount = getNewAccount(_accountNumber,\
                                        _accountAmount);
    if ( *accountList == NULL ) {
        *accountList = newAccount;
    } else {
        Account* lastNode = getLastNodeAtAccountList(*accountList);
        assert(lastNode != NULL);
        lastNode->next = newAccount;
    }
    return newAccount;
}
User* pushBackAtUserList(User** userList,\
                         char* _userName,\
                         double _loanAmount,\
                         double _loanLimit) {
    User* newUser = getNewUser(_userName,\
                               _loanAmount,\
                               _loanLimit);
    if ( *userList == NULL ) {
        *userList = newUser;
    } else {
        User* lastNode = getLastNodeAtUserList(*userList);
        assert(lastNode != NULL);
        lastNode->next = newUser;
    }
    return newUser;
}
Bank* pushBackAtBankList(Bank** bankList,\
                         char* _bankName,\
                         double _bankTotalAmount) {
    Bank* newBank = getNewBank(_bankName,\
                               _bankTotalAmount);
    if ( *bankList == NULL ) {
        *bankList = newBank;
    } else {
        Bank* lastNode = getLastNodeAtBankList(*bankList);
        assert(lastNode != NULL);
        lastNode->next = newBank;
    }
    return newBank;
}
/*
 * find node at list 
 */
Account* findAccountByAccountNumber(Account* accountList,\
                                    char* _accountNumber) {
    Account* p;
    for ( p=accountList ; p ; p=p->next ) 
        if ( !strcmp(p->accountNumber,_accountNumber) ) 
            return p;
    return NULL;
}
User* findUserByUserName(User* userList,\
                         char* _userName) {
    User* p;
    for ( p=userList ; p ; p=p->next ) 
        if ( !strcmp(p->userName,_userName) ) 
            return p;
    return NULL;
}
Bank* findBankByBankName(Bank* bankList,\
                         char* _bankName) {
    Bank* p;
    for ( p=bankList ; p ; p=p->next ) 
        if ( !strcmp(p->bankName,_bankName) ) 
            return p;
    return NULL;
}
/*
 * load file
 */
void loadFile(char *filename,Bank** bankList) {
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
                pushBackAtAccountList(&(up->accountList),\
                                      _accountNumber,\
                                      accountAmount);
            } else {
                User* user = pushBackAtUserList(&(bp->userList),\
                                                _userName,\
                                                BASE_LOAN_AMOUNT,\
                                                BASE_LOAN_LIMIT);
                pushBackAtAccountList(&(user->accountList),\
                                      _accountNumber,accountAmount);
            }
        } else {
            Bank* bp = pushBackAtBankList(bankList,_bankName,BASE_BANK_AMOUNT);
            User* user = pushBackAtUserList(&(bp->userList),_userName,\
                                            BASE_LOAN_AMOUNT,BASE_LOAN_LIMIT);
            pushBackAtAccountList(&(user->accountList),\
                                  _accountNumber,accountAmount);
        }
    }
    fclose(fp);
}

