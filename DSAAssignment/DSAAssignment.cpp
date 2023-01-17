#include <iostream>
#include <fstream>
#include <sstream> // for loading data file
#include <vector> // for loading data file
#include "Dictionary.h"
#include "List.h"
#include "Account.h"

void MainMenu()
{
    cout << "========================\n";
    cout << "| Welcome to the Forum |\n";
    cout << "========================\n";
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
/*
// Load data from csv file
void ReadFromAccount()
{
    Dictionary account;
    ifstream allAccount;
    allAccount.open("accountdata.csv");
    if (allAccount.fail())
    {
        cout << "File can't be opened\n";
    }
    allAccount.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the first line of the data file
    while (allAccount.peek() != EOF) {
        string userid, password;
        string temp, temp2;
        getline(allAccount, userid, ',');
        getline(allAccount, password, '\n');
        temp = userid + '\n';
        temp2 = password + '\n';
        cout << temp;
        cout << temp2;
        account.add(temp, temp2);
    }
    allAccount.close();
}*/

int main()
{
    Dictionary accountDictionary;
    List topic;
    List post;
    // Load from Account file
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
    // Temporarily store Topic for testing
    topic.add("Hash Table");
    topic.add("Linked List");
    int option = 1;
    while (true)
    {
        MainMenu();
        cin >> option;
        string userid;
        string password;
        // Login 
        if (option == 1)
        {
            Account accountLogin(userid, password);
            cout << "Please enter your User ID: ";
            cin >> userid;
            accountLogin.setUserID(userid);
            cout << "Please enter your Password: ";
            cin >> password;
            accountLogin.setPassword(password);
            string useridCompare = accountLogin.getUserID();
            string passwordCompare = accountLogin.getPassword();
            // Verify if user id and password is in hash table
            if (accountDictionary.get(useridCompare) == passwordCompare)
            {
                cout << "===========================\n";
                cout << "|      User is found      |\n";
                cout << "|      Welcome, " << userid << "     |\n";
                cout << "===========================\n";
                while (true)
                {
                    // Viewing the Forum
                    cout << "1) View all topics and posts\n";
                    cout << "2) Create a new topic\n";
                    cout << "Press any key to exit\n";
                    cout << "Type your option: ";
                    cin >> option;
                    // Topic and Post
                    // View all Topic (Linked List)
                    if (option == 1)
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
                    // Create New Topic
                    else if (option == 2)
                    {
                        string strtopic;
                        cout << "Creating new topic...\n";
                        cout << "Name the topic you want to create: \n";
                        // Accepts a string with spacing
                        cin.ignore();
                        getline(cin, strtopic);
                        topic.add(strtopic);
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                cout << "Invalid credential\n";
                continue;
            }

        }
        // Register Account
        else if (option == 2)
            {
                Account accountRegister(userid, password);
                cout << "Register\n";
                cout << "Key in your User ID: ";
                cin >> userid;
                accountRegister.setUserID(userid);
                cout << "Key in your Password: ";
                cin >> password;
                accountRegister.setPassword(password);
                string useridRegister = accountRegister.getUserID();
                string passwordRegister = accountRegister.getPassword();
                WriteToAccount(useridRegister, passwordRegister);
                accountDictionary.add(useridRegister, passwordRegister);
            }
    }
    return false;
}

