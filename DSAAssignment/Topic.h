#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
using namespace std;

class Topic
{
private:
	string content;

public:
	Topic();
	Topic(string content);
	void addTopic(string content);
};
