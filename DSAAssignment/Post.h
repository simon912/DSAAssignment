#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
#include "Queue.h"
using namespace std;

class Post 
{
private:
	string postName;
	string content;
	string author;
	int votes;
public:
	Queue replyIDs;

	Post();
	Post(string topic, string postName, string content, string author);

	string getPostName();
};