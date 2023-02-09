/*
=============================================
|	Group 10							    |
|	Name of Member 1: Simon Kwek			|
|	Student ID of Member 1 : S10228098J		|
|	Name of Member 2 : Yee Jia Chen			|
|	Student ID of Member 2 : S10219344C		|
=============================================
*/
// Account.cpp - Implementation of Account class
#include "Account.h"
#include <fstream>

Account::Account() {}
Account::Account(string uid, string psw) {
	userid = uid;
	password = psw;
}

void Account::setUserID(string uid) { userid = uid; }

string Account::getUserID() { return userid; }

void Account::setPassword(string psw) { password = psw; }

string Account::getPassword() { return password; }

void Account::WriteToAccount(string userid, string password)
{
    fstream fout;
    fout.open("Data/accountdata.csv", ios::out | ios::app);
    fout << userid << "," << password << "\n";
}

