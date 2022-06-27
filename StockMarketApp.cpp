#include <bits/stdc++.h>
using namespace std;

class Share;
class Account {
    string name, family;
    int nationalId;
    int accountNumber, iban;
    int balance, debt;
    int sumProperty;
    vector<Share> shares;
    
};
class Share {
    string title, symbol;
    int value;
    int marketCapacity;
    
};
