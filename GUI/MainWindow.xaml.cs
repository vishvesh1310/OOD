///////////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs - GUI for Project3HelpWPF                      //
// ver 2.1                                                         //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018
//Vishvesh Shah
///////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package provides a WPF-based GUI for Project3HelpWPF demo.  It's 
 * responsibilities are to:
 * - Provide a display of directory contents of a remote ServerPrototype.
 * - It provides a subdirectory list and a filelist for the selected directory.
 * - You can navigate into subdirectories by double-clicking on subdirectory
 *   or the parent directory, indicated by the name "..".
 *   
 * Required Files:
 * ---------------
 * Mainwindow.xaml, MainWindow.xaml.cs
 * Translater.dll
 * 
 * Maintenance History:
 * --------------------
 * ver 2.0 : 22 Apr 2018
 * - added tabbed display
 * - moved remote file view to RemoteNavControl
 * - migrated some methods from MainWindow to RemoteNavControl
 * - added local file view
 * - added NoSqlDb with very small demo as server starts up
 * ver 1.0 : 30 Mar 2018
 * - first release
 * - Several early prototypes were discussed in class. Those are all superceded
 *   by this package.
 */

// Translater has to be statically linked with CommLibWrapper
// - loader can't find Translater.dll dependent CommLibWrapper.dll
// - that can be fixed with a load failure event handler
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using System.IO;
using MsgPassingCommunication;

namespace WpfApp1
{
  public partial class MainWindow : Window
  {
    public MainWindow()
    {
      InitializeComponent();
      Console.Title = "Project4Demo GUI Console";
    }

    private Stack<string> pathStack_ = new Stack<string>();
    internal Translater translater;
    internal CsEndPoint endPoint_;
    private Thread rcvThrd = null;
    private Dictionary<string, Action<CsMessage>> dispatcher_ 
      = new Dictionary<string, Action<CsMessage>>();
    internal string saveFilesPath;
    internal string sendFilesPath;

    //----< process incoming messages on child thread >----------------

    private void processMessages()
    {
      ThreadStart thrdProc = () => {
        while (true)
        {
          CsMessage msg = translater.getMessage();
          try
          {
            string msgId = msg.value("command");
            Console.Write("\n  client getting message \"{0}\"", msgId);
            if (dispatcher_.ContainsKey(msgId))
              dispatcher_[msgId].Invoke(msg);
          }
          catch(Exception ex)
          {
            Console.Write("\n  {0}", ex.Message);
            msg.show();
          }
        }
      };
      rcvThrd = new Thread(thrdProc);
      rcvThrd.IsBackground = true;
      rcvThrd.Start();
    }
    //----< add client processing for message with key >---------------

    private void addClientProc(string key, Action<CsMessage> clientProc)
    {
      dispatcher_[key] = clientProc;
    }
    ////----< load getDirs processing into dispatcher dictionary >-------

    private void DispatcherLoadGetDirs()
    {
      Action<CsMessage> getDirs = (CsMessage rcvMsg) =>
      {
        Action clrDirs = () =>
        {
          //NavLocal.clearDirs();
          NavRemote.clearDirs();
        };
        Dispatcher.Invoke(clrDirs, new Object[] { });
        var enumer = rcvMsg.attributes.GetEnumerator();
        while (enumer.MoveNext())
        {
          string key = enumer.Current.Key;
          if (key.Contains("dir"))
          {
            Action<string> doDir = (string dir) =>
            {
              NavRemote.addDir(dir);
            };
            Dispatcher.Invoke(doDir, new Object[] { enumer.Current.Value });
          }
        }
        Action insertUp = () =>
        {
          NavRemote.insertParent();
        };
        Dispatcher.Invoke(insertUp, new Object[] { });
      };
      addClientProc("getDirs", getDirs);
    }
    //----< load getFiles processing into dispatcher dictionary >------

    private void DispatcherLoadGetFiles()
    {
      Action<CsMessage> getFiles = (CsMessage rcvMsg) =>
      {
        Action clrFiles = () =>
        {
          NavRemote.clearFiles();
        };
        Dispatcher.Invoke(clrFiles, new Object[] { });
        var enumer = rcvMsg.attributes.GetEnumerator();
        while (enumer.MoveNext())
        {
          string key = enumer.Current.Key;
          if (key.Contains("file"))
          {
            Action<string> doFile = (string file) =>
            {
              NavRemote.addFile(file);
            };
            Dispatcher.Invoke(doFile, new Object[] { enumer.Current.Value });
          }
        }
      };
      addClientProc("getFiles", getFiles);
    }
    //----< load getFiles processing into dispatcher dictionary >------

    private void DispatcherLoadSendFile()
    {
      Action<CsMessage> sendFile = (CsMessage rcvMsg) =>
      {
        Console.Write("\n  processing incoming file");
        string fileName = "";
        var enumer = rcvMsg.attributes.GetEnumerator();
        while (enumer.MoveNext())
        {
          string key = enumer.Current.Key;
          if (key.Contains("sendingFile"))
          {
            fileName = enumer.Current.Value;
            break;
          }
        }
        if (fileName.Length > 0)
        {
          Action<string> act = (string fileNm) => { showFile(fileNm); };
          Dispatcher.Invoke(act, new object[] { fileName });
        }
      };
      addClientProc("sendFile", sendFile);
    }

        //----< load connection processing into dispatcher dictionary >------
        private void DispatcherLoadRes_Conection()
        {
            Action<CsMessage> Res_Connection = (CsMessage rcvMsg) =>
            {
                Action clrFiles = () =>
                {
                    lstBoxConnect.Items.Insert(0, "Connection has been established between server and the client");
                };
                Dispatcher.Invoke(clrFiles, new Object[] { });
            };
            addClientProc("Res_Connection", Res_Connection);
        }


        //----< load metadata processing into dispatcher dictionary >------
        private void DispatcherLoadRes_Metadata()
        {
            Action<CsMessage> Res_Metadata = (CsMessage rcvMsg) =>
            {
                Action clrFiles = () =>
                {
                    NavRemote.txtMsgName.Content = rcvMsg.value("name");
                    NavRemote.txtMsgDescription.Content = rcvMsg.value("description");
                    NavRemote.txtMsgCategory.Content = rcvMsg.value("categories");
                    NavRemote.txtMsgPayloadvalue.Content = rcvMsg.value("children");
                };
                Dispatcher.Invoke(clrFiles, new Object[] { });
            };
            addClientProc("Res_Metadata", Res_Metadata);
        }

        //----< load query processing into dispatcher dictionary >------
        private void DispatcherLoadRes_Browse()
        {
            Action<CsMessage> Res_Browse = (CsMessage rcvMsg) =>
            {
                Action<string> Per_Browse  = (string fil) =>
                {
                    lstBoxFiles.Items.Insert(0, fil);
                };
                Dispatcher.Invoke(Per_Browse, new Object[] {rcvMsg.value("fil") });
            };
            addClientProc("Res_Browse", Res_Browse);
        }


        //----< load all dispatcher processing >---------------------------

        private void loadDispatcher()
    {
      DispatcherLoadGetDirs();
      DispatcherLoadGetFiles();
      DispatcherLoadSendFile();
            DispatcherLoadRes_Conection();
            DispatcherLoadRes_Browse();
            DispatcherLoadRes_Metadata();
    }
    //----< start Comm, fill window display with dirs and files >------

    private void Window_Loaded(object sender, RoutedEventArgs e)
    {
      // start Comm
      endPoint_ = new CsEndPoint();
      endPoint_.machineAddress = "localhost";
      endPoint_.port = 8082;
      NavRemote.navEndPoint_ = endPoint_;

      translater = new Translater();
      translater.listen(endPoint_);

      // start processing messages
      processMessages();

      // load dispatcher
      loadDispatcher();

      CsEndPoint serverEndPoint = new CsEndPoint();
      serverEndPoint.machineAddress = "localhost";
      serverEndPoint.port = 8080;
      pathStack_.Push("../Storage");

      NavRemote.PathTextBlock.Text = "Storage";
      NavRemote.pathStack_.Push("../Storage");

      NavLocal.PathTextBlock.Text = "LocalStorage";
      NavLocal.pathStack_.Push("");
      NavLocal.localStorageRoot_ = "../../../../LocalStorage";
      saveFilesPath = translater.setSaveFilePath("../../../../Local");
      sendFilesPath = translater.setSendFilePath("../../../../LocalStorage");

      NavLocal.refreshDisplay();
      NavRemote.refreshDisplay();
      test1();
    }
    //----< strip off name of first part of path >---------------------

    public string removeFirstDir(string path)
    {
      string modifiedPath = path;
      int pos = path.IndexOf("/");
      modifiedPath = path.Substring(pos + 1, path.Length - pos - 1);
      return modifiedPath;
    }
    //----< show file text >-------------------------------------------

    private void showFile(string fileName)
    {
      Paragraph paragraph = new Paragraph();
      string fileSpec = saveFilesPath + "\\" + fileName;
      string fileText = File.ReadAllText(fileSpec);
      paragraph.Inlines.Add(new Run(fileText));
      CodePopupWindow popUp = new CodePopupWindow();
      popUp.codeView.Blocks.Clear();
      popUp.codeView.Blocks.Add(paragraph);
      popUp.Show();
    }

        //---respond to click event on connect button----//
        void conbtn(object sen, RoutedEventArgs e)
        {
            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = "localhost";
            serverEndPoint.port = 8080;


            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(endPoint_));
            msg.add("command", "Per_Connection");
            translater.postMessage(msg);
        }

        //---respond to click event on browse(Search) button----//
        void brsbutton(object sen, RoutedEventArgs e)
        {

            MainWindow win = (MainWindow)Window.GetWindow(this);

            CsEndPoint serverEndPoint = new CsEndPoint();
            serverEndPoint.machineAddress = "localhost";
            serverEndPoint.port = 8080;

            CsMessage msg = new CsMessage();
            msg.add("to", CsEndPoint.toString(serverEndPoint));
            msg.add("from", CsEndPoint.toString(win.endPoint_));
            msg.add("path", pathStack_.Peek());
            msg.add("command", "Per_Browse");
            msg.add("Name", txtMsgName.Text);
            msg.add("Description", txtMsgDescription.Text);
            msg.add("Category", txtMsgCategory.Text);
            msg.add("Children", txtMsgPayloadvalue.Text);
            win.translater.postMessage(msg);
        }
        //----< first test not completed >---------------------------------

        void test1()
        {
            //NavLocal.DirList_MouseDoubleClick(new object(), new MouseButtonEventArgs(Mouse.PrimaryDevice, 0, MouseButton.Left));
            conbtn(new object(), new RoutedEventArgs());
            NavLocal.FileList.SelectedIndex = 1;
            NavLocal.Cinbutton(new object(), new RoutedEventArgs());

            NavLocal.FileList.SelectedIndex = 2;
            NavLocal.Cinbutton(new object(), new RoutedEventArgs());

            NavRemote.refreshDisplay();
            NavRemote.coutbutton(new object(), new RoutedEventArgs());

            NavRemote.Metadata(new object(), new RoutedEventArgs());
            
            brsbutton(new object(), new RoutedEventArgs());


        }
    }
}
