#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
using namespace std;

class Topic
{
private:
	int topicid;
	string topicName;

public:
	Topic();
	Topic(int topicid, string topicName);
	void setTopicName(string topicName);
	string getTopicName();
	void setTopicID(int topicid);
	int getTopicID();

};
