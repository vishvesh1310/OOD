#pragma once
/////////////////////////////////////////////////////////////////////
// MyRepo.h - Implements repository functionalities                 //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/* Package Operations :
*------------------ -
This package contains functions for displaying the various functionalities like checkin,checkout,browse,
adding some files to the database before we perform any of the functions,


* Required Files :
*-------------- -
*Executive.h,Payload.h,Checkin.h,Checkout.h,Browse.h
*/
/* Maintenance History :
*ver 1.0 : 6th Mar 2018
* -first release
*/
#include "stdafx.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include "../Checkin/Checkin.h"
#include "../Checkout/Checkout.h"
#include "../Browse/Browse.h"
using namespace NoSqlDb;

class DbProvider
{
public:
	DbCore<PayLoad>& db() { return db_; }
private:
	static DbCore<PayLoad> db_;
};

DbCore<PayLoad> DbProvider::db_;
/*This is the base database of files in remote repository*/
void main_db()
{
	Utilities::title("MainDb");
	Utilities::putline();
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();

	DbElement<PayLoad> elem = makeElement<PayLoad>("A", "For me_1");
	PayLoad pl, pl1, pl2, pl3, pl4;
	pl.value("../Remote_repository/DbCore");
	pl.categories().push_back("Header");
	pl.flag("open");
	elem.payLoad(pl);
	db["DbCore::DbCore.h.1"] = elem;

	elem.name() = "C";
	elem.descrip() = "For me_3";
	pl2.value("../Remote_repository/DbCore");
	pl2.categories().push_back("CPP");
	pl2.flag("open");
	elem.payLoad(pl2);
	db["DbCore::DbCore.cpp.1"] = elem;

	db["DbCore::DbCore.h.1"].children().push_back("DbCore::DbCore.cpp.1");

	elem.name() = "D";
	elem.descrip() = "For me_4";
	pl2.value("../Remote_repository/Checkout");
	pl2.categories().push_back("CPP");
	pl2.flag("close");
	elem.payLoad(pl2);
	db["Checkout::Checkout.h.1"] = elem;

	db["DbCore::DbCore.h.1"].children().push_back("Checkout::Checkout.h.1");
	dbp.db() = db;
	showDb(db);
	Utilities::putline();
	elem.payLoad().showDb(db);
	Utilities::putline();
}
/*This is for checkin a file that is not present in remote repo*/
void cin_ntexist()
{
	Utilities::title("Checking Not Existing File");
	Utilities::putline();
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	db=checkIn("Query::Query.h",db);
	db = dbp.db();
	db["Query::Query.h.1"].children().push_back("DbCore::DbCore.h.1");
	dbp.db() = db;
}
/*This is to checkin a file in which the checkin status is open*/
void cin_existopen()
{
	Utilities::title("Checking Existing File that has a status open");
	Utilities::putline();
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	db = checkIn("DbCore::DbCore.cpp",db);
}
/*This is to checkin a file which has a status of close or close pending*/
void cin_existclose()
{
	Utilities::title("Checking Existing File that has a status close");
	Utilities::putline();
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	close_file("DbCore::DbCore.cpp", db);
	close_file("DbCore::DbCore.h" ,db);
	db = checkIn("DbCore::DbCore.h",db );
}
/*provides the capability to locate files and view their contents.*/
void browser_files()
{
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();

	std::cout << "\nbrowse files with name including A\n";
	b_name("A",db);
	std::cout << "\nbrowse files description including me\n";
	b_description("me", db);
	std::cout << "\nbrowse files with key containing DbCore.h\n";
	b_key("DbCore::DbCore.h" ,db);
	std::cout << "\nbrowse files with children DbCore.cpp.1\n";
	b_children({ "DbCore::DbCore.cpp.1" },db );
	std::cout << "\nbrowse files with category CPP\n";
	b_payloadcat("CPP",db);
	std::cout << "\nbrowse files with path ../Remote_repository/\n";
	b_payloadpath("../Remote_repository/DbCore",db);
	std::cout << "\nbrowse files with datetime between Sun Mar 11 2:00:00 2018 and Tue Mar 27 9:00:00 2018\n";
	b_datetime(DateTime("Sun Mar 11 2:00:00 2018"), DateTime("Tue Mar 27 9:00:00 2018"),db);
}

/*Checkout a file from remote to local*/
void cout_file()
{
	DbProvider dbp;
	DbCore<PayLoad> db = dbp.db();
	checkOut("DbCore::DbCore.h.1", db);
}