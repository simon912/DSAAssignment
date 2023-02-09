/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
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