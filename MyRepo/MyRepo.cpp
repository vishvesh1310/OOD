/////////////////////////////////////////////////////////////////////
// MyRepo.cpp - Implements functions of the MyRepo package                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyRepo.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"

#define TEST_MyRepo
#ifdef TEST_MyRepo

int main()
{
	main_db();
	cout_file();
	cin_ntexist();
	cin_existopen();
	cin_existclose();
	browser_files();
	return 0;
}
#endif


