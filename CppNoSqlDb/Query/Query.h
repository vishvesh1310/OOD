#pragma once
///////////////////////////////////////////////////////////////////////
// Query.h - Returns information from db metadata and payload        //
// ver 1.0                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018         //
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package provides classes:
*  - Conditions holds the conditions that define the data returned from a query
*  - Query provides methods: select, from, keys, and show
*
*  Required Files:
*  ---------------
*    Query.h, Query.cpp
*    PayLoad.h, PayLoad.cpp - application defined package
*    DbCore.h, DbCore.cpp
*
*  Maintenance History:
*  --------------------
*  Ver 1.0 : 10 Feb 2018
*  - first release
*
*/
#include "../DbCore/Definitions.h"
#include "../DbCore/DbCore.h"
#include <vector>
#include <string>
#include <regex>

namespace NoSqlDb
{
	//using Key = std::string;
	//using Keys = std::vector<Key>;

	/////////////////////////////////////////////////////////////////////
	// Conditions class
	// - defines data returned by query

	template <typename P>
	class Conditions
	{
	public:
		using RegExp = const std::string&;

		Conditions() = default;
		void value(DbElement<P>& elem) { pDbElem_ = &elem; } // set pointer to element used during query
		void value1(std::string key) { key_ = key; }
		bool match();
		void name(RegExp regExp) { nameRegExp_ = regExp; }
		bool matchName();
		void key(RegExp regExp) { keyRegExp_ = regExp; }
		bool matchKey();
		void description(RegExp regExp) { descriptionRegExp_ = regExp; }
		bool matchDescription();
		void lowerBound(const DateTime& lower) { lowerBound_ = lower; }
		void upperBound(const DateTime& upper = DateTime.now()) { upperBound_ = upper; }
		bool matchDateTimeInterval();
		void children(Keys keys) { keys_ = keys; }
		bool matchChildren();

		///////////////////////////////////////////////////////////////
		// Not currently using the two functions, below.
		// Included, as I may decide to use them later.
		// template<typename CallObj>
		// void payLoadCallableObject(CallObj callObj) { callObj_ = callObj; }
		// template <typename CallObj>
		// bool matchPayLoad() 
		// { 
		//   return callObj_(pDbElem_->payLoad()); 
		// }
		///////////////////////////////////////////////////////////////
	private:
		// DbElement<P> is referenced through pointer, not C++ reference type,
		// so the element can be changed at any time.
		DbElement<P>* pDbElem_ = nullptr;
		std::string nameRegExp_ = "";
		std::string keyRegExp_ = "";
		std::string key_ = "";
		std::string descriptionRegExp_ = "";
		DateTime lowerBound_ = DateTime().now();
		DateTime upperBound_ = DateTime().now();
		Keys keys_;
		///////////////////////////////////////////////////////////////
		// Not currently used, but may later.
		// template<typename CallObj>
		// static CallObj callObj_;
	};
	/*----< test element metadata for specified conditions >-----------*/

	template<typename P>
	bool Conditions<P>::match()
	{
		try
		{
			return matchName() && matchDescription() && matchChildren() && matchDateTimeInterval() && matchKey();
		}
		catch (std::exception& ex)
		{
			std::cout << "\n  exception thrown:\n  " << ex.what();
		}
		return false;
	}
	/*----< test element metadata for name match >---------------------*/

	template<typename P>
	bool Conditions<P>::matchName()
	{

		if (nameRegExp_ == "")
			return true;
		std::regex re(nameRegExp_);
		return std::regex_search(pDbElem_->name(), re);
	}

	/*----< test element metadata for key match >---------------------*/

	template<typename P>
	bool Conditions<P>::matchKey()
	{
		if (keyRegExp_ == "")
			return true;
		std::regex re(keyRegExp_);
		return std::regex_search(key_, re);
	}
	/*----< test metadata for description match >----------------------*/

	template<typename P>
	bool Conditions<P>::matchDescription()
	{
		if (descriptionRegExp_ == "")
			return true;
		std::regex re(descriptionRegExp_);
		std::string desc = pDbElem_->descrip();
		return std::regex_search(desc, re);
	}
	/*----< test metadata for time interval match >--------------------*/

	template<typename P>
	bool Conditions<P>::matchDateTimeInterval()
	{
		if (lowerBound_ == upperBound_)
			return true;
		DateTime elemDateTime = pDbElem_->dateTime();
		bool aboveLower = lowerBound_ < elemDateTime;
		bool belowUpper = upperBound_ > elemDateTime;
		return aboveLower && belowUpper;
	}
	/*----< test metadata for children matches >-----------------------*/

	template<typename P>
	bool Conditions<P>::matchChildren()
	{
		if (keys_.size() == 0)
			return true;
		Keys::iterator start = pDbElem_->children().begin();
		Keys::iterator end = pDbElem_->children().end();
		for (Key key : keys_)
		{
			if (std::find(start, end, key) == end)
				return false;
		}
		return true;
	}

	/////////////////////////////////////////////////////////////////////
	// Query class

	template<typename P>
	class Query
	{
	public:
		Query(DbCore<P>& db) : db_(db) { keys_ = db_.keys(); }

		static void identify(std::ostream& out = std::cout);

		Query& select(Conditions<P>& conds);
		template<typename CallObj>
		Query& select(CallObj callObj);

		Query& query_or(Query<P>& q);

		Query& from(const Keys& keys) { keys_ = keys; return *this; }

		void show(std::ostream& out = std::cout);

		Keys& keys() { return keys_; }

	private:
		DbCore<P>& db_;
		Keys keys_;
	};
	//----< show file name >---------------------------------------------

	template<typename P>
	void Query<P>::identify(std::ostream& out)
	{
		out << "\n  \"" << __FILE__ << "\"";
	}
	/*----< returns keys for elements that match conds >---------------*/

	template<typename P>
	Query<P>& Query<P>::select(Conditions<P>& conds)
	{
		Keys newKeys;
		for (auto item : db_)
		{
			conds.value(item.second);
			conds.value1(item.first);
			if (conds.match())
				newKeys.push_back(item.first);
		}
		keys_ = newKeys;
		return *this;
	}
	/*----< supports application defined queries for payload >---------*/
	/*
	*  - CallObj is defined by the application to return results from
	*    application's payload.  See test stub for example uses.
	*/
	template<typename P>
	template<typename CallObj>
	Query<P>& Query<P>::select(CallObj callObj)
	{
		Keys newKeys;
		for (auto item : db_)
		{
			if (callObj(item.second))
				newKeys.push_back(item.first);
		}
		keys_ = newKeys;
		return *this;
	}
	/*----< form union of keys with q.keys() >-------------------------*/

	template<typename P>
	Query<P>& Query<P>::query_or(Query<P>& q)
	{
		Keys keys = q.keys();
		for (auto key : keys)
		{
			Keys::iterator start = keys_.begin();
			Keys::iterator end = keys_.end();
			if (std::find(start, end, key) == end)
				keys_.push_back(key);
		}
		return *this;
	}
	/*----< displays query results >-----------------------------------*/
	/*
	*  - displays an element for each key in query keys
	*/
	template<typename P>
	void Query<P>::show(std::ostream& out)
	{
		showHeader(showKey, out);
		for (auto key : keys_)
		{
			DbElement<P> temp = db_[key];
			showRecord<P>(key, temp, out);
		}
	}
}