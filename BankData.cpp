#include "BankData.h"
#include <algorithm>
#include <functional>

// Constructor
BankData::BankData(size_t size) : tableSize(size), bankStorage2d(size), bankStorage1d(size), isOccupied(size, false) {}

// Hash function
int BankData::hash(string id) {
    hash<string> hash_fn;
    return hash_fn(id) % tableSize;
}

// Chaining strategy
void BankData::createAccount(string id, int count) {
    int hashValue = hash(id);
    for (auto &account : bankStorage2d[hashValue]) {
        if (account.id == id) {
            return; // Account already exists
        }
    }
    bankStorage2d[hashValue].emplace_back(id, count);
}

int BankData::getBalance(string id) {
    int hashValue = hash(id);
    for (auto &account : bankStorage2d[hashValue]) {
        if (account.id == id) {
            return account.balance;
        }
    }
    return -1; // Account not found
}

void BankData::addTransaction(string id, int count) {
    int hashValue = hash(id);
    for (auto &account : bankStorage2d[hashValue]) {
        if (account.id == id) {
            account.balance += count;
            return;
        }
    }
    bankStorage2d[hashValue].emplace_back(id, count); // Create account if not exists
}

bool BankData::doesExist(string id) {
    int hashValue = hash(id);
    for (auto &account : bankStorage2d[hashValue]) {
        if (account.id == id) {
            return true;
        }
    }
    return false;
}

int BankData::databaseSize() {
    int size = 0;
    for (const auto &bucket : bankStorage2d) {
        size += bucket.size();
    }
    return size;
}

bool BankData::deleteAccount(string id) {
    int hashValue = hash(id);
    auto &bucket = bankStorage2d[hashValue];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->id == id) {
            bucket.erase(it);
            return true;
        }
    }
    return false;
}

// Probing strategies
int BankData::linearProbe(int hashValue) {
    int i = 0;
    while (isOccupied[(hashValue + i) % tableSize]) {
        i++;
    }
    return (hashValue + i) % tableSize;
}

int BankData::quadraticProbe(int hashValue, int i) {
    return (hashValue + i * i) % tableSize;
}

int BankData::cubicProbe(int hashValue, int i) {
    return (hashValue + i * i * i) % tableSize;
}

void BankData::createAccountProbing(string id, int count, function<int(int, int)> probe) {
    int hashValue = hash(id);
    int i = 0;
    while (isOccupied[probe(hashValue, i)]) {
        i++;
    }
    int pos = probe(hashValue, i);
    bankStorage1d[pos] = Account(id, count);
    isOccupied[pos] = true;
}

void BankData::createAccountLinearProbing(string id, int count) {
    createAccountProbing(id, count, [this](int hashValue, int i) { return linearProbe(hashValue); });
}

void BankData::createAccountQuadraticProbing(string id, int count) {
    createAccountProbing(id, count, [this](int hashValue, int i) { return quadraticProbe(hashValue, i); });
}

void BankData::createAccountCubicProbing(string id, int count) {
    createAccountProbing(id, count, [this](int hashValue, int i) { return cubicProbe(hashValue, i); });
}

// Implement other methods similarly for probing strategies
