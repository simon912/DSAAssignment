/*
=================================
Group 10
	  Name of Member 1: Simon Kwek
Student ID of Member 1: S10228098J
	  Name of Member 2: Yee Jia Chen
Student ID of Member 2: S10219344C
*/
// Dictionary.h - Specification of Dictionary ADT (Pointer-based)
// Topic.h - Definition of Topic class
#pragma once
#include<string>
#include<iostream>
#include"Stack.h"
using namespace std;

class Topic
{
private:
	string topicName;
	string pinnedPost;

public:
	Stack postIDs;
	/*
	* Description: Initialise the Account class
	*/
	Topic();
	/*
	* Desciption: Overload Topic class function
	* Input: Topic Name
	* Output: None
	*/
	Topic(string topicName);
	/*
	* Description: set a Topic Name for the Topic
	* Input: Topic Name
	* Output: None
	*/
	void setTopicName(string topicName);
	/*
	* Description: gets the Topic Name for the Topic
	* Input: None
	* Output: Topic Name
	*/
	string getTopicName();
	/*
	* isnt used
	*/
	void WriteToTopic(int topicid, string topicName);
	/*
	* isnt used
	*/
	void RemoveTopic();
	/*
	* Description: gets the Pinned Post for that Topic
	* Input: None
	* Output: Post that is Pinned
	*/
	string getPinnedPost();
	/*
	* Description: sets the Pinned Post for that Topic
	* Input: Pinned Post
	* Output: None
	*/
	void setPinnedPost(string postID);
	/*
	* Description: checks for Pinned Post for that Topic
	* Input: None
	* Output: None
	*/
	bool hasPinnedPost();
};
