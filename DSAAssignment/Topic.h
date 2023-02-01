#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
using namespace std;

class Topic
{
private:
	int topicid;
	string content;

public:
	Topic();
	Topic(int topicid, string content);
};
