#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
using namespace std;

class Post 
{
private:
	string topic;
	string postName;
	string content;
	string author;
public:
	Post();
	Post(string topic, string postName, string content, string author);
};