// Topic.cpp - Implementation of Topic class
#include "Topic.h"
#include "List.h"
#include <fstream>;

Topic::Topic() {}
Topic::Topic(int tid, string tName) {
	topicid = tid;
	topicName = tName;
}
void Topic::setTopicName(string tName) {
	topicName = tName;
}

string Topic::getTopicName() {
	return topicName;
}

void Topic::setTopicID(int tid) {
	topicid = tid;
}

int Topic::getTopicID() {
	return topicid;
}

void Topic::WriteToTopic(int topicid, string topicName)
{
	fstream fout;
	fout.open("Data/topicdata.csv", ios::out | ios::app);
	fout << topicid << "," << topicName << "\n";
}
