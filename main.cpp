#include "BankData.h"
#include <iostream>

using namespace std;

int main() {
    size_t tableSize = 100000;
    BankData bankData(tableSize);

    // Chaining
    bankData.createAccount("123ABC", 1000);
    bankData.createAccount("456DEF", 1500);

    cout << "Balance for 123ABC: " << bankData.getBalance("123ABC") << endl;
    cout << "Balance for 456DEF: " << bankData.getBalance("456DEF") << endl;

    bankData.addTransaction("123ABC", 500);
    cout << "Balance for 123ABC after transaction: " << bankData.getBalance("123ABC") << endl;

    cout << "Account 123ABC exists: " << bankData.doesExist("123ABC") << endl;
    cout << "Database size: " << bankData.databaseSize() << endl;

    bankData.deleteAccount("123ABC");
    cout << "Account 123ABC exists after deletion: " << bankData.doesExist("123ABC") << endl;

    // Linear Probing
    bankData.createAccountLinearProbing("789GHI", 2000);
    cout << "Balance for 789GHI (Linear Probing): " << bankData.getBalance("789GHI") << endl;

    // Quadratic Probing
    bankData.createAccountQuadraticProbing("012JKL", 3000);
    cout << "Balance for 012JKL (Quadratic Probing): " << bankData.getBalance("012JKL") << endl;

    // Cubic Probing
    bankData.createAccountCubicProbing("345MNO", 4000);
    cout << "Balance for 345MNO (Cubic Probing): " << bankData.getBalance("345MNO") << endl;

    return 0;
}
