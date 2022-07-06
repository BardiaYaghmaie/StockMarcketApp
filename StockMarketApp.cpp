// Stock Market Applicaton
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
#include <utility>
using namespace std;

class Share;
class Account {
	int account_id;
	string name, family, username, password
		, nationalId;
	int accountNumber, iban;
	int balance, debt;
	int sumProperty;
public:
	vector< pair<Share*, float> > shares;
	static int AccountCount;
	void SetAccountId(int account_id) { this->account_id = account_id; }
	void SetName(string name) { this->name = name; }
	void SetFamily(string family) { this->family = family; }
	void SetUsername(string username) { this->username = username; }
	void SetPassword(string password) { this->password = password; }
	void SetNationalId(string nationalId) { this->nationalId = nationalId; }
    void SetBalance(int balance) { this->balance = balance; }
	int GetAccountId() { return account_id; }
	string GetName() { return name; }
	string GetFamily() { return family; }
	string GetNationalId() { return nationalId; }
	string GetUsername() { return username; }
	string GetPassword() { return password; }
    int GetBalance() { return balance; }
    int GetSumProp() { return sumProperty; }
	friend class Share;    
};
int Account::AccountCount = 0;
vector<Account*> Accounts;
class Share {
private:
	string title, symbol;
	double value;
	long double marketCapacity;
	int id;

public:
	void SetTitle(string title) { this->title = title; }
	void SetSymbol(string symbol) { this->symbol = symbol; }
	void SetValue(double value) { this->value = value; }
	void SetMarketCapacity(double marketCapacity) { this->marketCapacity = marketCapacity; }
	string GetTitle() { return title; }
	string GetSymbol() { return symbol; }
	double GetValue() { return this->value; }
	double GetMarketCapacity() { return marketCapacity; }
	int GetId() { return this->id; }
	void SetId(int id) { this->id = id; }
};

Share* Parse(string text) {
	int index = text.find(",");

	Share* share = new Share();
	string id_string = text.substr(0, index);
	share->SetId(stoi(id_string));
	text.erase(0, index + 1);



	index = text.find(",");
	string symbol = text.substr(0, index);
	share->SetSymbol(symbol);
	text.erase(0, index + 1);




	string title;
	int index_first_double_quote = text.find("\"");
	index = text.find(",");
	string temp = text;
	int index_second_double_quote = -1;

	if (index_first_double_quote != -1)
	{
		temp.erase(index_first_double_quote, index_first_double_quote + 1);
		index_second_double_quote = temp.find("\"");
		index_second_double_quote++;

	}

	if (index_first_double_quote != -1 &&
		index_second_double_quote != -1
		&& index > index_first_double_quote && index < index_second_double_quote)
	{
		title = text.substr(index_first_double_quote + 1, index_second_double_quote - 1);
		share->SetTitle(title);
		text.erase(index_first_double_quote, index_second_double_quote + 2);

	}
	else {
		title = text.substr(0, index);
		share->SetTitle(title);
		text.erase(0, index + 1);
	}





	index = text.find(",");
	string value_string = text.substr(0, index);
	long double x = stold(value_string);
	share->SetValue(x);
	text.erase(0, index + 1);


	index = text.find(",");
	string marketCapacity = text.substr(0, index);
	share->SetMarketCapacity(stold(marketCapacity));
	text.erase(0, index + 1);
    


	return share;
}
const string FileName = "stock_market_data.csv";
vector<Share*> ReadSharesFromFile(string fileName) {
	vector<Share*> result;
	ifstream input(fileName, ios::in);
	if (!input)
	{
		cout << "can not open the file";
		throw "error";
	}
	else {
		string text;
		int counter = 0;
		while (getline(input, text))
		{
			if (counter > 0)
			{
				Share* share = Parse(text);
				result.push_back(share);
			}
			counter++;
		}
		return result;
	}
}
vector<Share*> SharesInFile = ReadSharesFromFile(FileName);

Share* FindShareBySymbolInMarket(string symbol){
    for (int i = 0; i < SharesInFile.size(); i++) {
        if (symbol == SharesInFile.at(i)->GetSymbol()) {
            return SharesInFile.at(i);
        }
    }
    return NULL;
}
void ShowWallet();
void WriteShareToFile(string fileName, Share share) {
	fstream output(fileName, ios::app);
	if (!output)
	{
		cout << "can not write to file";
	}
	else {
		output << share.GetId() << "#" << share.GetSymbol() << "#" << share.GetTitle() << "#" << share.GetValue()
			<< "#" << share.GetMarketCapacity() << "\n";
		
	}
}
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
    Accounts.at(edittedAccount->GetAccountId())->SetUsername(e_usr);
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
                Accounts.at(edittedAccount->GetAccountId())->SetPassword(n_pwd);
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
vector<Share*> market = ReadSharesFromFile(FileName);
float CalculateSumProperty(Account* acc){
    float result = 0;
    for (int i = 0; i < market.size(); i++)
    {
        result +=  acc->shares.at(i).first->GetValue() * acc->shares.at(i).second;
    }
    return result;
    
}
pair<Share*, float> FindShareBySymbolInWallet(Account* acc, string symbol) {
    pair<Share*, float> def;
    def.first = nullptr;
    def.second = 0;
    for (int i = 0; i < acc->shares.size(); i++) {
        if (symbol == acc->shares.at(i).first->GetSymbol()) {
            pair<Share*, float> curr;
            curr.first = acc->shares.at(i).first;
            curr.second = acc->shares.at(i).second;
            return curr;
        }
    }
    return def;
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
    for (int i = 0; i < market.size(); i++) {
        pair<Share*, float> curr;
        curr.first =market.at(i);
        curr.second = 0;
        LoggedInAcc.shares.push_back(curr);
            
    }
	cout << "\n\tWelcome " << LoggedInAcc.GetUsername() << " :)\n" << endl;
panel2:
	cout << "-------------------------------------------------\nDashboard\n" << endl;
	cout << "\t\t\t\t Balance: " << LoggedInAcc.GetBalance() << endl;
	cout << "\t\t\t\t Stock Property Value: " << CalculateSumProperty(&LoggedInAcc) << "\n\n" << endl;
    cout << "\t1. Market            2.Wallet\n" << endl;
    cout << "\t3. Sell              4.Buy\n" << endl;
    cout << "\t5. Charge Account    6. Edit Profile\n" << endl;
    cout << "\t7. Sign Out" << endl;
	int cmd;
	cin >> cmd;
	switch (cmd) {
	case 1: {

		cout << "\n\t MARKET \n" << endl;
        cout << "  #    Symbol        Title        Value    MarketCap\n " << endl;
        for (int i = 0; i < market.size(); i++) {
            cout << "  " << market[i]->GetId() <<"     "<< market[i]->GetSymbol()<<"     " << market[i]->GetTitle()<<"     " << market[i]->GetValue()<<"     " << market[i]->GetMarketCapacity()<<"     " << endl;
        }
		goto panel2;

	}
	case 2: {
    cout << "\n\t WALLET \n" << endl;
        int cnt = 0;
        for (int i = 0; i < market.size(); i++) {
            if (LoggedInAcc.shares.at(i).second != 0) {
                cout << "[*]\n\t" << LoggedInAcc.shares.at(i).second << LoggedInAcc.shares.at(i).first->GetSymbol() << "     Share Value: "
                << LoggedInAcc.shares.at(i).first->GetValue() * LoggedInAcc.shares.at(i).second << "\n\n";
                cnt++;
            }
        }
        if (cnt == 0) {
            cout << "\n\tWALLET IS EMPTY\n" << endl;
        }
		goto panel2;
    }    
	case 3: {
        cout << "\n\tSELL\n" << endl;
        cout << "Which Share of Yours You Want To Sell: ";
        string sym;
        cin >> sym;
        cout << "Share Unit: ";
        float unit;
        cin >> unit;
        if (unit <= FindShareBySymbolInWallet(&LoggedInAcc, sym).second) {
            for (int i = 0; i < LoggedInAcc.shares.size(); i++) {
                if (LoggedInAcc.shares.at(i).first->GetSymbol() == sym) {
                    LoggedInAcc.shares.at(i).second -= unit;
                    LoggedInAcc.SetBalance(LoggedInAcc.GetBalance() + (unit * LoggedInAcc.shares.at(i).first->GetValue()));
                    break;
                }
            }

        }


        goto panel2;
	}
    case 4: {
        
        cout << "\n\t BUY \n" << endl;
        buy:
        cout << "Share On The Market List You Want To Buy (Symbol): ";
        string sym;
        cin >> sym;
        cout << endl;
        if (FindShareBySymbolInMarket(sym)){
            cout << "Share Unit (0.001 ~ 100): ";
            float unit;
            cin >> unit;
            if (unit * FindShareBySymbolInMarket(sym)->GetValue() < LoggedInAcc.GetBalance()) {
                pair<Share*, float> curr;
                curr.first = FindShareBySymbolInMarket(sym);
                curr.second = unit;
                for (int i = 0; i < LoggedInAcc.shares.size(); i++) {
                    if (LoggedInAcc.shares.at(i).first->GetSymbol() == sym){
                        LoggedInAcc.shares.at(i).second += unit;
                        LoggedInAcc.SetBalance(LoggedInAcc.GetBalance() - unit*LoggedInAcc.shares.at(i).first->GetValue());
                        break;
                    }
        
                }
                cout << "\n\tSuccesful Buy!\n" << endl;
            }
            else {
                cout << "\n\tNot Enough Balane To Buy This Share\n" << endl;
                goto panel2;
            }

        }
        else
            goto buy;
		goto panel2;
        }
    case 5: {
        cout << "\n\t ACCOUNT CHARGING \n" << endl;
        cout << "How Much You Wanna Charge Your Account (In Dollars): ";
        int chargingAmount;
        cin >> chargingAmount;
        LoggedInAcc.SetBalance(LoggedInAcc.GetBalance() + chargingAmount);
        cout << "\n\t Account Charged " << LoggedInAcc.GetBalance() << "$\n" << endl;
		goto panel2;
    }
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

