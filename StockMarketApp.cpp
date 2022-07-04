// Stock Market Applicaton
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Share;
class Account {
	int account_id;
	string name, family, username, password
		, nationalId;
	int accountNumber, iban;
	int balance, debt;
	int sumProperty;
	vector<Share> shares;
public:
	static int AccountCount;
	void SetAccountId(int account_id) { this->account_id = account_id; }
	void SetName(string name) { this->name = name; }
	void SetFamily(string family) { this->family = family; }
	void SetUsername(string username) { this->username = username; }
	void SetPassword(string password) { this->password = password; }
	void SetNationalId(string nationalId) { this->nationalId = nationalId; }
	int GetAccountId() { return account_id; }
	string GetName() { return name; }
	string GetFamily() { return family; }
	string GetNationalId() { return nationalId; }
	string GetUsername() { return username; }
	string GetPassword() { return password; }
    int GetBalance() { return balance; }
    int GetSumProp() { return sumProperty; }
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
void EditAccount(Account* edittedAccount) {
	cout << "\n\n\nPROFILE EDIT PAGE\n" << endl;
    cout << "Username: " << edittedAccount->GetUsername() << endl;
    cout << "New Username: ";
    string e_usr;
    cin >> e_usr;
    edittedAccount->SetUsername(e_usr);
    cout << endl;
    editpwd:
    cout << "Enter Current Password: ";
    string c_pwd;
    cin >> c_pwd;
    if (c_pwd == edittedAccount->GetPassword()) {
        cout << "\nPassword Must Contain SpecialCharacter, Digits, Upper and Lower Cases" << endl;
        cout << "New Password: ";
        string n_pwd;
        cin >> n_pwd;
        if (IsStrongPassword(n_pwd)) {
            confirm:
            cout << "Confirm Password: ";
		    string conf;
		    cin >> conf;
		    if (conf == n_pwd)
			    edittedAccount->SetPassword(n_pwd);
		    else {
			    cout << "\n\t Passwords Do Not Match\n" << endl;
			    goto confirm;
		    }   
        }
        else {
            cout << "\n\t Password Not Strong \n" << endl;
        }
    }
    else {
        cout << "\nCurrent Password Is Wrong\n" << endl;
        goto editpwd;
    }
    cout << "\n\t Edit Succeeded \n " << endl;



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
	cout << "\n\n\nLOGIN PAGE\n" << endl;
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
void CSVToArray(string) {

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
        //bool flag = true;
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
	cout << "-------------------------------------------------\nDashboard\n" << endl;
	cout << "\t\t\t\t Balance: " << LoggedInAcc.GetBalance() << endl;
	cout << "\t\t\t\t Stock Property Value: " << LoggedInAcc.GetSumProp() << "\n\n" << endl;
    cout << "\t1. Market            2.Wallet\n" << endl;
    cout << "\t3. Sell              4.Buy\n" << endl;
    cout << "\t5. Charge Account    6. Edit Profile\n" << endl;
    cout << "\t7. Sign Out" << endl;
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

	}
    case 4: {}
    case 5: {}
    case 6: {
        EditAccount(&LoggedInAcc);
        goto panel2;
    }
    case 7: {
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