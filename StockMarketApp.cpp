// Stock Market Applicaton
#include <bits/stdc++.h>
using namespace std;

class Share;
class Account {
    int account_id;
    string name, family, username, password
    ,nationalId;
    int accountNumber, iban;
    int balance, debt;
    int sumProperty;
    vector<Share> shares;
public:
    static int AccountCount;
    void SetAccountId(int account_id) { this->account_id = account_id; }
    void SetName(string name) {this->name = name;}
    void SetFamily(string family) {this->family = family;}
    void SetUsername(string username) {this->username = username;}
    void SetPassword(string password) {this->password = password;}
    void SetNationalId(string nationalId) {this->nationalId = nationalId; }
    int GetAccountId() {return account_id; }
    string GetName() {return name; }
    string GetFamily() {return family;}
    string GetNationalId() {return nationalId; }
    string GetUsername() {return username; }
    string GetPassword() {return password; }
    //friend class Share;    
};
int Account::AccountCount = 0;
vector<Account*> Accounts;
class Share {
    string title, symbol;
    int value;
    int marketCapacity;
    
};
bool IsStrongPassword(string input) { 
    int n = input.length();
    // Checking lower alphabet in string
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, hasSpecialChar = false;
    string normalChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
    for (int i = 0; i < n; i++) {
        if (islower(input[i]))
            hasLower = true;
        if (isupper(input[i]))
            hasUpper = true;
        if (isdigit(input[i]))
            hasDigit = true;
        size_t special = input.find_first_not_of(normalChars);
        if (special != string::npos)
            hasSpecialChar = true;
    }
    if (hasLower && hasUpper && hasDigit && hasSpecialChar)
        return true;

    return false;
    


}
void RegisterAccount() {
	cout << "\nREGISTERATION PAGE\n" << endl;
	Account* tempAccount = new Account();
	cout << "Name: ";
	string name;
	cin >> name;
	tempAccount->SetName(name);
    cout << "Family: ";
	string family;
	cin >> family;
	tempAccount->SetFamily(family);
    setnid:
    cout << "National ID: ";
	string nid;
	cin >> nid;
    if (nid.length() == 10)
	    tempAccount->SetNationalId(nid);
    else {
        cout << "\n\tNational ID Must Have 10 Digits!\n" << endl;
        goto setnid;
    }
    cout << "Username: ";
	string usr;
	cin >> usr;
	tempAccount->SetUsername(usr);
    passwordset:
    cout << "\nPassword Must Contain SpecialCharacter, Digits, Upper and Lower Cases" << endl;
	cout << "Password: ";
	string pass;
	cin >> pass;
    if (IsStrongPassword(pass)) {
        confirm:
        cout << "\nConfirm Password: ";
        string conf;
        cin >> conf;
        if (conf == pass)
            tempAccount->SetPassword(pass);
        else {
            cout << "\n\t Passwords Do Not Match\n" << endl;
            goto confirm;

        }
    }
    else {
        cout << "\n\tInvalid Password\n" << endl;
        goto passwordset;
    }
	tempAccount->SetAccountId(Account::AccountCount);
	cout << "Register Done!" << endl;
	Account::AccountCount++;

	Accounts.push_back(tempAccount);
}
Account* FindUserByUsernameAndPassword(string username, string password) {
	for (int i = 0; i < Accounts.size(); i++)
	{
		if (Accounts.at(i)->GetUsername() == username && Accounts.at(i)->GetPassword() == password)
		{
			return Accounts[i];
		}
	}
	return NULL;
}
Account LoggedInAcc;
bool LoginAccount() {
	cout << "\nLOGIN PAGE\n" << endl;
	string username, password;
	cout << "Username : ";
	cin >> username;
	cout << "Password : ";
	cin >> password;
	Account* acc = FindUserByUsernameAndPassword(username, password);
	if (acc)     // this means that there is at least one user with the given details . so the user can log in
	{
		//i should write something here that logs the user in
		 // so i go up and define a global varibale named : "loggedInUser" which is of type User*;
		LoggedInAcc.SetAccountId(acc->GetAccountId());
		LoggedInAcc.SetUsername(acc->GetUsername());
		LoggedInAcc.SetPassword(acc->GetPassword());
		//cout << "The user with id : " << LoggedInUser.GetUserId() << " and username : " << LoggedInUser.GetUsername() << " is logged in now !" << endl;
		cout << endl;
        return true;
	}
	else {
		cout << "\n\tLogin Failed\n" << endl;
		return false;
	}

}


int main() {
    firstpage:
	cout << "\nBARILEX (Stock Market Application)\n" << endl;
	cout << "\t1. Sign Up\t2. Login" << endl;
	int command;
	cin >> command;
	switch (command) {
	case 1:
		RegisterAccount();
		goto login;

	case 2: {
	login:
		bool flag = LoginAccount();
		if (flag)
		{
			goto panel;

		}
		else {
			goto firstpage;
		}

	}
	default:
		cout << "Error: Unknown command!!";
		goto firstpage;

	}
panel:
	cout << "\n\tWelcome " << LoggedInAcc.GetUsername() << " :)\n" << endl;
panel2:
	cout << "User Panel\n" << endl;
	cout << "\t1. Register Article        2. See List of Articles        3. Sign Out" << endl;
	int cmd;
	cin >> cmd;
	switch (cmd) {
	case 1: {

		//RegisterArticle();
		goto panel2;

	}
	case 2:
		//ShowAllArticles();
		goto panel2;
	case 3: {
		LoggedInAcc.SetPassword("");
		LoggedInAcc.SetAccountId(-1);
		LoggedInAcc.SetUsername("");
		goto firstpage;
	}

	default:
		goto panel;
	}


    return 0;
}