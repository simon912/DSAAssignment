/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Account.h - Definition of Account class
#pragma once
#include<string>
#include<iostream>
using namespace std;

class Account
{
private:
	string userid;
	string password; 

public:
	/*
	* Description: Initialise the Topic class
	*/
	Account();
	/*
	* Desciption: Overload Topic class function
	* Input: User ID, Password
	* Output: None
	*/
	Account(string uid, string psw);
	/*
	* Description: set a User ID for the Account
	* Input: User ID
	* Output: None
	*/
	void setUserID(string uid);
	/*
	* Description: gets the User ID from the Account
	* Input: None
	* Output: User ID
	*/
	string getUserID();
	/*
	* Description: set a Password for the Account
	* Input: Password
	* Output: None
	*/
	void setPassword(string psw);
	/*
	* Description: gets the Password from the Account
	* Input: None
	* Output: Password
	*/
	string getPassword();
	/*
	* Description: saves the Account data to account.csv
	* Input: User ID and Password
	* Output: csv file gets updated with the User ID and Password
	*/
	void WriteToAccount(string uid, string psw);
};
