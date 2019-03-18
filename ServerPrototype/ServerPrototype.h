#pragma once
///////////////////////////////////////////////////////////////////////
// ServerPrototype.h - Console App that processes incoming messages  //
// ver 1.3                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018    
// Vishvesh Shah//
///////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
* ---------------------
*  Package contains one class, Server, that contains a Message-Passing Communication
*  facility. It processes each message by invoking an installed callable object
*  defined by the message's command key.
*  - This is implemented with a message dispatcher (unodered_map<Msg.Id,ServerProc>
*    where ServerProcs are defined for each type of processing required by the server.
*
*  Message handling runs on a child thread, so the Server main thread is free to do
*  any necessary background processing (none, so far).
*
*  Required Files:
* -----------------
*  ServerPrototype.h, ServerPrototype.cpp
*  Comm.h, Comm.cpp, IComm.h
*  Message.h, Message.cpp (static library)
*  Process.h, Process.cpp (static library)
*  FileSystem.h, FileSystem.cpp
*  Utilities.h
*
*  Maintenance History:
* ----------------------
*  ver 1.2 : 22 Apr 2018
*  - added NoSqlDb to server members
*  - added simple demo of db in Server startup
*  ver 1.1 : 09 Apr 2018
*  - added ServerProcs for
*    - sending files for popup display
*    - executing remote analysis
*  ver 1.0 : 03/27/2018
*  - first release
*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <thread>
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppNoSqlDb/DbCore/DbCore.h"
#include "../CppNoSqlDb/PayLoad/PayLoad.h"
#include <windows.h>
#include <tchar.h>
#include "../Checkin/Checkin.h"
#include "../Checkout/Checkout.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"

namespace Repository
{
  using File = std::string;
  using Files = std::vector<File>;
  using Dir = std::string;
  using Dirs = std::vector<Dir>;
  using SearchPath = std::string;
  using Key = std::string;
  using Msg = MsgPassingCommunication::Message;
  using ServerProc = std::function<Msg(Msg)>;
  using MsgDispatcher = std::unordered_map<Key,ServerProc>;
  
  const SearchPath storageRoot = "../Storage";  // root for all server file storage
  const MsgPassingCommunication::EndPoint serverEndPoint("localhost", 8080);  // listening endpoint

  class Server
  {
  public:
    Server(MsgPassingCommunication::EndPoint ep, const std::string& name);
    void start();
    void stop();
    void addMsgProc(Key key, ServerProc proc);
    bool hasMessageKey(const Key& key);
	void  metadata(Msg& msg);
	void checkin(Msg& msg);
	void browse(Msg& msg);
    void processMessages();
    void postMessage(MsgPassingCommunication::Message msg);
    MsgPassingCommunication::Message getMessage();
    static Dirs getDirs(const SearchPath& path = storageRoot);
    static Files getFiles(const SearchPath& path = storageRoot);
    MsgPassingCommunication::Context* getContext();
    std::string setSendFilePath(const std::string& relPath);
    std::string setSaveFilePath(const std::string& relPath);
    std::string getSendFilePath();
    std::string getSaveFilePath();
    void initializeDb();
  private:
    MsgPassingCommunication::Comm comm_;
    MsgDispatcher dispatcher_;
    std::thread msgProcThrd_;
    NoSqlDb::DbCore<NoSqlDb::PayLoad> db_;
  };
  //----< return reference to MsgPassingCommunication context >--------

  inline MsgPassingCommunication::Context* Server::getContext()
  {
    return comm_.getContext();
  }
  //----< initialize server endpoint and give server a name >----------

  inline Server::Server(MsgPassingCommunication::EndPoint ep, const std::string& name)
    : comm_(ep, name) {
    initializeDb();
  }

  inline std::string Server::setSendFilePath(const std::string& relPath)
  {
    comm_.setSendFilePath(relPath);
  }
  inline std::string Server::setSaveFilePath(const std::string& relPath)
  {
    comm_.setSaveFilePath(relPath);
  }
  inline std::string Server::getSendFilePath()
  {
    comm_.getSendFilePath();
  }
  inline std::string Server::getSaveFilePath()
  {
    comm_.getSaveFilePath();
  }
  //----< start server's instance of Comm >----------------------------

  inline void Server::start()
  {
    comm_.start();
  }
  //----< stop Comm instance >-----------------------------------------

  inline void Server::stop()
  {
    if(msgProcThrd_.joinable())
      msgProcThrd_.join();
    comm_.stop();
  }
  //----< pass message to Comm for sending >---------------------------

  inline void Server::postMessage(MsgPassingCommunication::Message msg)
  {
    comm_.postMessage(msg);
  }
  //----< get message from Comm >--------------------------------------

  inline MsgPassingCommunication::Message Server::getMessage()
  {
    Msg msg = comm_.getMessage();
    return msg;
  }
  //----< add ServerProc callable object to server's dispatcher >------

  inline void Server::addMsgProc(Key key, ServerProc proc)
  {
    dispatcher_[key] = proc;
  }
  //Perform browse
  void Server::browse(Msg& msg)
  {
	  std::cout << " \n Fulfilling the requirement of browse \n\n";
	  std::string n;
	  Query<PayLoad> q1(db_);
	  Conditions<PayLoad> c;
	  c.name(msg.value("txtMsgName"));
	  c.description(msg.value("txtMsgDescription"));
	  c.children(Utilities::split(msg.value("txtMsgPayloadvalue"), ';'));
	  std::vector<std::string> k = Utilities::split(msg.value("txtMsgCategory"), ';');
	  for (auto e : k)
	  {
		  auto hasCategory = [&e](DbElement<PayLoad>& elem) {
			  return (elem.payLoad()).hasCategory(e);
		  };

		  q1.select(hasCategory);
	  }
	  q1.select(c);
	  for (auto a : q1.keys())
	  {
		  n = a + ",";
	  }
	  msg.attribute("fil", n);
  }

  //Perform Checkin 
  void Server::checkin(Msg& msg)
  {
	  std::cout << "\n Fulfilling the requirement of checkin \n\n";
	  std::string a = msg.value("fileName");
	  std::string file = checkIn(a, db_);
	  std::string source = FileSystem::Path::getFullFileSpec("../Storage/" + msg.value("fileName"));
	  std::string dest = FileSystem::Path::getFullFileSpec("../Storage/" + file);
	  FileSystem::File::copy(source, dest, false);
	  FileSystem::File::remove(source);
  }
  //Perform metadata
  void  Server::metadata(Msg& msg)
  {
	  std::cout << "\n Fulfilling the requirement of viewing metadata \n\n";
	  std::string child, categ;
	  std::string file = msg.value("fileName");
	  msg.attribute("name", db_[file].name());
	  msg.attribute("description", db_[file].descrip());
	  for (auto a : db_[file].children())
	  {
		  child += a + ";";
	  }
	  msg.attribute("children", child);
	  for (auto b : db_[file].payLoad().categories())
	  {
		  categ += b + ";";
	  }
	  msg.attribute("categories", categ);
  }

  //----< does server have specified key? >----------------------------

  inline bool Server::hasMessageKey(const Key& key)
  {for (auto item : dispatcher_)
    { if (item.first == key)
        return true;}
    return false;}
  //----< start processing messages on child thread >------------------
  inline void Server::processMessages()
  { auto proc = [&]()
    {  if (dispatcher_.size() == 0)
      { std::cout << "\n  no server procs to call";
        return;}
      while (true)
      {Msg msg = getMessage();
        std::cout << "\n  received message: " << msg.command() << " from " << msg.from().toString();
        if (msg.containsKey("verbose"))
        { std::cout << "\n";
          msg.show();}
		if (msg.command() == "serverQuit")
			break;
		else if (msg.command() == "Per_Checkin")
		{
			checkin(msg);
		}
		else if (msg.command() == "Per_Browse")
		{
			browse(msg);
		}
		else if (msg.command() == "Per_Metadata")
		{
			metadata(msg);
		}
        Msg reply;
        reply.to(msg.from());
        reply.from(msg.to());
        if (hasMessageKey(msg.command()))
        {
          reply = dispatcher_[msg.command()](msg);
        }
        else
        {reply.command("error - unknown command");}
        if (msg.to().port != msg.from().port)  // avoid infinite message loop
        {  postMessage(reply);
          msg.show();
          reply.show();}
        else
          std::cout << "\n  server attempting to post to self";}
      std::cout << "\n  server message processing thread is shutting down";};
    std::thread t(proc);
    //SetThreadPriority(t.native_handle(), THREAD_PRIORITY_HIGHEST);
    std::cout << "\n  starting server thread to process messages";
    msgProcThrd_ = std::move(t);
  }
  inline void Server::initializeDb()
  {
    NoSqlDb::DbElement<NoSqlDb::PayLoad> elem;
    elem.name("SuperNode_Proj4");
    elem.descrip("Intended to hold references to Project #4 files.  Left as an exercise.");
    NoSqlDb::PayLoad pl;
    pl.value("demonstration");
    elem.payLoad(pl);
    db_[elem.name()] = elem;
    NoSqlDb::showDb(db_);
    std::cout << "\n";
  }
}