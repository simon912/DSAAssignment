#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include "Dictionary.h"
#include "List.h"
#include "Account.h"
#include "Topic.h"
#include "Stack.h"
#include "Post.h"

Account account;
Topic topic;
Dictionary<string> accountDictionary;
List<Topic> topicList;
Dictionary<Post> postList;
string option;
bool loggedIn;

void MainMenu();
void ReadFromAccount();
void ReadFromTopic();
void Login();
void Register();
void ViewAllTopic();
void createTopic();
void displayTopic(int index);
void loadPersistentData();
void readFromPosts();
void loggedInMenu();
void writeAllTopics();

void centerAlignText(string input, bool hasBox);

int main()
{
    // Load the data
    loadPersistentData();

    while (true)
    {
        MainMenu();
        cin >> option;
        // Login 
        if (option == "1")
        {
            Login();
            
            while (loggedIn == true) {
                loggedInMenu();
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

void loadPersistentData() {
    ReadFromAccount();
    ReadFromTopic();
    readFromPosts();
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
    ifstream file("Data/topicdata.tsv"); // Open the file
    string line;

    // Check if the file is open
    if (file.is_open()) {
        // Read the file line by line
        while (getline(file, line)) {
            string component;
            istringstream stream(line);

            bool isTopicTitle = true;

            Topic topic;

            while (getline(stream, component, '\t')) {
                if (isTopicTitle) {
                    isTopicTitle = false;
                    topic.setTopicName(component);
                } else {
                    topic.postIDs.push(component);
                }
            }

            topicList.add(topic);
        }
        
        file.close();
    } else {
        cout << "Could not read posts.csv" << endl;
    }
}

void readFromPosts() {
    ifstream file("Data/posts.tsv"); // Open the file
    string line;

    // Check if the file is open
    if (file.is_open()) {
        // Read the file line by line
        while (getline(file, line)) {
            string component;
            istringstream stream(line);

            int counter = 0;

            string postID;
            Post post;

            while (getline(stream, component, '\t')) {
                switch (counter)
                {
                case 0: // postid
                    postID = component;
                    break;
                case 1: // authorid
                    post.setAuthor(component);
                    break;
                case 2: // content
                    post.setContent(component);
                    break;
                case 3: // votes
                    post.setVotes(stoi(component));
                    break;
                default: // append to repliesIDs
                    post.replyIDs.enqueue(component);
                    break;
                }

                counter++;
            }

            postList.add(postID, post);
        }
        
        file.close();
    } else {
        cout << "Could not read posts.csv" << endl;
    }
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
        centerAlignText("Welcome, " + account.getUserID(), false);
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

// Create Topic
void createTopic()
{
    string topicName;
    cout << "Creating new topic...\n";
    cout << "Name the topic you want to create: \n";
    // Accepts a string with spacing
    cin.ignore();
    getline(cin, topicName);

    // topic.WriteToTopic((topicList.getLength()-1) + 1, topicName);
    topicList.add(Topic(topicName));
    writeAllTopics();
}

void writeAllTopics() {
    string data = "";
    ofstream file("Data/topicdata.tsv");

    for (int i = 0; i < topicList.getLength(); i++)
    {
        Topic topic = topicList.get(i);
        string topicName = topic.getTopicName();

        data += topicName;

        Stack tempStack;
        
        while (!topic.postIDs.isEmpty()) {
            string item;
            topic.postIDs.pop(item);
            data += "\t" + item;
            tempStack.push(item);
        }
        
        while (!tempStack.isEmpty()) {
            string item;
            tempStack.pop(item);
            topic.postIDs.push(item);
        }

        data += "\n";
    }

    // Check if the file is open
    if (file.is_open()) {
        
        // Write the data to the file
        file << data;

        // Close the file
        file.close();
    }
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

void loggedInMenu() {
    // Viewing the Forum
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "===================================================================" << endl;
    cout << "[0] Create a new topic" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "Explore the forum!" << endl;
    topicList.printTopic();
    cout << "-------------------------------------------------------------------" << endl;
    cout << "Any other key to log out." << endl;
    cout << "===================================================================" << endl;
    cout << "Type your option and press enter: ";
    
    int value;
    if (cin >> value && value <= topicList.getLength()) {
        if (value == 0) {
            createTopic();
        } else {
            displayTopic(value - 1);
        }
    } else {
        // input was invalid
        cout << "===================================================================" << endl;
        cout << "Logging out... Bye!" << endl;
        cout << "===================================================================" << endl;
        cin.clear();
        loggedIn = false;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void displayTopic(int index) {
    Topic currentTopic = topicList.get(index);

    cout << endl << endl;
    cout << "===================================================================" << endl;
    centerAlignText(currentTopic.getTopicName(), true);
    cout << "===================================================================" << endl;
    currentTopic.postIDs.displayContents(postList);
}

void centerAlignText(string input, bool hasBox) {
    int viewportWidth = 67;
    int leadingSpaceCount = (viewportWidth - input.length()) / 2 - (hasBox ? 1 : 0);
    int trailingSpaceCount = viewportWidth - leadingSpaceCount - input.length() - (hasBox ? 1 : 0) - 1;

    if (hasBox) { cout << "|"; }
    for (int i = 0; i < leadingSpaceCount; ++i) {
        cout << " ";
    }
    cout << input;
    for (int i = 0; i < trailingSpaceCount; ++i) {
        cout << " ";
    }
    if (hasBox) { cout << "|"; }
    cout << endl;
}