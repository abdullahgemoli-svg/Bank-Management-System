
#include<string>
#include <iostream>
#include <cctype>
#include<vector>
#include<iomanip>
#include <fstream>
using namespace std;
  //Progict Bank frast One 
/*const string ClientsFileName = "MyFileClients.txt";
void ShowMainMenue();
struct stClinet
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};
enum enMainMnueoptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindCLient = 5, eExit = 6
};
vector <string> SplitString(string S9, string Delim)

{
	vector <string> vString;

	short pos = 0;
	string sWord;
	while ((pos = S9.find(Delim)) != std::string::npos)
	{
		sWord = S9.substr(0, pos);
		if (sWord != "")
		{

			vString.push_back(sWord);
		}


		S9.erase(0, pos + Delim.length());

	}

	if (S9 != "")
	{

		vString.push_back(S9);

	}
	return vString;
}
string CounvertRecordToLine(stClinet Clinet, string Seperator = "#//#")
{
	string stClinetRecord = "";

	stClinetRecord += Clinet.AccountNumber + Seperator;
	stClinetRecord += Clinet.PinCode + Seperator;
	stClinetRecord += Clinet.Name + Seperator;
	stClinetRecord += Clinet.Phone + Seperator;
	stClinetRecord += to_string(Clinet.AccountBalance);
	return stClinetRecord;
}
stClinet CounvertLineToRecord(string Line, string Seperator = "#//#")
{
	stClinet Clinet;
	vector <string> vClinetData;

	vClinetData = SplitString(Line, Seperator);
	if (vClinetData.size() != 5)
	{
		cout << "Invalid line format: " << Line << endl;
		return Clinet;
	}
	Clinet.AccountNumber = vClinetData[0];
	Clinet.PinCode = vClinetData[1];
	Clinet.Name = vClinetData[2];
	Clinet.Phone = vClinetData[3];
	Clinet.AccountBalance = stod(vClinetData[4]);
	return Clinet;
}
bool ClientExitstsByAccountNumber(string AccountNumber, string FileName)
{
	vector <stClinet>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClinet Client;
		while (getline(MyFile, Line))
		{
			Client = CounvertLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
stClinet ReadNewClient()
{
	stClinet Client;
	cout << "Enter Account Number ?";

	getline(cin >> ws, Client.AccountNumber);

	while (ClientExitstsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [ " << Client.AccountNumber << "] already exists ,Enter another Account Number ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode : ";
	getline(cin, Client.PinCode);
	cout << "Enter Name :";
	getline(cin, Client.Name);
	cout << "Enter Phone :";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance :";
	cin >> Client.AccountBalance;
	return Client;
}
vector <stClinet> LoadClientsDataFromFile(string FileName)
{
	vector <stClinet> vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClinet Clinet;

		while (getline(MyFile, Line))
		{
			Clinet = CounvertLineToRecord(Line);

			vClient.push_back(Clinet);

		}

		MyFile.close();
	}

	return vClient;
}

void AddDataLineToFile(string FileName, string strDataline)
{
	fstream MyFile;
	char Revision = 'y';
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << strDataline << endl;
		MyFile.close();
	}

}
bool FindClientByAccountNumber(string AccountNumber, vector <stClinet> vClients, stClinet& Client)
{
	for (stClinet C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintClientRecordLine(stClinet Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClinetRecord(stClinet Clinet)
{
	cout << "\n\nThe following are the client Delete : \n\n";
	cout << "----------------------------------------------";
	cout << "\nAccount Number  : " << Clinet.AccountNumber;
	cout << "\nPinCode         : " << Clinet.PinCode;
	cout << "\nName            : " << Clinet.Name;
	cout << "\nPhone           : " << Clinet.Phone;
	cout << "\nAccount Balance : " << Clinet.AccountBalance;
	cout << "\n----------------------------------------------";
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClinet>& vClient)
{
	for (stClinet& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClinet>SaveCleintsDataToFile(string FileName, vector<stClinet>vClinet)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLina;
	if (MyFile.is_open())
	{
		for (stClinet C : vClinet)
		{
			if (C.MarkForDelete == false)
			{
				DataLina = CounvertRecordToLine(C);
				MyFile << DataLina << endl;
			}
		}
		MyFile.close();
	}
	return vClinet;
}
void ShowAllClientsScreen()
{
	vector< stClinet>vClients = LoadClientsDataFromFile(ClientsFileName);
	//cout << "\n\t\t\t\t\tClient List (" << vClients.size() << "(Client(s).";
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";

	cout << "\n---------------------------------------------------------------";
	cout << "---------------------------------------------\n";

	cout << "| " << left << setw(15) << "Accout Number: ";
	cout << "| " << left << setw(10) << "Pin Code: ";
	cout << "| " << left << setw(40) << "Client Name : ";
	cout << "| " << left << setw(12) << "Phone : ";
	cout << "| " << left << setw(12) << "Balance: ";
	cout << "\n-----------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	if (vClients.size() == 0)

		cout << "\t\t\t\t No CLients Available In the System  ! ";
	else
		for (stClinet Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << "\n";
		}
	cout << "\n --------------------------------------------------------------------------";
	cout << "--------------------------------------------\n";
}
void AddNewClient()
{
	stClinet Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, CounvertRecordToLine(Client));
}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client :\n\n";
		AddNewClient();


		cout << "\n Client Added Successfully ,do you want to add More Clinets? Y\ N?";

		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

stClinet ChangeClientRecord()
{
	stClinet Client;
	string AccountNumber;
	Client.AccountNumber = AccountNumber;
	cout << "Enter Account Number ?";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClinet>& vClinet)
{
	stClinet Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClinet, Client))
	{
		PrintClinetRecord(Client);
		cout << "\n\n Are you sur you want delete this client? y/n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClinet);
			SaveCleintsDataToFile(ClientsFileName, vClinet);

			vClinet = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\n Client Deleted Successfully .";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
	}
	return false;

}
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClinet>& vClients)
{
	stClinet Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClinetRecord(Client);

		cout << "\n\nAre you sure you want Update client ? n/y ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClinet& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord();
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\n Client Deleted Successfully. \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";

		return false;
	}
	return false;

}
string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber ? ";
	cin >> AccountNumber;

	return AccountNumber;
}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client screen ";
	cout << "\n------------------------------------\n";
	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumbe = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumbe, vClient);
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen ";
	cout << "\n------------------------------------\n";
	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumbe = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumbe, vClient);
}
void ShowAddNewClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t Add New Client Screen ";
	cout << "\n------------------------------------\n";

	AddNewClients();
}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t Find Client Screen  ";
	cout << "\n------------------------------------\n";

	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	stClinet Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
		PrintClinetRecord(Client);
	else
		cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";

}
void ShowEndScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\t Program Ends :-  ";
	cout << "\n------------------------------------\n";

}


void GoBackToMainMenue()
{
	cout << "\n\npress any Key to go  back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do ? [1 to 6]?";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void PerfromMenueOption(enMainMnueoptions MainMenueoption)
{
	switch (MainMenueoption)
	{
	case enMainMnueoptions::eListClients:

		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;


	case enMainMnueoptions::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eFindCLient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMnueoptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}

}
void ShowMainMenue()
{
	system("cls");
	cout << "=============================================================\n";
	cout << "\t\t Main Menue Screen  \t\t\t\n";
	cout << "=============================================================\n";
	cout << "\t[1]Show Client tist\n ";
	cout << "\t[2]Add New Client.\n";
	cout << "\t[3]Delete Client .\n";
	cout << "\t[4]Update Client Info\n";
	cout << "\t[5]Find Client.\n";
	cout << "\t[6]Exit.\n";
	cout << "=============================================================\n";
	PerfromMenueOption((enMainMnueoptions)ReadMainMenueOption());
}
int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}*/


const string ClientsFileName = "MyFileClients.txt";

void ShowMainMenue();
void ShowTransactionsScreen();

struct stClinet
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};
enum enMainMnueoptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindCLient = 5, enShowTransactionMenue = 6, eExit = 7
};
enum enTransactionMenueOptions
{
	enDeposit = 1, enWithdraw = 2,
	enShowTotalBalances = 3, enShowMainMenue = 4
};
vector <string> SplitString(string S9, string Delim)

{
	vector <string> vString;

	short pos = 0;
	string sWord;
	while ((pos = S9.find(Delim)) != std::string::npos)
	{
		sWord = S9.substr(0, pos);
		if (sWord != "")
		{

			vString.push_back(sWord);
		}


		S9.erase(0, pos + Delim.length());

	}

	if (S9 != "")
	{

		vString.push_back(S9);

	}
	return vString;
}
string CounvertRecordToLine(stClinet Clinet, string Seperator = "#//#")
{
	string stClinetRecord = "";

	stClinetRecord += Clinet.AccountNumber + Seperator;
	stClinetRecord += Clinet.PinCode + Seperator;
	stClinetRecord += Clinet.Name + Seperator;
	stClinetRecord += Clinet.Phone + Seperator;
	stClinetRecord += to_string(Clinet.AccountBalance);
	return stClinetRecord;
}
stClinet CounvertLineToRecord(string Line, string Seperator = "#//#")
{
	stClinet Clinet;
	vector <string> vClinetData;

	vClinetData = SplitString(Line, Seperator);
	if (vClinetData.size() != 5)
	{
		cout << "Invalid line format: " << Line << endl;
		return Clinet;
	}
	Clinet.AccountNumber = vClinetData[0];
	Clinet.PinCode = vClinetData[1];
	Clinet.Name = vClinetData[2];
	Clinet.Phone = vClinetData[3];
	Clinet.AccountBalance = stod(vClinetData[4]);
	return Clinet;
}
bool ClientExitstsByAccountNumber(string AccountNumber, string FileName)
{
	vector <stClinet>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClinet Client;
		while (getline(MyFile, Line))
		{
			Client = CounvertLineToRecord(Line);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
stClinet ReadNewClient()
{
	stClinet Client;
	cout << "\nEnter Account Number ?";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExitstsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [ " << Client.AccountNumber << "] already exists ,Enter another Account Number ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode : ";
	getline(cin, Client.PinCode);
	cout << "Enter Name :";
	getline(cin, Client.Name);
	cout << "Enter Phone :";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance :";
	cin >> Client.AccountBalance;
	return Client;
}
vector <stClinet> LoadClientsDataFromFile(string FileName)
{
	vector <stClinet> vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClinet Clinet;

		while (getline(MyFile, Line))
		{
			Clinet = CounvertLineToRecord(Line);

			vClient.push_back(Clinet);

		}

		MyFile.close();
	}

	return vClient;
}

void AddDataLineToFile(string FileName, string strDataline)
{
	fstream MyFile;
	char Revision = 'y';
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << strDataline << endl;
		MyFile.close();
	}

}
bool FindClientByAccountNumber(string AccountNumber, vector <stClinet> vClients, stClinet& Client)
{
	for (stClinet C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

void PrintClientRecordLine(stClinet Client)
{
	cout << "| " << setw(20) << left << Client.AccountNumber;
	cout << "| " << setw(16) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClientRecordBalanceLine(stClinet Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClinetRecord(stClinet Clinet)
{
	cout << "\nThe following are the client Delete : \n";
	cout << "----------------------------------------------";
	cout << "\n\tAccount Number  : " << Clinet.AccountNumber;
	cout << "\n\tPinCode         : " << Clinet.PinCode;
	cout << "\n\tName            : " << Clinet.Name;
	cout << "\n\tPhone           : " << Clinet.Phone;
	cout << "\n\tAccount Balance : " << Clinet.AccountBalance;
	cout << "\n----------------------------------------------\n";
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClinet>& vClient)
{
	for (stClinet& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector<stClinet>SaveCleintsDataToFile(string FileName, vector<stClinet>vClinet)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLina;
	if (MyFile.is_open())
	{
		for (stClinet C : vClinet)
		{
			if (C.MarkForDelete == false)
			{
				DataLina = CounvertRecordToLine(C);
				MyFile << DataLina << endl;
			}
		}
		MyFile.close();
	}
	return vClinet;
}
void ShowAllClientsScreen()
{
	vector< stClinet>vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";

	cout << "\n---------------------------------------------------------------";
	cout << "---------------------------------------------\n";

	cout << "| " << left << setw(20) << " Accout Number: ";
	cout << "| " << left << setw(16) << " Pin Code: ";
	cout << "| " << left << setw(40) << " Client Name : ";
	cout << "| " << left << setw(12) << " Phone : ";
	cout << "| " << left << setw(12) << " Balance: ";
	cout << "\n-----------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	if (vClients.size() == 0)

		cout << "\t\t\t\t No CLients Available In the System  ! ";
	else
		for (stClinet Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << "\n";
		}
	cout << "\n --------------------------------------------------------------------------";
	cout << "--------------------------------------------\n";
}
void ShowTotalBalances()
{
	vector< stClinet>vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";

	cout << "\n---------------------------------------------------------------";
	cout << "------------------------------------------\n" << endl;

	cout << "| " << left << setw(15) << " Accout Number: ";
	cout << "| " << left << setw(40) << " Client Name : ";
	cout << "| " << left << setw(12) << " Balance: ";
	cout << "\n-----------------------------------------------------------------";
	cout << "----------------------------------\n\n";

	double TotalBalances = 0;

	if (vClients.size() == 0)

		cout << "\t\t\t\t No CLients Available In the System  ! ";
	else
		for (stClinet Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << "\n";
		}
	cout << "\n --------------------------------------------------------------------------";
	cout << "----------------------------------\n";
	cout << "\n\t\t\t\t Total Balances = " << TotalBalances << endl;
}
void AddNewClient()
{
	stClinet Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, CounvertRecordToLine(Client));
}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "   Adding New Client :\n\n";
		AddNewClient();


		cout << "\n Client Added Successfully ,do you want to add More Clinets? Y\ N?";

		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

stClinet ChangeClientRecord()
{
	stClinet Client;
	string AccountNumber;
	Client.AccountNumber = AccountNumber;
	cout << "Enter Account Number ?";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClinet>& vClinet)
{
	stClinet Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClinet, Client))
	{
		PrintClinetRecord(Client);
		cout << "\n\n Are you sur you want delete this client? y/n";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClinet);
			SaveCleintsDataToFile(ClientsFileName, vClinet);

			vClinet = LoadClientsDataFromFile(ClientsFileName);

			cout << "\n\n Client Deleted Successfully .";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
	}
	return false;

}
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClinet>& vClients)
{
	stClinet Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClinetRecord(Client);

		cout << "\n\nAre you sure you want Update client ? n/y ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClinet& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord();
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\n Client Deleted Successfully. \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";

		return false;
	}
	return false;

}
bool DepositBalanceToClientByAccoutNumber(string AccountNumber, double Amount, vector <stClinet>& vClient)
{
	char Answer = 'n';
	cout << "\n\n Are you sure you want perform this transaction?y/n ?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		for (stClinet& c : vClient)
		{
			if (c.AccountNumber == AccountNumber)
			{
				c.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClient);
				cout << "\n\nDone Successfully. New balance is : " << c.AccountBalance;

				return true;
			}
		}
		return false;
	}
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber ? ";
	cin >> AccountNumber;

	return AccountNumber;
}
void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t Delete Client screen ";
	cout << "\n------------------------------------\n";
	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumbe = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumbe, vClient);
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen ";
	cout << "\n------------------------------------\n";
	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumbe = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumbe, vClient);
}
void ShowAddNewClientScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\t Add New Client Screen ";
	cout << "\n------------------------------------\n";

	AddNewClients();
}


void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t Find Client Screen  ";
	cout << "\n------------------------------------\n";

	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	stClinet Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
		PrintClinetRecord(Client);
	else
		cout << "\nClient with Account Number [" << AccountNumber << "] is not found!";

}
void ShowEndScreen()
{

	cout << "\n-----------------------------------\n";
	cout << "\t Program Ends :-  ";
	cout << "\n------------------------------------\n";

}


void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t Deposit Screen    ";
	cout << "\n------------------------------------\n";
	stClinet Client;

	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\n Client with [ " << AccountNumber << " ] does not exisst.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClinetRecord(Client);

	double Amount = 0;
	cout << "please enter deposit amount ?";
	cin >> Amount;
	DepositBalanceToClientByAccoutNumber(AccountNumber, Amount, vClient);

}
void ShowWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\t WithDraw  Screen    ";
	cout << "\n------------------------------------\n";
	stClinet Client;

	vector<stClinet>vClient = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\n Client with [ " << AccountNumber << " ] does not exisst.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClinetRecord(Client);

	double Amount = 0;
	cout << "please enter deposit amount ?";
	cin >> Amount;
	while (Amount > Client.AccountBalance)
	{
		cout << "\n Amount Exceeds the balance,you can withdraw up to :[" << Client.AccountBalance << " ] jast ";
		cout << "Please Enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccoutNumber(AccountNumber, Amount * -1, vClient);

}

void ShowTotalBlanceScreen()
{
	ShowTotalBalances();
}
void GoBackToMainMenue()
{
	cout << "\n\npress any Key to go  back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do ? [1 to 7]?";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do ? [1 to 4]?";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void GoBaktoTransactionsMenue()
{
	cout << "\n\nPress Enter  any Key to go  Tranaction Mian  Menue....";
	system("Pause>0");
	ShowTransactionsScreen();
}
void PerfromTranactionMenueOption(enTransactionMenueOptions TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionMenueOptions::enDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBaktoTransactionsMenue();
		break;
	}
	case enTransactionMenueOptions::enWithdraw:
	{
		system("cls");
		ShowWithDrawScreen();
		GoBaktoTransactionsMenue();
		break;


	}
	case enTransactionMenueOptions::enShowTotalBalances:
	{
		system("cls");
		ShowTotalBlanceScreen();
		GoBaktoTransactionsMenue();
		break;
	}
	case enTransactionMenueOptions::enShowMainMenue:
	{
		ShowMainMenue();
		break;
	}

	}

}

void PerfromMenueOption(enMainMnueoptions MainMenueoption)
{
	switch (MainMenueoption)
	{
	case enMainMnueoptions::eListClients:

		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;


	case enMainMnueoptions::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMnueoptions::eFindCLient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;


	case enMainMnueoptions::enShowTransactionMenue:
		system("cls");
		ShowTransactionsScreen();
		GoBaktoTransactionsMenue();
		break;
	case enMainMnueoptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}

}
void ShowTransactionsScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\t Transactions Menuen Screen     ";
	cout << "\n====================================\n";
	cout << "\t [1] Deposit.\n";
	cout << "\t [2] Withdraw.\n";
	cout << "\t [3] Total Balances .\n";
	cout << "\t [4] Main Menue.\n";
	cout << "\n====================================\n";
	PerfromTranactionMenueOption((enTransactionMenueOptions)ReadTransactionsMenueOption());
}
void ShowMainMenue()
{
	system("cls");
	cout << "=============================================================\n";
	cout << "\t\t Main Menue Screen  \t\t\t\n";
	cout << "=============================================================\n";
	cout << "\t[1] Show Client tist\n ";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client .\n";
	cout << "\t[4] Update Client Info\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "=============================================================\n";
	PerfromMenueOption((enMainMnueoptions)ReadMainMenueOption());
}
int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}
