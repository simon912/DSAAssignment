#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <random>

#include "Dictionary.h"
#include "List.h"
#include "Account.h"
#include "Topic.h"
#include "Stack.h"
#include "Post.h"

Account account;
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
void createTopic();
void displayTopic(int index);
void loadPersistentData();
void readFromPosts();
void loggedInMenu();
void writeAllTopics();
void writePost(string key);

void likePost(string postID);
void viewReplies(string postID);

string generateRandomID(std::size_t n);

void centerAlignText(string input, bool hasBox);
void newPostInTopic(int index);
string getPostFromTopic(Topic topic, int index);
void displayPost(string postID);

void pinPost(int topicIndex);

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
                case 2: // post name
                    post.setPostName(component);
                    break;
                case 3: // content
                    post.setContent(component);
                    break;
                case 4: // votes
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
    bool showTopic = true;

    while (showTopic) {
        Topic currentTopic = topicList.get(index);
        
        cout << endl << endl;
        cout << "===================================================================" << endl;
        centerAlignText(currentTopic.getTopicName(), true);
        cout << "===================================================================" << endl;
        if (currentTopic.hasPinnedPost()) {
            cout << "[-1] PINNED POST" << endl;
            Post pinnedPost = postList.get(currentTopic.getPinnedPost());

            cout << "     " + pinnedPost.getPostName() << endl;
            cout << "     " + pinnedPost.getContent() << endl << endl;
            cout << "     By " + pinnedPost.getAuthor() << endl << endl;

            cout << "[-2] Remove pinned post" << endl;
        } else {
            cout << "[-1] Pin/Stick a post" << endl;
        }
        
        cout << "-------------------------------------------------------------------" << endl;
        cout << "[0] Create a new post in " + currentTopic.getTopicName() << endl;
        cout << "-------------------------------------------------------------------" << endl;
        currentTopic.postIDs.displayContents(postList);
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Any other number to go back." << endl;
        cout << "===================================================================" << endl;
        cout << "Type your option and press enter: ";

        int value;
        if (cin >> value && value <= currentTopic.postIDs.getLength()) {
            if (value == 0) {
                // New Post
                newPostInTopic(index);
            } else if (value > 0) {
                string postID = getPostFromTopic(currentTopic, value - 1);
                displayPost(postID);
            } else if (value == -1) {
                // Stick sticky post stickily
                if (currentTopic.hasPinnedPost()) {
                    // Open pinned post
                    displayPost(currentTopic.getPinnedPost());
                } else {
                    // Select a post number to pin
                    pinPost(index);
                }
            } else if (value == -2) {
                currentTopic.setPinnedPost(string());
                topicList.replace(index, currentTopic);
            } else {
                showTopic = false;
            }
        }
    }
}

void pinPost(int topicIndex) {
    Topic currentTopic = topicList.get(topicIndex);
    cout << "Which post would you like to pin? " << endl;
    int value;
    if (cin >> value && value <= currentTopic.postIDs.getLength() && value > 0) {
        string postID = getPostFromTopic(currentTopic, value - 1);
        currentTopic.setPinnedPost(postID);
    }
    topicList.replace(topicIndex, currentTopic);
}

void newPostInTopic(int index) {
    Topic topic;
    topicList.get(index, &topic);

    string postID = generateRandomID(32);
    cout << "===================================================================" << endl;
    centerAlignText("Create New Post", true);
    centerAlignText(topic.getTopicName(), true);
    cout << "===================================================================" << endl;
    cout << "Title: ";

    string postName;
    cin >> postName;
    // getline(cin, postName);

    string content;
    cout << "Contents: ";
    cin >> content;
    // getline(cin, content);

    Post post = Post(postName, content, account.getUserID());
    
    post.setPostName(postName);
    post.setContent(content);
    post.setAuthor(account.getUserID());
    post.setVotes(0);

    cout << "===================================================================" << endl;
    cout << "Created new post" << endl; 
    cout << postID << endl; 
    cout << "===================================================================" << endl;

    topic.postIDs.push(postID);
    
    postList.add(postID, post);

    topicList.replace(index, topic);

    cout << topicList.get(index).postIDs.getLength() << endl;

    writeAllTopics();
    writePost(postID);
}

string getPostFromTopic(Topic topic, int index) {
    Stack tempStack;
    Post post;
    int counter = 0;

    while (!topic.postIDs.isEmpty()) {
        string item;
        topic.postIDs.getTop(item);
        topic.postIDs.pop();
        tempStack.push(item);

        if (counter == index) {
            return item;
            break;
        }
        
        counter++;
    }

    while (!tempStack.isEmpty()) {
        string item;
        tempStack.getTop(item);
        tempStack.pop();
        topic.postIDs.push(item);
    }

    return "";
}

void displayPost(string postID) {
    bool escapePost = false;

    while (!escapePost) {
        Post post = postList.get(postID);
        cout << "===================================================================" << endl;
        centerAlignText(post.getPostName(), true);
        centerAlignText("By " + post.getAuthor(), true);
        centerAlignText("-----------------------------------------------------------------", true);
        centerAlignText(to_string(post.getVotes()) + " like(s)", true);
        cout << "===================================================================" << endl;
        cout << post.getContent() << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "[0] Like Post" << endl;
        cout << "[1] View Replies (" + to_string(post.replyIDs.getLength()) + ")" << endl;

        if (account.getUserID() == post.getAuthor()) {
            cout << endl;
            cout << "[2] Edit Post" << endl;
            cout << "[3] Delete Post" << endl;
        }
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Any other number to go back." << endl;
        cout << "===================================================================" << endl;
        cout << "Type your option and press enter: ";

        int value;
        cin >> value;

        switch (value)
        {
        case 0:
            // Like post
            likePost(postID);
            break;
        case 1:
            // View replies post
            viewReplies(postID);
            break;
        case 2:
            // Edit post
            if (account.getUserID() == post.getAuthor()) {
                
            }
            break;
        case 3:
            // Delete post
            if (account.getUserID() == post.getAuthor()) {

            }
            escapePost = true;
            break;
        default:
            escapePost = true;
            break;
        }
    }
}

void likePost(string postID) {
    Post post = postList.get(postID);
    post.setVotes(post.getVotes() + 1);

    postList.remove(postID);

    postList.add(postID, post);
}

void viewReplies(string postID) {
    bool isShowingReplies = true;
    while (isShowingReplies) {
        Post post = postList.get(postID);
        Queue replyQueue = post.replyIDs;
        
        Queue tempQueue;
        cout << replyQueue.getLength() << " replies"<< endl;
        while (!replyQueue.isEmpty()) {
            string item;
            replyQueue.dequeue(item);
            
            Post reply = postList.get(item);

            string authorLabel = "By " + reply.getAuthor();
            int leadingSpaces = 63 - authorLabel.length();

            cout << reply.getContent() << endl;
            for (int i = 0; i < leadingSpaces; i++)
            {
                cout << " ";
            }
            cout << authorLabel << endl;
            cout << "-------------------------------------------------------------------" << endl;
            tempQueue.enqueue(item);
        }
        
        while (!tempQueue.isEmpty()) {
            string item;
            tempQueue.dequeue(item);
            replyQueue.enqueue(item);
        }

        string value;
        cout << "Reply (type Q to go back): ";
        cin >> value;

        if (value == "Q") {
            // go back
            isShowingReplies = false;
        } else {
            string newPostID = generateRandomID(32);
            
            replyQueue.enqueue(newPostID);
            post.replyIDs = replyQueue;

            Post newPost;
            newPost.setAuthor(account.getUserID());
            newPost.setContent(value);

            postList.add(newPostID, newPost);
            
            postList.remove(postID);
            postList.add(postID, post);

            writePost(postID);
        }
    }
}

void writePost(string key) {
    Post post = postList.get(key);
    string value = key + "\t" + post.getAuthor() + "\t" + post.getPostName() + "\t" + post.getContent() + "\t" + to_string(post.getVotes());
    ofstream file;
    file.open("Data/posts.tsv", ios::app);
    if (file.is_open()) {
        file << endl << value << endl;
        file.close();
    } else {
        cout << "Could not open file for appending." << endl;
    }
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

string generateRandomID(std::size_t n) {
    constexpr char chars[] = "abcdefghijklmnopqrstuvwxyz";
    constexpr std::size_t size = sizeof(chars) - 1;
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, size - 1);
    std::string result;
    for (std::size_t i = 0; i < n; ++i) {
        result += chars[dist(engine)];
    }
    return result;
}