#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 200
#define MIN_BALANCE 500.0
#define DAILY_WITHDRAWAL_LIMIT 20000.0

// ---------------- ACCOUNT STRUCTURE ----------------
typedef struct
{
    int accountNumber;
    char name[50];
    int pin;
    float balance;

    float withdrawnToday;
    int withdrawalDay;
} Account;


// ---------------- TRANSACTION STRUCTURE ----------------
typedef struct
{
    int transactionID;
    int accountNumber;
    char type[20];       // Deposit or Withdrawal
    float amount;
    char date[20];
} Transaction;


// ---------------- GLOBAL ARRAYS ----------------
Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS];

int accountCount = 0;
int transactionCount = 0;
int nextTransactionID = 1;


// ====================================================
//                SEARCHING FUNCTIONS
// ====================================================

// Linear Search for Account
int searchAccount(int accountNumber)
{
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].accountNumber == accountNumber)
        {
            return i;
        }
    }

    return -1;
}


// Linear Search for Transaction ID
int searchTransactionByID(int id)
{
    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].transactionID == id)
        {
            return i;
        }
    }

    return -1;
}


// ====================================================
//                TRANSACTION FUNCTIONS
// ====================================================

void addTransaction(int accountNumber, char type[], float amount)
{
    if (transactionCount >= MAX_TRANSACTIONS)
    {
        printf("\nTransaction storage is full!\n");
        return;
    }

    Transaction t;

    t.transactionID = nextTransactionID++;
    t.accountNumber = accountNumber;

    strcpy(t.type, type);

    t.amount = amount;

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", t.date);

    transactions[transactionCount] = t;
    transactionCount++;
}


// ====================================================
//             MODULE 1: CREATE ACCOUNT
// ====================================================

void createAccount()
{
    if (accountCount >= MAX_ACCOUNTS)
    {
        printf("\nMaximum account limit reached!\n");
        return;
    }

    Account newAccount;

    printf("\n========== CREATE ACCOUNT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &newAccount.accountNumber);

    // Check duplicate account number
    if (searchAccount(newAccount.accountNumber) != -1)
    {
        printf("\nAccount already exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", newAccount.name);

    printf("Create 4-digit PIN: ");
    scanf("%d", &newAccount.pin);

    printf("Enter Initial Balance: ");
    scanf("%f", &newAccount.balance);

    if (newAccount.balance < MIN_BALANCE)
    {
        printf("\nMinimum balance must be Rs. %.2f\n", MIN_BALANCE);
        return;
    }

    newAccount.withdrawnToday = 0;
    newAccount.withdrawalDay = 0;

    accounts[accountCount] = newAccount;
    accountCount++;

    printf("\nAccount created successfully!\n");
}


// ====================================================
//             VIEW ACCOUNT DETAILS
// ====================================================

void viewAccountDetails()
{
    int accountNumber;

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNumber);

    int index = searchAccount(accountNumber);

    if (index == -1)
    {
        printf("\nAccount not found!\n");
        return;
    }

    printf("\n========== ACCOUNT DETAILS ==========\n");

    printf("Account Number : %d\n",
           accounts[index].accountNumber);

    printf("Name           : %s\n",
           accounts[index].name);

    printf("Balance        : Rs. %.2f\n",
           accounts[index].balance);
}


// ====================================================
//             UPDATE ACCOUNT DETAILS
// ====================================================

void updateAccount()
{
    int accountNumber;
    int pin;

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNumber);

    int index = searchAccount(accountNumber);

    if (index == -1)
    {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[index].pin != pin)
    {
        printf("\nIncorrect PIN!\n");
        return;
    }

    int choice;

    printf("\n1. Change Name\n");
    printf("2. Change PIN\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter New Name: ");
            scanf(" %[^\n]", accounts[index].name);

            printf("\nName updated successfully!\n");
            break;

        case 2:
            printf("Enter New PIN: ");
            scanf("%d", &accounts[index].pin);

            printf("\nPIN updated successfully!\n");
            break;

        default:
            printf("\nInvalid choice!\n");
    }
}


// ====================================================
//        MODULE 2: BALANCE INQUIRY
// ====================================================

void checkBalance()
{
    int accountNumber;
    int pin;

    printf("\nEnter Account Number: ");
    scanf("%d", &accountNumber);

    int index = searchAccount(accountNumber);

    if (index == -1)
    {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[index].pin != pin)
    {
        printf("\nIncorrect PIN!\n");
        return;
    }

    printf("\nCurrent Balance: Rs. %.2f\n",
           accounts[index].balance);
}


// ====================================================
//                    DEPOSIT
// ====================================================

void depositMoney()
{
    int accountNumber;
    int pin;
    float amount;

    printf("\n========== DEPOSIT MONEY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    int index = searchAccount(accountNumber);

    if (index == -1)
    {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[index].pin != pin)
    {
        printf("\nIncorrect PIN!\n");
        return;
    }

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\nInvalid amount!\n");
        return;
    }

    accounts[index].balance += amount;

    addTransaction(
        accounts[index].accountNumber,
        "Deposit",
        amount
    );

    printf("\nDeposit successful!\n");

    printf("Updated Balance: Rs. %.2f\n",
           accounts[index].balance);
}


// ====================================================
//        MODULE 3: CASH WITHDRAWAL
// ====================================================

void withdrawMoney()
{
    int accountNumber;
    int pin;
    float amount;
    int day;

    printf("\n========== CASH WITHDRAWAL ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    int index = searchAccount(accountNumber);

    if (index == -1)
    {
        printf("\nAccount not found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[index].pin != pin)
    {
        printf("\nIncorrect PIN!\n");
        return;
    }

    printf("Enter Today's Day Number: ");
    scanf("%d", &day);

    // Reset daily withdrawal if day changes
    if (accounts[index].withdrawalDay != day)
    {
        accounts[index].withdrawalDay = day;
        accounts[index].withdrawnToday = 0;
    }

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\nInvalid amount!\n");
        return;
    }

    // Check sufficient balance
    if (accounts[index].balance - amount < MIN_BALANCE)
    {
        printf("\nWithdrawal failed!\n");

        printf("Minimum balance of Rs. %.2f must remain.\n",
               MIN_BALANCE);

        return;
    }

    // Check daily limit
    if (accounts[index].withdrawnToday + amount >
        DAILY_WITHDRAWAL_LIMIT)
    {
        printf("\nDaily withdrawal limit exceeded!\n");

        printf("Daily Limit: Rs. %.2f\n",
               DAILY_WITHDRAWAL_LIMIT);

        return;
    }

    accounts[index].balance -= amount;

    accounts[index].withdrawnToday += amount;

    addTransaction(
        accounts[index].accountNumber,
        "Withdrawal",
        amount
    );

    printf("\nWithdrawal successful!\n");

    printf("Remaining Balance: Rs. %.2f\n",
           accounts[index].balance);
}


// ====================================================
//           MODULE 4: TRANSACTION HISTORY
// ====================================================

void displayTransactions()
{
    if (transactionCount == 0)
    {
        printf("\nNo transactions available!\n");
        return;
    }

    printf("\n========================================================\n");

    printf("ID\tAccount\t\tType\t\tAmount\t\tDate\n");

    printf("========================================================\n");

    for (int i = 0; i < transactionCount; i++)
    {
        printf("%d\t%d\t\t%s\t\t%.2f\t\t%s\n",

               transactions[i].transactionID,
               transactions[i].accountNumber,
               transactions[i].type,
               transactions[i].amount,
               transactions[i].date);
    }
}


// ====================================================
//          SEARCH TRANSACTION BY TYPE
// ====================================================

void searchTransactionByType()
{
    char type[20];
    int found = 0;

    printf("\nEnter Transaction Type (Deposit/Withdrawal): ");

    scanf("%s", type);

    printf("\nTransactions of type: %s\n", type);

    for (int i = 0; i < transactionCount; i++)
    {
        if (strcmp(transactions[i].type, type) == 0)
        {
            printf("\nTransaction ID: %d",
                   transactions[i].transactionID);

            printf("\nAccount Number: %d",
                   transactions[i].accountNumber);

            printf("\nAmount: Rs. %.2f",
                   transactions[i].amount);

            printf("\nDate: %s\n",
                   transactions[i].date);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo transaction found!\n");
    }
}


// ====================================================
//       SEARCH TRANSACTION BY TRANSACTION ID
// ====================================================

void searchTransaction()
{
    int id;

    printf("\nEnter Transaction ID: ");
    scanf("%d", &id);

    int index = searchTransactionByID(id);

    if (index == -1)
    {
        printf("\nTransaction not found!\n");
        return;
    }

    printf("\n========== TRANSACTION FOUND ==========\n");

    printf("Transaction ID : %d\n",
           transactions[index].transactionID);

    printf("Account Number: %d\n",
           transactions[index].accountNumber);

    printf("Type           : %s\n",
           transactions[index].type);

    printf("Amount         : Rs. %.2f\n",
           transactions[index].amount);

    printf("Date           : %s\n",
           transactions[index].date);
}


// ====================================================
//          SORT BY AMOUNT - BUBBLE SORT
// ====================================================

void sortByAmount()
{
    if (transactionCount == 0)
    {
        printf("\nNo transactions available!\n");
        return;
    }

    Transaction temp;

    for (int i = 0; i < transactionCount - 1; i++)
    {
        for (int j = 0; j < transactionCount - i - 1; j++)
        {
            if (transactions[j].amount >
                transactions[j + 1].amount)
            {
                temp = transactions[j];

                transactions[j] =
                    transactions[j + 1];

                transactions[j + 1] = temp;
            }
        }
    }

    printf("\nTransactions sorted by amount successfully!\n");

    displayTransactions();
}


// ====================================================
//                     MAIN FUNCTION
// ====================================================

int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("========================================\n");
        printf("         ATM MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Create Account\n");
        printf("2. View Account Details\n");
        printf("3. Update Account Details\n");
        printf("4. Balance Inquiry\n");
        printf("5. Deposit Money\n");
        printf("6. Withdraw Money\n");
        printf("7. Display Transaction History\n");
        printf("8. Search Transaction by ID\n");
        printf("9. Search Transaction by Type\n");
        printf("10. Sort Transactions by Amount\n");
        printf("0. Exit\n");

        printf("========================================\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                viewAccountDetails();
                break;

            case 3:
                updateAccount();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                depositMoney();
                break;

            case 6:
                withdrawMoney();
                break;

            case 7:
                displayTransactions();
                break;

            case 8:
                searchTransaction();
                break;

            case 9:
                searchTransactionByType();
                break;

            case 10:
                sortByAmount();
                break;

            case 0:
                printf("\nThank you for using ATM Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}