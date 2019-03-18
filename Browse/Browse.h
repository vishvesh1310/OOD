#pragma once
/////////////////////////////////////////////////////////////////////
// Checkin.h - Implements browse functionalities of the files                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018//
//Source : Dr.Jim Fawcett                                            //
/////////////////////////////////////////////////////////////////////
/* Package Operations :
*------------------ -
This package contains functions for browsing various files and displaying according to name description etc
* Required Files :
*-------------- -
*Executive.h,Payload.h,FileSystem.h,Browse.h,Query.h,Process.h,Checkin.h
*/
/* Maintenance History :
*ver 1.0 : 6th Mar 2018
* -first release
*/
#include "stdafx.h"
#include "../CppNoSqlDb/Query/Query.h"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
#include "../Checkin/Checkin.h"
#include "../Process/Process/Process.h"

/*Provides the capability to locate files and view their contents according to name*/
void b_name(std::string x,DbCore<PayLoad> db)
{
	
	Conditions<PayLoad> conds1;
	conds1.name(x);
	Query<PayLoad> q1(db);
	q1.select(conds1).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" +x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}
	
}

/*Provides the capability to locate files and view their contents according to description*/
void b_description(std::string x,DbCore<PayLoad> db)
{
	
	Conditions<PayLoad> conds1;
	conds1.description(x);
	Query<PayLoad> q1(db);
	q1.select(conds1).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}

}
/*Provides the capability to locate files and view their contents according to children*/
void b_children(Keys x,DbCore<PayLoad> db)
{
	
	Conditions<PayLoad> conds0;
	conds0.children(x);
	Query<PayLoad> q1(db);
	q1.select(conds0).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}
}

/*Provides the capability to locate files and view their contents according to key*/
void b_key(std::string x,DbCore<PayLoad> db)
{
	
	PayLoad pl;
	Conditions<PayLoad> conds1;
	conds1.key(x);
	Query<PayLoad> q1(db);
	q1.select(conds1).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}

}

/*Provides the capability to locate files and view their contents according to datetime*/
void b_datetime(DateTime lb, DateTime ub,DbCore<PayLoad> db)
{
	
	Query<PayLoad> q1(db);
	Conditions<PayLoad> conds1;
	conds1.lowerBound(lb);
	conds1.upperBound(ub);
	q1.select(conds1).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}


}

/*Provides the capability to locate files and view their contents according to payload category*/
void b_payloadcat(std::string x,DbCore<PayLoad> db)
{
	
	Query<PayLoad> q1(db);

	

	auto hasCategory = [&x](DbElement<PayLoad>& elem) {
		return (elem.payLoad()).hasCategory(x);
	};

	q1.select(hasCategory).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}

}

/*Provides the capability to locate files and view their contents according to payload path*/
void b_payloadpath(std::string value,DbCore<PayLoad> db)
{
	
	Query<PayLoad> q1(db);

	auto hasValue = [&value](DbElement<PayLoad>& elem) {
		return (elem.payLoad()).value() == value;
	};
	Utilities::putline();

	
	q1.from(db.keys());
	q1.select(hasValue).show();
	Utilities::putline();

	Process p;
	p.title("Browse");
	std::string appPath = "c:/windows/system32/notepad.exe";
	p.application(appPath);

	for (auto a : q1.keys())
	{
		std::vector<std::string> x = split(a, ':');
		std::string cmdLine = "/A ../Remote_repository/" + x[0] + "/" + x[2];
		p.commandLine(cmdLine);

		std::cout << "\n  starting process: \"" << appPath << "\"";
		std::cout << "\n  with this cmdlne: \"" << cmdLine << "\"";
		p.create();
	}
}

