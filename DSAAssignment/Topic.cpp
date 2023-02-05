// Topic.cpp - Implementation of Topic class
#include "Topic.h"
#include "List.h"

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

