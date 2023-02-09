// Topic.cpp - Implementation of Topic class
#include "Topic.h"
#include "List.h"
#include <fstream>;

Topic::Topic() {}
Topic::Topic(string tName) {
	topicName = tName;
}

void Topic::setTopicName(string tName) {
	topicName = tName;
}

string Topic::getTopicName() {
	return topicName;
}

bool Topic::hasPinnedPost() {
	return pinnedPost != string();
}

string Topic::getPinnedPost() {
	return pinnedPost;
}

void Topic::setPinnedPost(string postID) {
	pinnedPost = postID;
}