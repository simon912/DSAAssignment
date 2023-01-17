// Account.cpp - Implementation of Account class (by Simon)
#include "Account.h"

Account::Account() {}

Account::Account(string uid, string psw)
{
	userid = uid;
	password = psw;
}
void Account::setUserID(string uid) { userid = uid; }
string Account::getUserID() { return userid; }
void Account::setPassword(string psw) { password = psw; }
string Account::getPassword() { return password; }
