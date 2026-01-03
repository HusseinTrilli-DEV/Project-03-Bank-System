#pragma once

#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>


using namespace std;
const string ClientsFileName = "Client.txt";
namespace MyInPut
{
    int RandomNumber(int From, int To)
    {
       
        int randNum = rand() % (To - From + 1) + From;
        return randNum; 
    }

    int ShowHowManyRound()
    {
        int Rounds = 1;
        do
        {
            cout << "How Many Questuions do you need to to answer ?";
            cin >> Rounds;

        } while (Rounds > 10 || Rounds < 1);

        return Rounds;

    }

    float ReadFloatNumber()
    {
        float Number;  // Variable to store user input.

        // Prompt the user to enter a floating-point number.
        cout << "Please enter a float number? ";
        cin >> Number;  // Read input from the user.

        return Number;  // Return the input number.
    }

    int ReadNumberOnly() 
    {

        int Number;  
        cout << "Please enter a number?" << endl;  
        cin >> Number;
        while (cin.fail())
        { // user didn't input a number 
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   
            cout << "Invalid Number, Enter a valid one:" << endl;   
            cin >> Number;   
        }
        return Number;
    }

    void LoadDataFromFileToVector(string FileName, vector <string>& vFileContenet)
    {
        fstream MyFile;

        MyFile.open(FileName, ios::in); // Read Mode

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {

                vFileContenet.push_back(Line);
            }

            MyFile.close();
        }
    }

    void PrintFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && IsFirstLetter)
            {
                cout << S1[i] << endl;
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }

    }

    string UpperFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && IsFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    string LowerFirstLetterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && IsFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }

            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }
        return S1;
    }

    string UpperAllString(string S1)
    {

        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }

        return S1;
    }

    string LowerAllString(string S1)
    {

        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }

        return S1;
    }

    char InvertCharactar(char C1)
    {
        return  isupper(C1) ? tolower(C1) : toupper(C1);

    }

    string InvertAllString(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertCharactar(S1[i]);
        }
        return S1;
    }

    enum enwahtToCount { SmallLetters = 0, Capitalletters = 1, all = 3 };

    short CountLetters(string S1, enwahtToCount WahtTocount = enwahtToCount::all)
    {
        if (WahtTocount == enwahtToCount::all)
        {
            return S1.length();
        }



        short Count = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (WahtTocount == enwahtToCount::Capitalletters && isupper(S1[i]))
                Count++;

            if (WahtTocount == enwahtToCount::SmallLetters && islower(S1[i]))
                Count++;


        }

        return Count;

    }

    short CountCapitalLetter(string S1)
    {
        short CountCapitalLetter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
            {
                CountCapitalLetter++;
            }

        }

        return CountCapitalLetter;
    }

    short CountSmallLetter(string S1)
    {
        short CountSmallLetter = 0;
        for (int i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
            {
                CountSmallLetter++;
            }

        }

        return CountSmallLetter;
    }
    short CountOneLetter(string S1, char C1)
    {
        short Count = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] == C1)
                Count++;
        }
        return Count;
    }


    short CountLetter(string S1, char Letter, bool matchCase = true)
    {
        short Count = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (matchCase)
            {
                if (S1[i] == Letter)
                    Count++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Count++;
            }
        }
        return Count;
    }

    bool IsVowel(char Letter)
    {
        Letter = tolower(Letter);

        return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));

    }

    short CountVowel(string S1)
    {
        short Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {

            if (IsVowel(S1[i]))
            {
                Counter++;
            }

        }
        return Counter;
    }

    void PrintVowels(string S1)
    {
        cout << "\nvowels in string are : ";
        for (short i = 0; i < S1.length(); i++)
        {

            if (IsVowel(S1[i]))
            {
                cout << S1[i] << "  ";
            }

        }
        cout << "\n";
    }

    void PrintEachWordInString(string S1)
    {
        cout << "\nYour String Words are :  \n\n";
        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ')
            {
                cout << S1[i];
            }
            else
                cout << "\n";
        }


    }

    void PrintEachWordInStringAdvenced(string S1)
    {
        string Delim = " ";
        cout << "\nYour String Words are :  \n\n";
        short Pos = 0;
        string sWord;
        while ((Pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, Pos);
            if (sWord != " ")
            {
                cout << sWord << endl;
            }

            S1.erase(0, Pos + Delim.length());
        }
        if (S1 != " ")
        {
            cout << S1 << endl;
        }

    }

    short CountWords(string S1)
    {
        string Delim = " ";
        short Pos = 0;
        short counter = 0;
        string sWord;

        while ((Pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, Pos);
            if (sWord != " ")
            {
                counter++;
            }

            S1.erase(0, Pos + Delim.length());
        }
        if (S1 != " ")
        {
            counter++;
        }
        return counter;
    }

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

    string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - 1);
            }

        }
        return "";
    }

    string TrimRight(string S1)
    {
        for (short i = S1.length() - 1; i >= 0; i--)
        {

            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }

        }
        return "";
    }
    string Trim(string S1)
    {
        return (TrimLeft(TrimRight(S1)));
    }

    string JoinString(vector<string> vString, string Delim)
    {
        string S1 = "";
        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }
        return S1.substr(0, S1.length() - Delim.length());
    }

    string JoinString(string arrString[], short Length, string Delim)
    {
        string S1 = "";
        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }
        return S1.substr(0, S1.length() - Delim.length());
    }

    string ReverseWordsInString(string S1)
    {
        vector<string> vString;
        string S2 = "";

        vString = SplitString(S1, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();
        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter + " ";
        }
        S2 = S2.substr(0, S2.length() - 1);  //remove last space.

        return S2;
    }
    string ReplaceWordInStringUsingBuiltInFunction(string S1, string StringToReplace, string sRepalceTo)
    {
        short pos = S1.find(StringToReplace);

        while (pos != std::string::npos)
        {
            S1 = S1.replace(pos, StringToReplace.length(), sRepalceTo);
            pos = S1.find(StringToReplace);//find next 
        }
        return S1;
    }

    string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
        vector<string> vString = SplitString(S1, " ");
        for (string& s : vString)

            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }

        return JoinString(vString, " ");
    }

    string RemovePunctuationsFromString(string S1)
    {
        string S2 = "";

        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }
        return S2;
    }

    struct sClient
    {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double AccountBalance;
    };

    sClient ReadNewClient()
    {
        sClient Client;


        cout << "Please enter Account Number?";
        getline(cin >> ws, Client.AccountNumber);

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

    void PrintClientRecord(sClient Client)
    {
        cout << "\n\nThe following is the extracted client record:\n";
        cout << "\nAccout Number: " << Client.AccountNumber;
        cout << "\nPin Code     : " << Client.PinCode;
        cout << "\nName         : " << Client.Name;
        cout << "\nPhone        : " << Client.Phone;
        cout << "\nAccount Balance: " << Client.AccountBalance;

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

    void AddNewClient()
    {
        sClient Client;
        Client = ReadNewClient();
        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

    }

    void AddClient()
    {
        char AddMore = 'Y';

        do
        {
            system("cls");
            cout << "Adding New Clients.\n\n";

            AddNewClient();
            cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
            cin >> AddMore;

        } while (toupper(AddMore) == 'Y');

    }
    void PrintClientRecord2(sClient Client)
    {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(40) << left << Client.Name;
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

    void PrintAllClientsData(vector <sClient> vClients)
    {
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

        for (sClient Client : vClients)
        {
            PrintClientRecord2(Client);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

}