#pragma once
/////////////////////////////////////////////////////////////////////
// Checkin.h - Implements checkin functionalities of the files                  //
// ver 1.0                                                         //
// Vishvesh Shah, CSE687 - Object Oriented Design, Spring 2018       //
/////////////////////////////////////////////////////////////////////
/* Package Operations :
*------------------ -
This package contains checkin function for checkin of files,
notExist func for checking the files that does not exist,
open func for checking the files that does exist and status is open,
close_exist for checking the files that does exist and status is closed or close pending,
close_file for changing the status to close.

* Required Files :
*-------------- -
*Executive.h,Payload.h,Filesystem.h,Version.h
*/
/* Maintenance History :
*ver 1.0 : 6th Mar 2018
* -first release
*/

#include "stdafx.h"
#include "../CppNoSqlDb/Executive/NoSqlDb.h"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include "../CppNoSqlDb/DbCore/DbCore.h"

//#include "../FileSystemDemo/FileSystem.h"
#include "string"
#include "string.h"
#include "../Version/Version.h"


using namespace NoSqlDb;





/*Checkin a file that does not exist in remote repo*/
std::string NotExist(std::string x,DbCore<PayLoad>& db)
{
	
	size_t lastindex = x.find_last_of(".");
	std::string name1 = x.substr(lastindex,sizeof(x));
	std::string cat;
	
	if (name1 == ".h")
	{
		cat = "Header";
	}

	else
	{ cat = "Cpp"; }
	
	
		
		
		DbElement<PayLoad> elem = makeElement<PayLoad>("Vishvesh", "For me");
		elem.children().push_back("Children");
		PayLoad pl;
		pl.value("../Remote_repository/" +x);
		pl.categories().push_back(cat);
		pl.flag("close");
		elem.payLoad(pl);
		db[x+".1"] = elem;
		
		showDb(db);
		

		pl.showDb(db);
		
		return (x + ".1");

	
}

/*Close the checkin status of the file*/
void close_file(std::string a, DbCore<PayLoad>& db)
{
	
	PayLoad pl;
	Conditions<PayLoad> conds1;
	conds1.key(a);
	Query<PayLoad> q1(db);
	q1.select(conds1);
	Keys k = q1.keys();
	if (k.empty())
	{
		std::cout << '\n' << "Sorry the file is not present" << '\n';
	}
	else
	{
		int max = 0, b = 0;
		for (auto k1 : k)
		{
			std::string name = k1;
			max = maximum(name, max, b);
		}
		std::string nf = a + "." + std::to_string(max);
		if (db[nf].children().empty())
		{
			db[nf].payLoad().flag("close");
		}
		else
		{
			bool m = true;
			for (auto c : db[nf].children())
			{
				if (db[c].payLoad().flag() == "open") { m = false; }
			}
			if (m)
			{
				db[nf].payLoad().flag("close");
			}
			else
			{
				db[nf].payLoad().flag("close pending");
			}
		}
	}
	
	showDb(db);
	
	pl.showDb(db);
	
	
}

/*Checkin a file that does exist in remote repo but checkin status is open*/
std::string open(std::string x,int max,DbCore<PayLoad>& db)
{
	
	
	PayLoad pl;
	showDb(db);
	
    pl.showDb(db);
	
	return (x + "." + std::to_string(max));
}

/*Checkin a file that does exist in remote repo but checkin status is close or close pending*/
std::string close(std::string x, int max,DbCore<PayLoad>& db)
{
	
	size_t lastindex = x.find_last_of(".");
	
	std::string cat;
	

	
	
		
		DbElement<PayLoad> elem = db[x + "." + std::to_string(max)];
		
		PayLoad pl;
		elem.payLoad().flag("close");
		db[x + "." + std::to_string(max + 1)] = elem;
		Conditions<PayLoad> conds1;
		conds1.children({ x + "." + std::to_string(max) });
		Query<PayLoad> q1(db);
		q1.select(conds1);
		for (auto l : q1.keys())
		{
			db[l].children().push_back(x + "." + std::to_string(max+1));
		}
		std::string ret = (x + "." + std::to_string(max + 1));
		showDb(db);
		
		pl.showDb(db);
		
		return ret;
}

/*Checkin a file*/
std::string checkIn(std::string x,DbCore<PayLoad>& db)
{
	
	Conditions<PayLoad> conds1;
	conds1.key(x);
	Query<PayLoad> q1(db);
    q1.select(conds1);
	Keys a = q1.keys();
	std::string ret;
	
	if (a.empty())
	{
		ret = NotExist(x,db);
	}
	else
	{
		int max = 0, b = 0;
		for (auto k : a)
		{
			std::string name = k;
			max = maximum(name, max, b);
        }
		if (db[x + "." + std::to_string(max)].payLoad().flag() == "open")
		{
			ret = open(x,max,db);
		}
		else
		{
			ret = close(x, max,db);
		}

		
	}
	return ret;
}
