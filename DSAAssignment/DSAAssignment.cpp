#include <iostream>
#include "Dictionary.h"
void MainMenu()
{
    cout << "========================\n";
    cout << "| Welcome to the Forum |\n";
    cout << "========================\n";
    cout << "1) Log In\n";
    cout << "2) Register\n";
    cout << "Press any key to exit\n";
    cout << "Type your option: ";
}

int main()
{
    Dictionary account;
    // Temporarily store Account for testing
    account.add("User1", "password1");
    account.add("User2", "password2");
    int option = 1;
    while (option != 0)
    {
        MainMenu();
        cin >> option;
        string userid;
        string password;
        // Login 
        if (option == 1)
        {
            cout << "Please enter your User ID: ";
            cin >> userid;
            cout << "Please enter your Password: ";
            cin >> password;
            // Validate user id and password in hash table
            if (account.get(userid) == password)
            {
                cout << "User is found\n";
                cout << "Welcome, " << userid << "\n";
                cout << "1) View all topics and posts\n";
                cout << "2) Create a new topic\n";
                cout << "Press any key to exit\n";
                cout << "Type your option: ";
                cin >> option;
                // View all Topic (Linked List???)
                if (option == 1)
                {
                    return false;
                }
                // Create New Topic
                else if (option == 2)
                {
                    return false;
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
                cout << "Register\n";
                cout << "Key in your User ID: ";
                cin >> userid;
                cout << "Key in your Password: ";
                cin >> password;
                account.add(userid, password);
            }
    }
    cout << "Goodbye!";
    return 0;
}

