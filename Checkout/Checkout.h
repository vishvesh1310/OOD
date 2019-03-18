#pragma once
/////////////////////////////////////////////////////////////////////
// Checkout.h - Implements checkout functionalities of the files                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/* Package Operations :
*------------------ -
This package contains function checkout for checking out a file 
* Required Files :
*-------------- -
*Executive.h,Payload.h,FileSystem.h,Browse.h
*/
/* Maintenance History :
*ver 1.0 : 6th Mar 2018
* -first release
*/
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
//#include "../CppNoSqlDb"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include "../Version/Version.h"
#include "../Checkin/Checkin.h"

using namespace NoSqlDb;


/*Checkout a file from remote to local repository*/
std::string checkOut(std::string x,DbCore<PayLoad> db)
{
	
	
	
	size_t lastindex = x.find_last_of(".");
	std::string name1 = x.substr(0, lastindex);
	
	return name1;
}
