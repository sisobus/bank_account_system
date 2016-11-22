#include "a.h"
int main(int argc,char* argv[]) {
    Bank* bankList;
    loadFile(LOAD_FILENAME,&bankList);

    int state = 1, select;
    double amount;
    char buf[MAX_BUFFER_SIZE]={};
    Bank* bp = NULL;
    User* up = NULL;
    Account* ap = NULL;
    while ( state != 13 ) {
        if ( state == 1 ) {
            printMenuScene1(bankList);
            printMenuMessage(1);
            scanf("%d",&select);
            if ( select == 1 ) {
                state = 11;
            } else if ( select == 2 ) {
                state = 12;
            } else if ( select == 3 ) {
                state = 13;
                puts("bye~");
            } else {
                printErrorMessage(-1);
            }
        } else if ( state == 11 ) {
            printMenuScene1_1(bankList);
            printMenuMessage(1);
            scanf("%d",&select);
            bp = findBankByBankId(bankList,select);
            if ( bp ) {
                state = 2;
                printf("you choose %s\n",bp->bankName);
            } else {
                printErrorMessage(-2);
            }
        } else if ( state == 12 ) {
            printMenuScene1_1(bankList);
            printMenuMessage(1);
            scanf("%d",&select);
            bp = findBankByBankId(bankList,select);
            if ( bp ) {
                state = 1;
                printBankUserAccountInformation(bp);
            } else {
                printErrorMessage(-2);
            }
        } else if ( state == 13 ) {
            break;
        } else if ( state == 2 ) {
            printMenuScene2(bp->userList);
            printMenuMessage(1);
            scanf("%d",&select);
            if ( select == 1 ) {
                state = 21;
            } else if ( select == 2 ) {
                state = 22;
            } else if ( select == 3 ) {
                state = 23;
            } else {
                printErrorMessage(-1);
            }
        } else if ( state == 21 ) {
            printUserList(bp->userList);
            printMenuMessage(2);
            scanf("%s",buf);
            up = findUserByUserName(bp->userList,buf);
            if ( up ) {
                printf("you choose %s\n",up->userName);
                state = 3;
            } else {
                printErrorMessage(-3);
            }
        } else if ( state == 22 ) {
            printUserList(bp->userList);
            printMenuMessage(2);
            scanf("%s",buf);
            up = findUserByUserName(bp->userList,buf);
            if ( up ) {
                printErrorMessage(-4);
            } else {
                up = pushBackAtUserList(&bp->userList,buf,0,BASE_LOAN_LIMIT,bp);
                printUserList(bp->userList);
                state = 3;
            }
        } else if ( state == 23 ) {
            state = 1;
            bp = NULL;
            continue;
        } else if ( state == 3 ) {
            printMenuScene3(up->accountList);
            printMenuMessage(1);
            scanf("%d",&select);
            if ( select == 1 ) {
                state = 31;
            } else if ( select == 2 ) {
                state = 32;
            } else if ( select == 3 ) {
                state = 33;
            } else if ( select == 4 ) {
                state = 34;
            } else if ( select == 5 ) {
                state = 35;
            } else if ( select == 6 ) {
                state = 36;
            } else if ( select == 7 ) {
                state = 37;
            } else if ( select == 8 ) {
                state = 38;
            } else {
                printErrorMessage(-1);
            }
        } else if ( state == 31 ) {
            printUserAccountInformation(up);
            printMenuMessage(3);
            scanf("%s",buf);
            ap = findAccountByAccountNumber(up->accountList,buf);
            if ( ap ) {
                printErrorMessage(-5);
            } else {
                ap = pushBackAtAccountList(&up->accountList,buf,0,up);
                pushBackAtAccountHistoryList(&(ap->accountHistoryList),"registration",buf,0,ap);
                printUserAccountInformation(up);
                state = 3;
            }
        } else if ( state == 32 ) {
            printUserAccountInformation(up);
            printMenuMessage(3);
            scanf("%s",buf);
            ap = findAccountByAccountNumber(up->accountList,buf);
            if ( ap ) {
                printMenuMessage(4);
                scanf("%lf",&amount);
                while ( amount == 0 ) {
                    printErrorMessage(-8);
                    printMenuMessage(4);
                    scanf("%lf",&amount);
                }
                int r = updateAccountAmount(ap,amount);
                if ( r ) {
                    pushBackAtAccountHistoryList(&ap->accountHistoryList,\
                                                 "deposits and withdrawals",\
                                                 ap->accountNumber,amount,ap);
                    PRINT_DOUBLE_LINE();
                    printAccount(ap);
                    PRINT_DOUBLE_LINE();
                    state = 3;
                } else {
                    printErrorMessage(-7);
                    state = 3;
                }
            } else {
                printErrorMessage(-6);
            }
        } else if ( state == 33 ) {
            printUserAccountInformation(up);
            printMenuMessage(5);
            scanf("%s",buf);
            Account* fromAccount = findAccountByAccountNumber(up->accountList,buf);
            if ( fromAccount ) {
            } else {
                printErrorMessage(-6);
                continue;
            }
            printAllUserAccountInformation(bankList);
            printMenuMessage(6);
            scanf("%s",buf);
            Account* toAccount = findAccountByAccountNumberAtAllBankList(bankList,buf);
            if ( toAccount ) {
                printMenuMessage(4);
                scanf("%lf",&amount);
                while ( amount <= 0 ) {
                    printErrorMessage(-9);
                    printMenuMessage(4);
                    scanf("%lf",&amount);
                }
                int r = sendAmountFromUserToUser(fromAccount,toAccount,amount);
                if ( r ) {
                    pushBackAtAccountHistoryList(&fromAccount->accountHistoryList,\
                                                 fromAccount->accountNumber,\
                                                 toAccount->accountNumber,\
                                                 -amount,fromAccount);
                    pushBackAtAccountHistoryList(&toAccount->accountHistoryList,\
                                                 fromAccount->accountNumber,\
                                                 toAccount->accountNumber,\
                                                 amount,fromAccount);
                    PRINT_DOUBLE_LINE();
                    printAccount(fromAccount);
                    PRINT_DOUBLE_LINE();
                    PRINT_DOUBLE_LINE();
                    printAccount(toAccount);
                    PRINT_DOUBLE_LINE();
                    state = 3;
                } else {
                    printErrorMessage(-10);
                }
            } else {
                printErrorMessage(-6);
                continue;
            }
        } else if ( state == 34 ) {
            printBankLoanLimit(bp);
            printUserAccountInformation(up);
            printMenuMessage(3);
            scanf("%s",buf);
            ap = findAccountByAccountNumber(up->accountList,buf);
            if ( ap ) {
                if ( ap->accountAmount <= 0 ) {
                    printErrorMessage(-11);
                    state = 3;
                }
                printMenuMessage(4);
                scanf("%lf",&amount);
                int r = loanAmountFromBank(ap,bp,amount);
                if ( r ) {
                    pushBackAtAccountHistoryList(&ap->accountHistoryList,\
                                                 "loan",ap->accountNumber,amount,ap);
                    PRINT_DOUBLE_LINE();
                    printAccount(ap);
                    PRINT_DOUBLE_LINE();
                    printBankLoanLimit(bp);
                    state = 3;
                } else {
                    printErrorMessage(-12);
                    state = 3;
                }
            } else {
                printErrorMessage(-6);
            }
        } else if ( state == 35 ) {
            printUserAccountInformation(up);
            printMenuMessage(3);
            scanf("%s",buf);
            ap = findAccountByAccountNumber(up->accountList,buf);
            if ( ap ) {
                PRINT_DOUBLE_LINE();
                printAccount(ap);
                puts("");
                printAccountHistoryListReverse(ap->accountHistoryList);
                PRINT_DOUBLE_LINE();
                state = 3;
            } else {
                printErrorMessage(-6);
            }
        } else if ( state == 36 ) {
            printUserAccountInformation(up);
            printBankLoanLimit(bp);
            printMenuMessage(3);
            scanf("%s",buf);
            ap = findAccountByAccountNumber(up->accountList,buf);
            if ( ap ) {
                int r = accountTermination(ap,bp);
                if ( r == -13 ) {
                    printErrorMessage(-13);
                } else if ( r == -14 ) {
                    printErrorMessage(-14);
                } else if ( r == 2 ) {
                    state = 2;
                } else if ( r == 3 ) {
                    state = 3;
                } else {
                    /* never */
                }
            } else {
                printErrorMessage(-6);
            }
        } else if ( state == 37 ) {
            printUserAccountInformation(up);
            state = 3;
        } else if ( state == 38 ) {
            up = NULL;
            state = 2;
            continue;
        }
    }
    return 0;
}
