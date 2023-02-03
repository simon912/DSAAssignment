#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "List.h"
#include "Account.h"

Account account;
Dictionary<string> accountDictionary;
List topic;
List post;
string input;
int option = 1;
bool loggedIn;

void MainMenu();
void ReadFromAccount();
void Login();
void Register();
void ViewAllTopic();
void CreateTopic();

int main()
{
    // Load the data
    ReadFromAccount();
    // Temporarily store Topic for testing
    topic.add("Hash Table");
    topic.add("Linked List");
    while (true)
    {
        MainMenu();
        cin >> option;
        // Login 
        if (option == 1)
        {
            Login();
            if (loggedIn == true)
            {
                while (loggedIn == true)
                {
                    // Viewing the Forum
                    cout << "1) View all topics and posts\n";
                    cout << "2) Create a new topic\n";
                    cout << "Press any other number to log out\n";
                    cout << "Type your option: ";
                    cin >> option;
                    // Topic and Post
                    // View all Topic (Linked List)
                    if (option == 1)
                    {
                        ViewAllTopic();
                    }
                    // Create New Topic
                    else if (option == 2)
                    {
                        CreateTopic();
                    }
                    else
                    {
                        loggedIn = false;
                    }
                }
            }
        }
        // Register Account
        else if (option == 2)
        {
            Register();
        }
        else
        {
            break;
        }
    }
}

// The Main Menu that is displayed before the User logs in
void MainMenu()
{
    cout << "===================================================================\n";
    cout << "                                                                 \n";
    cout << "                     Welcome to the Forum                        \n";
    cout << "                                                                 \n";
    cout << "===================================================================\n";
    cout << "You need an account to access the forum\n";
    cout << "1) Log In\n";
    cout << "2) Register\n";
    cout << "Press any key to exit\n";
    cout << "Type your option: ";
}

// Write to csv file when user registered
void WriteToAccount(string userid, string password)
{
    fstream fout;
    fout.open("accountdata.csv", ios::out | ios::app);
    fout << userid << "," << password << "\n";
}

// Load data from csv file
void ReadFromAccount()
{
    ifstream allAccount;
    allAccount.open("accountdata.csv");
    if (allAccount.fail())
    {
        cout << "File can't be opened\n";
    }
    allAccount.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the first line of the data file
    while (allAccount.peek() != EOF) {
        string userid, password;
        getline(allAccount, userid, ',');
        getline(allAccount, password, '\n');
        accountDictionary.add(userid, password);
    }
    allAccount.close();
}
// Login Account
void Login()
{
    cout << endl;
    cout << "===================================================================\n";
    cout << "                                                                 \n";
    cout << "                          Logging in...                          \n";
    cout << "                                                                 \n";
    cout << "===================================================================\n";
    cout << "Please enter your User ID: ";
    cin >> input;
    account.setUserID(input);
    cout << "Please enter your Password: ";
    cin >> input;
    account.setPassword(input);
    string userid = account.getUserID();
    string password = account.getPassword();
    // Verify if user id and password is in hash table
    if (accountDictionary.loginStatus(userid, password))
    {
        loggedIn = true;
        cout << endl;
        cout << "===================================================================\n";
        cout << "                        User is found                            \n";
        cout << "                       Welcome, " << account.getUserID() << "                 \n";
        cout << "===================================================================\n";
    }
    else
    {
        loggedIn = false;
        cout << "Invalid credential\n";
    }
}

// View all Topic 
void ViewAllTopic()
{
    topic.printTopic();
    cin >> option;
    int topicSize = topic.getLength();
    for (int i = 0; i < topicSize; i++)
    {
        if (option == i)
        {
            cout << "You entered " << i << endl;
        }
    }
}

// Create Topic
void CreateTopic()
{
    string strtopic;
    cout << "Creating new topic...\n";
    cout << "Name the topic you want to create: \n";
    // Accepts a string with spacing
    cin.ignore();
    getline(cin, strtopic);
    topic.add(strtopic);
}
// Register Account
void Register()
{
    cout << endl;
    cout << "===================================================================\n";
    cout << "|                                                                 |\n";
    cout << "|                     Registering an account...                   |\n";
    cout << "|                                                                 |\n";
    cout << "===================================================================\n";
    cout << "Enter your User ID: ";
    cin >> input;
    account.setUserID(input);
    cout << "Enter your Password: ";
    cin >> input;
    account.setPassword(input);
    string userid = account.getUserID();
    string password = account.getPassword();
    if (accountDictionary.ifAccountExist(userid))
    {
        cout << "The UserID is already in use!\n";
    }
    else
    {
        WriteToAccount(userid, password);
        accountDictionary.add(userid, password);
        cout << "Account has been successfully created!\n";
        cout << endl;
    }
}