#ifndef BANKDATA_H
#define BANKDATA_H

#include <vector>
#include <string>
#include <list>

using namespace std;

struct Account {
    string id;
    int balance;

    Account(string accountId, int initialBalance)
        : id(accountId), balance(initialBalance) {}
};

class BankData {
public:
    BankData(size_t size);
    void createAccount(string id, int count);
    vector<int> getTopK(int k);
    int getBalance(string id);
    void addTransaction(string id, int count);
    bool doesExist(string id);
    int databaseSize();
    int hash(string id);
    bool deleteAccount(string id);

    void createAccountLinearProbing(string id, int count);
    void createAccountQuadraticProbing(string id, int count);
    void createAccountCubicProbing(string id, int count);

private:
    size_t tableSize;
    vector<list<Account>> bankStorage2d; // For chaining
    vector<Account> bankStorage1d; // For probing
    vector<bool> isOccupied; // To check occupied slots for probing

    int linearProbe(int hashValue);
    int quadraticProbe(int hashValue, int i);
    int cubicProbe(int hashValue, int i);

    void createAccountProbing(string id, int count, function<int(int, int)> probe);
};

#endif
