/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Post.h - Definition of Post class
#pragma once
#include<string>
#include<iostream>
#include "Queue.h"
using namespace std;

class Post 
{
private:
	string postName;
	string content;
	string author;
	int votes;
public:
	Queue replyIDs;
	/*
	* Description: Initialise the Post class
	*/
	Post();
	/*
	* Desciption: Overload Post class function
	* Input: Post Name, Content, Author
	* Output: None
	*/
	Post(string postName, string content, string author);
	/*
	* Description: gets the Post Name from the Post
	* Input: None
	* Output: Post Name
	*/
	string getPostName();
	/*
	* Description: set a Post Name for that Post
	* Input: Post Name
	* Output: None
	*/
	void setPostName(string postName);
	/*
	* Description: gets the Content from the Post
	* Input: None
	* Output: Content
	*/
	string getContent();
	/*
	* Description: set the Content for that Post
	* Input: Content
	* Output: None
	*/
	void setContent(string content);
	/*
	* Description: gets the Author from the Post
	* Input: None
	* Output: Author
	*/
	string getAuthor();
	/*
	* Description: set the Author for that Post
	* Input: Author
	* Output: None
	*/
	void setAuthor(string authorID);
	/*
	* Description: gets the amount of Votes from the Post
	* Input: None
	* Output: Vote
	*/
	int getVotes();
	/*
	* Description: set the Vote for that Post
	* Input: Vote
	* Output: None
	*/
	void setVotes(int votes);
};