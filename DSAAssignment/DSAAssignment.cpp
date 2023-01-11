#include <iostream>
#include "Dictionary.h"

int main()
{
    Dictionary account;
    account.add("User1", "password1");
    account.add("User2", "password2");
    cout << "Welcome to the Forum\n";
    cout << "1) Log In\n";
    cout << "2) Register\n"; // not done 
    cout << "Press any other key to exit\n";
    cout << "Type your option: ";
    int option;
    cin >> option;
    while (true)
    {
        if (option == 1)
        {
            string userid;
            string password;
            cout << "Key in your User ID: ";
            cin >> userid;
            cout << "Key in your Password: ";
            cin >> password;
            if (account.get(userid) == password)
            {
                cout << "User is found\n";
                cout << "1) View all topics and posts\n";
                cout << "2) Create a new topic\n";
            }
            else
            {
                cout << "User does not exist\n";
            }
        }
        cout << "Goodbye!";
        return false;
    }
    
}


