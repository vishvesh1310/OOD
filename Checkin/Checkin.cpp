/////////////////////////////////////////////////////////////////////
// Checkin.cpp - Implements functions of the checkin package                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "../FileSystemDemo/FileSystem.h"
#include "../CppNoSqlDb/DbCore/DbCore.h"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
#include "Checkin.h"


#define TEST_CHECKIN
#ifdef TEST_CHECKIN

int main()
{
	
	checkIn("DbCore.h",db);
	
    return 0;
}
#endif
