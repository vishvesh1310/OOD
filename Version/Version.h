#pragma once
/////////////////////////////////////////////////////////////////////
// Version.h - Implements version functionalities of the files like split and max for updating the version number                 //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/* Package Operations :
*------------------ -
This package contains functions for finding maximum version number and splitting a string according to delimeter
* Required Files :
*-------------- -
*Executive.h,string.h
*/
/* Maintenance History :
*ver 1.0 : 6th Mar 2018
* -first release
*/
#include "stdafx.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
#include "string"
#include "string.h"

/*This will make a split function that can be used to split a string according to a delimeter*/
std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

/*This will give the maximum version of the file present in the remote repository*/
int maximum(std::string name,int max,int b)
{
	std::vector<std::string> arr;
	arr = split(name, '.');
	b = stoi(arr[2]);
	if (b > max) max = b;
	return max;
}