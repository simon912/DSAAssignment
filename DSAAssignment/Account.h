#pragma once
// Account.h - Definition of Account class (by Simon)

#include<string>
#include<iostream>
using namespace std;

class Account
{
private:
	string userid;
	string password; 

public:
	Account();
	Account(string uid, string psw);
	void setUserID(string uid);
	string getUserID();
	void setPassword(string psw);
	string getPassword();
};
