#include <iostream>
#include <string>
#include<vector>
#include <fstream>
#include<iomanip>

using namespace std;

void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageMenue();

const string ClientsFileName = "Client.txt";
const string UserFileName = "User.txt";
enum enTransactionMenue
{
    eDeposit=1,eWithdraw=2,
    eTotalbalance=3,MainMenue=4

};
enum enOptions
{
    eShowClientsList = 1, eAddNewClients = 2,
    eDeleteClient = 3, eUpdateClientInfo = 4,
    eFindClient = 5, etransactions = 6, eManageMenue = 7,
    eLogout = 8
};
enum enManageMenue
{
    eListUser = 1, eAddNewUser = 2,
    eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5, eMainMenue = 6
};
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
    
};
struct stUser
{
    string UserName;
    string PassWord;
    int Permission;
    bool MarkForDelete = false;
};
stUser CurrentUser;

enum enMainMenuePermissions
{
    eAll = -1, pListClients = 1, pAddNewClient = 2,
    pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16,
    pTranactions = 32, pManageUsers = 64 
};
bool CheckAccessPermission(enMainMenuePermissions Permission);

vector <string> SplitString(string S1, string Delim)
{
    vector<string> vstring;

    short Pos = 0;
    string sWord;

    while ((Pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, Pos);
        if (sWord != " ")
        {
            vstring.push_back(sWord);
        }

        S1.erase(0, Pos + Delim.length());
    }
    if (S1 != " ")
    {
        vstring.push_back(S1);
    }

    return vstring;
}


int ReadPermissionsToSet() 
{

    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";  
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { return -1; }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? "; 
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pListClients; }  

    cout << "\nAdd New Client? y/n? ";   
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pAddNewClient; }  

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pDeleteClient; } 

    cout << "\nUpdate Client? y/n? ";  
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pUpdateClients; }

    cout << "\nFind Client? y/n? ";  
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    { Permissions += enMainMenuePermissions::pFindClient; } 

    cout << "\nTransactions? y/n? ";   
    cin >> Answer; if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pTranactions; }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') 
    { Permissions += enMainMenuePermissions::pManageUsers; 
    }
    return Permissions;
}
sClient convertLineToRecord(string line, string sparater = "#//#")
{
    sClient Client;
    vector<string > vClientdata;
    vClientdata = SplitString(line, sparater);

    Client.AccountNumber = vClientdata[0];
    Client.PinCode = vClientdata[1];
    Client.Name = vClientdata[2];
    Client.Phone = vClientdata[3];
    Client.AccountBalance = stod(vClientdata[4]);
    return Client;
}


stUser convertLineToRecordforUser(string line, string sparater = "#//#")
{
    stUser User;
    vector<string > vUserdata;
    vUserdata = SplitString(line, sparater);

    User.UserName = vUserdata[0];
    User.PassWord = vUserdata[1];
    User.Permission = stoi(vUserdata[2]);
    
    return User;
}
void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}

bool CheckAccessPermission(enMainMenuePermissions Permission) 
{
    if (CurrentUser.Permission == enMainMenuePermissions::eAll) 
        return true;
    if ((Permission & CurrentUser.Permission) == Permission)
        return true;
    else 
        return false; 
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = convertLineToRecord(Line);

            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return vClients;
}

vector <stUser> LoadUserDataFromFile(string FileName)
{
    vector <stUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = convertLineToRecordforUser(Line);

            vUser.push_back(User);
        }
        MyFile.close();
    }

    return vUser;
}


void PrintClientRecord2(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecord2(stUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.PassWord;
    cout << "| " << setw(10) << left << User.Permission;

}


void PrintClientRecord3(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
//    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
  //  cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsDataScreen()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        ShowAccessDeniedMessage();
        return;
    }


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

    for (sClient Client : vClients)
    {
        PrintClientRecord2(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalanceScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    double TotalBalance = 0;
    
    cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients)
    {
        PrintClientRecord3(Client);
        TotalBalance = TotalBalance + Client.AccountBalance;
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout<<"\n"   << "\t\t\t\t\t\tTotalBalance = " << TotalBalance;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = convertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

bool IsUserExistsByName(string UserName, string FileName)
{
    vector <stUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = convertLineToRecordforUser(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            vUser.push_back(User);
        }

        MyFile.close();

    }
    return false;
}


sClient ReadNewClient()
{
    sClient Client;


    cout << "Please enter Account Number?";
    getline(cin >> ws, Client.AccountNumber);
    /////////////////////////////
 
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "enter PinCode?";
    getline(cin, Client.PinCode);

    cout << "Please enter your Name?";
    getline(cin, Client.Name);

    cout << "Please enter your phone?";
    getline(cin, Client.Phone);

    cout << "Please enter AccountBalance?";
    cin >> Client.AccountBalance;

    return Client;



}
stUser ReadNewUser()
{
    stUser User;
    cout << "Enter UserName? ";
    getline(cin >> ws, User.UserName);
    

    while (IsUserExistsByName(User.UserName, UserFileName))
    {
        cout << "\nClient with [" << User.UserName << "] already exists, Enter another UserName? ";
        getline(cin >> ws, User.UserName);
       
    }
    cout << "Enter Password? ";
    getline(cin >> ws, User.PassWord);

    User.Permission = ReadPermissionsToSet();
    return User;
}


void AddDataLineToFile(string FileName, string stClientData)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stClientData << endl;

        MyFile.close();
    }

}

string ConvertRecordToLine(sClient Client, string Separater = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Separater;
    stClientRecord += Client.PinCode + Separater;
    stClientRecord += Client.Name + Separater;
    stClientRecord += Client.Phone + Separater;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

string ConvertRecordToLine(stUser User, string Separater = "#//#")
{
    string stUserRecord = "";

    stUserRecord += User.UserName + Separater;
    stUserRecord += User.PassWord + Separater;
    stUserRecord += to_string(User.Permission);

    return stUserRecord;

}


void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}
void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UserFileName, ConvertRecordToLine(User));

}


void AddClient()
{
   
    char AddMore = 'Y';

    do
    {
    
        cout << "Adding New Clients:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
void AddUser()
{

    char AddMore = 'Y';

    do
    {

        cout << "Adding New Clients:\n\n";

        AddNewUser();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

void GoBackToManageMenue()
{
    cout << "\n\nPress any key to go back to Transaction menue...\n";
    system("pause>0");
    ShowManageMenue();
}

void GoBackToMain()
{
    cout << "\n\nPress any key to go back to main menue...\n" ;
    system("pause>0");
    ShowMainMenue();
}

void GoBackToMaintransaction()
{
    cout << "\n\nPress any key to go back to Transaction menue...\n";
    system("pause>0");
    ShowTransactionsMenue();
}



bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUserName(string UserName, vector<stUser> vUser, stUser& User)
{
    for (stUser C : vUser)
    {
        if (C.UserName == UserName)
        {
            User = C;
            return true;
        }
    }
    return false;
}


bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true; return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUserName(string UserName, vector <stUser>& vUser)
{
    for (stUser& C : vUser)
    {
        if (C.UserName == UserName)
        {
            C.MarkForDelete = true; return true;
        }
    }
    return false;
}


vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

vector <stUser> SaveUsersDataToFile(string FileName, vector<stUser> vUser)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stUser C : vUser)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUser;
}


void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "---------------------------------------------\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n---------------------------------------------\n";

}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "---------------------------------------------\n";
    cout << "\nUserName     : " << User.UserName;
    cout << "\nPassword     : " << User.PassWord;
    cout << "\nPermission   : " << User.Permission;
    cout << "\n---------------------------------------------\n";

}

string  ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "Please enter AccountNumer?" << endl;
    cin >> AccountNumber;

    return AccountNumber;
}

string  ReadUserName()
{
    string UserName = "";
    cout << "Please enter UserName?" << endl;
    cin >> UserName;

    return UserName;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> vClients)
{
  
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DeleteUserByUserName(string UserName, vector<stUser> vUser)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            MarkUserForDeleteByUserName(UserName,vUser);
            SaveUsersDataToFile(UserFileName, vUser);

            //Refresh Clients
            vUser = LoadUserDataFromFile(UserFileName);

            cout << "\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";
        return false;
    }
}

stUser ChangeUserRecord(string Username)
{
    stUser User;
    User.UserName = Username;

    cout << "\nEnter password? ";
    getline(cin >> ws, User.PassWord);

  
    return User;
}

bool UpdateUserByUserName(string UserName, vector<stUser> vUser)
{
    
    stUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want Update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (stUser& U : vUser)
            {
                if (U.UserName == UserName)
                {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }

            SaveUsersDataToFile(UserFileName, vUser);
            //Refresh Clients
            vUser = LoadUserDataFromFile(UserFileName);

            cout << "\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";
        return false;
    }
}

bool FindUserByUserName(string UserName, vector<stUser> vUser)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {
        PrintUserCard(User);
        return true;
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";
        return false;
    }
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void UpdateScreenInfo()
{
    system("cls");
    cout << "\n-----------------------------\n";
    cout << " Update Clients Screen\n";
    cout << "-----------------------------\n";

}

void ShowAddNewClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout << "\n-----------------------------\n";
    cout << " Add New Clients Screen\n";
    cout << "-----------------------------\n";
    AddClient();
}

void FindScreen()
{
    system("cls");
    cout << "\n-----------------------------\n";
    cout << " Find Clients Screen\n";
    cout << "-----------------------------\n";

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
  
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {

                if (C.AccountNumber == AccountNumber)
                {
                   
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }


            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DepositAmountClientByAccountNumber(string AccountNumber,double Amount, vector<sClient>& vClients)
{

    char Answer = 'n';

        cout << "\n\nAre you sure do you want Perform this transaction? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {

                if (C.AccountNumber == AccountNumber)
                {
                    C.AccountBalance += Amount;
                    SaveCleintsDataToFile(ClientsFileName, vClients);
                    cout << "\n\nDone Successfully. New Balance is " << C.AccountBalance;
                    return true;
                }
            }
           
        }
        return true;
    }

void TheEndScreen()
{
    system("cls");
    cout << "-----------------------------\n";
    cout << "\tProgram Ends :-)\n";
    cout << "-----------------------------\n";

}

void ShowDepositScreen()
{ 
    
    cout << "\n-----------------------------\n";
    cout << " Deposit Screen\n";
    cout << "-----------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
   
  while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
       cout << "\nClient With [" << AccountNumber << "] does Not Exist.";
       AccountNumber = ReadClientAccountNumber();
    }

  PrintClientCard(Client);
  double Amount = 0;
  cout << "\nPlease enter Deposit amount. ";
  cin >> Amount;

  DepositAmountClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{

    cout << "\n-----------------------------\n";
    cout << " WithDraw Screen\n";
    cout << "-----------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With [" << AccountNumber << "] does Not Exist.";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter WithDraw amount. ";
    cin >> Amount;
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << Client.AccountBalance;
        cout << "\nPlease enter Another amount. ";
        cin >> Amount;
    }

    DepositAmountClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}


short ReadMainMenueOption()
{
    short CHOOSE =0;
    cout << "\nChoose what do you want to do? [1 to 8]?";
    cin >> CHOOSE;
    return CHOOSE;
}

short ReadTransactionsOption()
{
    short CHOOSE = 0;
    cout << "\nChoose what do you want to do? [1 to 4]?";
    cin >> CHOOSE;
    return CHOOSE;
}

short ReadManageMenueOption()
{
    short CHOOSE = 0;
    cout << "\nChoose what do you want to do? [1 to 6]?";
    cin >> CHOOSE;
    return CHOOSE;
}

void ShowDeleteClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout << "\n-----------------------------\n";
    cout << " Delete Clients Screen\n";
    cout << "-----------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------\n";
    cout << " Delete User Screen\n";
    cout << "-----------------------------\n";

    vector <stUser> vUser = LoadUserDataFromFile(UserFileName);
    string UserName = ReadUserName();

    DeleteUserByUserName(UserName, vUser);
}

void ShowUpdateUserScreen()
{
  


    cout << "\n-----------------------------\n";
    cout << " Update User Screen\n";
    cout << "-----------------------------\n";

    vector <stUser> vUser = LoadUserDataFromFile(UserFileName);
    string UserName = ReadUserName();

    UpdateUserByUserName(UserName, vUser);
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------\n";
    cout << " Find User Screen\n";
    cout << "-----------------------------\n";

    vector <stUser> vUser = LoadUserDataFromFile(UserFileName);
    string UserName = ReadUserName();

    FindUserByUserName(UserName, vUser);
}

void ShowUpdateClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------\n";
    cout << " Update Clients Screen\n";
    cout << "-----------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void StartTransactionsMenue(enTransactionMenue transactionMenue)
{
    switch (transactionMenue)
    {

    case enTransactionMenue::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToMaintransaction();
        break;
    }

    case enTransactionMenue::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToMaintransaction();
        break;
    }

    case enTransactionMenue::eTotalbalance:
    {
        system("cls");
        ShowTotalBalanceScreen();
        GoBackToMaintransaction();
        break;
    }

    case enTransactionMenue::MainMenue:
    {
        ShowMainMenue();
        break;
    }

    }
}

void ShowTransactionsMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedMessage();
        GoBackToMain();
        return;
    }

    system("cls");
    cout << "===================================\n";
    cout << "\tTransactions Menue Screen\n";
    cout << "===================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===================================\n";
    StartTransactionsMenue((enTransactionMenue)ReadTransactionsOption());

}
void ShowUserListScreen()
{
    vector <stUser> vUser = LoadUserDataFromFile(UserFileName);
   
    cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(12) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stUser User : vUser)
    {
        PrintUserRecord2(User);
        cout << endl;

    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    
}
void ShowAddNewUserScreen()
{

    cout << "\n-----------------------------\n";
    cout << " Add New User Screen\n";
    cout << "-----------------------------\n";
    AddUser();
}
void StartManageMenue(enManageMenue ManageMenueOption)
{
    switch (ManageMenueOption)
    {

    case enManageMenue::eListUser:
        system("cls");
        ShowUserListScreen();
        GoBackToManageMenue();
        break;

    case enManageMenue::eAddNewUser:
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageMenue();
        break;

    case enManageMenue::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageMenue();
        break;

    case enManageMenue::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageMenue();
        break;

    case enManageMenue::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageMenue();
        break;

    case enManageMenue::eMainMenue:

        ShowMainMenue();
        break;
    }

}
void ShowManageMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        system("cls");
        ShowAccessDeniedMessage();
        GoBackToMain();
        return;
    }

    system("cls");
    cout << "===================================\n";
    cout << "\tManage User Menue Screen\n";
    cout << "===================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===================================\n";
    StartManageMenue((enManageMenue)ReadManageMenueOption());
}
void ReadLogin(string &UserName, string &Password)
{
    cout << "Enter UserName: ";
    getline(cin >> ws, UserName);
    cout << "Enter Password: ";
    getline(cin >> ws, Password);

}
void LoginScreen()
{
    cout << "---------------------------------\n";
    cout << "\tLogin Screen\n";
    cout << "---------------------------------\n";
}
bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
    vector <stUser> vUsers = LoadUserDataFromFile(UserFileName);
    for (stUser U : vUsers) 
    {
        if (U.UserName == Username && U.PassWord == Password)
        {
            User = U; 
            return true;
        }
    }
    return false;

}
bool  LoadUserInfo(string Username, string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else 
        return false;
}
void LogIn()
{
    bool LoginFaild = false;
    string Username, Password;
    do 
    {
        system("cls");  
        cout << "\n---------------------------------\n"; 
        cout << "\tLogin Screen";   
        cout << "\n---------------------------------\n";

        if (LoginFaild) 
        {
            cout << "Invlaid Username/Password!\n";
        }
        cout << "Enter Username? ";
        cin >> Username;    
        cout << "Enter Password? ";     
        cin >> Password;   
        LoginFaild = !LoadUserInfo(Username, Password); 

    }while (LoginFaild);  

    ShowMainMenue();
    
   
       
}
void ShowFindClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        return;
    }

    cout << "\n-----------------------------\n";
    cout << " Find Clients Screen\n";
    cout << "-----------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient With Account Number[" << AccountNumber << "] is Not Found.";
    }

}
void StartMainMenue(enOptions Option)
{
   
    switch (Option)
    {

    case enOptions::eShowClientsList :
        system("cls");
        ShowAllClientsDataScreen();
        GoBackToMain();
        break;

    case enOptions::eAddNewClients :
    {
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMain();
        break;
    }
    case enOptions::eDeleteClient :
    {
        system("cls");
        ShowDeleteClientsScreen();
        GoBackToMain();
        break;
    }
    case enOptions::eUpdateClientInfo :
    {
        system("cls");
        ShowUpdateClientsScreen();
        GoBackToMain();
        break;
    }
    case enOptions::eFindClient:
    {
        system("cls");
        ShowFindClientsScreen();
        GoBackToMain();
        break;
    }
    case enOptions::etransactions:
    {
  
        ShowTransactionsMenue();
        break;
    }
    case enOptions::eManageMenue:
    {
        ShowManageMenue();
        break;
    }
    case enOptions::eLogout:
        system("cls");
        LogIn();
        break;
    }



}
void ShowMainMenue()
{
    system("cls");
    cout << "===================================\n";
    cout << "\tMain Screen\n";
    cout << "===================================\n";
    cout << "\t[1] Show Clients List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Menue.\n";
    cout << "\t[8] LogOut.\n";
    cout << "===================================\n";
    StartMainMenue((enOptions)ReadMainMenueOption());


}
int main()
{
   
    LogIn();

    return 0;
}