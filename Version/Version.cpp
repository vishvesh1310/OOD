/////////////////////////////////////////////////////////////////////
// Version.cpp - Implements functions of the version package                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Version.h"

#define TEST_VERSION
#ifdef TEST_VERSION

int main()
{
	maximum("DbCore::DbCore.h.1", 0, 0);
	split("DbCore::DbCore.h.1", '.');
	return 0;
}
#endif
