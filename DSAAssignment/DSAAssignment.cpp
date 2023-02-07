#include <iostream>
#include <fstream>
#include <cstdio>
#include "Dictionary.h"
#include "List.h"
#include "Account.h"
#include "Topic.h"

Account account;
Topic topic;
Dictionary<string> accountDictionary;
List<string> topicList;
List<string> postList;
string option;
bool loggedIn;

void MainMenu();
void ReadFromAccount();
void ReadFromTopic();
void Login();
void Register();
void ViewAllTopic();
void CreateTopic();

int main()
{
    // Load the data
    ReadFromAccount();
    ReadFromTopic();
    while (true)
    {
        MainMenu();
        cin >> option;
        // Login 
        if (option == "1")
        {
            Login();
            if (loggedIn == true)
            {
                while (loggedIn == true)
                {
                    // Viewing the Forum
                    cout << endl;
                    cout << "What would you like to do?\n";
                    cout << "1) View all topics and posts\n";
                    cout << "2) Create a new topic\n";
                    cout << "Press any key to log out\n";
                    cout << "Type your option: ";
                    cin >> option;
                    // Topic and Post
                    // View all Topic (Linked List)
                    if (option == "1")
                    {
                        ViewAllTopic();
                        // put the post list here for that topic i guess
                    }
                    // Create New Topic
                    else if (option == "2")
                    {
                        CreateTopic();
                    }
                    else
                    {
                        cin.clear();
                        cout << endl;
                        cout << "Logging out...\n";
                        cout << endl;
                        loggedIn = false;
                    }
                }
            }
        }
        // Register Account
        else if (option == "2")
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
    cout << "===================================================================\n";
    cout << "Type your option or press any key to exit: ";
}

// Load account data from csv file
void ReadFromAccount()
{
    ifstream allAccount;
    allAccount.open("Data/accountdata.csv");
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
// Load topic data from csv file
void ReadFromTopic()
{
    ifstream allTopic;
    allTopic.open("Data/topicdata.csv");
    if (allTopic.fail())
    {
        cout << "File can't be opened\n";
    }
    allTopic.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the first line of the data file
    while (allTopic.peek() != EOF) {
        string topicid;
        string topic;
        getline(allTopic, topicid, ',');
        getline(allTopic, topic, '\n');
        topicList.add(topic);
    }
    allTopic.close();
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
    cin >> option;
    account.setUserID(option);
    getline(cin, option);
    cout << "Please enter your Password: ";
    cin >> option;
    account.setPassword(option);
    getline(cin, option);
    // Verify if user id and password is in hash table
    if (accountDictionary.loginStatus(account.getUserID(), account.getPassword()))
    {
        loggedIn = true;
        cout << endl;
        cout << "===================================================================\n";
        cout << "                        User is found                            \n";
        cout << "                        Welcome, " << account.getUserID() << "                 \n";
        cout << "===================================================================\n";
    }
    else if (account.getUserID().find_first_not_of("\t\n ") != string::npos)
    {
        loggedIn = false;
        cout << "Invalid credential\n";
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
    topicList.printTopic();
    cout << "1) View a topic\n";
    cout << "2) Sticky a topic\n";
    cout << "Press any key to go back\n";
    cout << "What do you want to do?: ";
    cin >> option;
    cout << endl;
    int selectedTopic;
    if (option == "1")
    {
        cout << "Enter the topic number that you want to view\n";
        
        cin >> selectedTopic;
        if (cin.fail())
        {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        for (int i = 0; i < topicList.getLength(); i++)
        {
            if (selectedTopic == i)
            {
                cout << "You have entered the topic, " << topicList.get(i) << endl;
                cout << "Here are the list of post for this topic: " << endl;
                return;

            }
            else if (selectedTopic >= topicList.getLength() || selectedTopic < 1)
            {
                cout << "Invalid input!\n";
                break;
            }
            
        }
    }
    else if (option == "2")
    {
        cout << "What topic do you want to pin?: \n";
        cin >> selectedTopic;
        if (cin.fail())
        {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        topicList.shifttoFirst(selectedTopic);
        

    }
    else
    {
        cout << "Going back...\n";
    }
    
}

// Create Topic
void CreateTopic()
{
    string topicName;
    cout << "Creating new topic...\n";
    cout << "Name the topic you want to create: \n";
    // Accepts a string with spacing
    cin.ignore();
    getline(cin, topicName);

    topic.WriteToTopic((topicList.getLength()-1) + 1, topicName);
    topicList.add(topicName);
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
    cin >> option;
    cin.ignore();
    getline(cin, option);
    account.setUserID(option);
    cout << "Enter your Password: ";
    cin >> option;
    cin.ignore();
    getline(cin, option);
    account.setPassword(option);
    string userid = account.getUserID();
    string password = account.getPassword();
    if (accountDictionary.ifKeyExist(userid))
    {
        cout << "The User ID is already in use!\n";
        cout << endl;
    }
    else if (account.getUserID().find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != string::npos || account.getUserID().find_first_not_of("\t\n ") != string::npos)
    {
        loggedIn = false;
        cout << "No special character or spacing in your User ID!\n";
    }
    else
    {
        account.WriteToAccount(userid, password);
        accountDictionary.add(userid, password);
        cout << "Account has been successfully created!\n";
        cout << endl;
    }
}