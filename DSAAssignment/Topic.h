#pragma once
// Topic.h - Definition of Account class

#include<string>
#include<iostream>
#include"Stack.h"
using namespace std;

class Topic
{
private:
	string topicName;

public:
	Stack postIDs;

	Topic();
	Topic(string topicName);
	void setTopicName(string topicName);
	string getTopicName();
	void setTopicID(int topicid);
	int getTopicID();
	void WriteToTopic(int topicid, string topicName);
	void RemoveTopic();
};
