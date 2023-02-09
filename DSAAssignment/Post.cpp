/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Post.cpp - Implementation of Post class
#include "Post.h"

Post::Post() {}
Post::Post(string postName, string content, string author) {
	postName = postName;
	content = content;
	author = author;
	votes = 0;
}

string Post::getPostName() {
	return postName;
}

void Post::setPostName(string postName) {
	this->postName = postName;
}

string Post::getContent() {
	return content;
}

void Post::setContent(string content) {
	this->content = content;
}

string Post::getAuthor() {
	return author;
}

void Post::setAuthor(string authorID) {
	this->author = authorID;
}

int Post::getVotes() {
	return votes;
}
void Post::setVotes(int votes) {
	this->votes = votes;
}