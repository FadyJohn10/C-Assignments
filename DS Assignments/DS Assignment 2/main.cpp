//============================================================================
// Name         : DS Assignment#2
// Author       : Mai Oudah
// Version      : 2.0
// Date Created : 07-04-2023
// Date Modified: 
// Description  : Virtual Filesystem - Main Program
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<exception>

#include "inode.h"
#include "vfs_tree.h"

using namespace std;


void pwd(VFS_Tree& myVFS_Tree);
void realpath(VFS_Tree& myVFS_Tree, string file);
void cd(VFS_Tree& myVFS_Tree, string to);
void ls(VFS_Tree& myVFS_Tree, string command);
void mkdir(VFS_Tree& myVFS_Tree, string folderName);
void touch(VFS_Tree& myVFS_Tree, string fileName, string sizeInString);
void find(VFS_Tree& myVFS_Tree, string name);
void mv(VFS_Tree& myVFS_Tree, string fileName, string folderName);
void rm(VFS_Tree& myVFS_Tree, string name);
void size(VFS_Tree& myVFS_Tree, string path);
void emptybin(VFS_Tree& myVFS_Tree);
void showbin(VFS_Tree& myVFS_Tree);
void recover(VFS_Tree& myVFS_Tree);

void exportVFS(VFS_Tree& myVFS_Tree);
void importVFS(VFS_Tree& myVFS_Tree);

//=====================================
void listCommands()
{
	cout<<" ===================================================================================="<<endl
        <<" Welcome to the Virtual Filesystem!\n"<<endl
        <<" List of available Commands:"<<endl
		<<" pwd                     : Print full path to the current working directory"<<endl
		<<" realpath <filename>     : Print the absolute/full path of a given filename of a file within the current directory"<<endl
		<<" ls                      : List files and folders inside the current folder"<<endl
		<<" mkdir <foldername>      : Make a new directory/folder"<<endl
		<<" touch  <filename> <size>            : Create a new file"<<endl     
		<<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" cd <filename>                       : Change directory"<<endl
		<<" mv <filename> <foldername>          : Move a file"<<endl
		<<" rm <filename|foldername>            : Remove a file or a folder"<<endl
		<<" size <filename|foldername>          : Print size of an file/folder"<<endl     
		<<" find <filename|foldername>          : Return the path of the file (or the folder) if it exists"<<endl
        <<" emptybin                            : Empty the trash"<<endl
		<<" showbin                 : Print the oldest file/folder of the bin"<<endl
		<<" recover                 : Recover the oldest file/folder form bin if path still exists"<<endl
		<<" help                    : Display the list of available commands"<<endl
		<<" exit                    : Exit the Program"<<endl
		<<" ====================================================================================\n"<<endl;
		
}



//=======================================
// main function
int main() {

	VFS_Tree myVFS_Tree;
	importVFS(myVFS_Tree);

    listCommands();

    string user_input;
    string command;
	string params[3];
    do {
        params[0] = "";
        params[1] = "";
        params[2] = "";
		cout<<">";
		getline(cin,user_input);

		istringstream ss(user_input);
		int i = 0;
		while (ss >> command) {
			params[i] = command;
			i++;
		}
		
		try
		{
			if(command == "help")               listCommands();
            else if(params[0]=="pwd")           pwd(myVFS_Tree);
            else if(params[0]=="realpath")      realpath(myVFS_Tree, params[1]);
            else if(params[0]=="ls")            ls(myVFS_Tree, params[1]);
            else if(params[0]=="mkdir")         mkdir(myVFS_Tree, params[1]);
            else if(params[0]=="touch")         touch(myVFS_Tree, params[1], params[2]);
            else if(params[0]=="cd")            cd(myVFS_Tree, params[1]);
            else if(params[0]=="find")          find(myVFS_Tree, params[1]);
            else if(params[0]=="mv")            mv(myVFS_Tree, params[1], params[2]);
            else if(params[0]=="rm")            rm(myVFS_Tree, params[1]);
            else if(params[0]=="size")          size(myVFS_Tree, params[1]);
            else if(params[0]=="emptybin")      emptybin(myVFS_Tree);
            else if(params[0]=="showbin")       showbin(myVFS_Tree);
            else if(params[0]=="recover")       recover(myVFS_Tree);
			else if(command == "exit")          break;
			else if(user_input=="")             continue;
			else                                cout<<"Invalid Command!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	} while(command!="exit");

	exportVFS(myVFS_Tree);
    

    return EXIT_SUCCESS;
}

// -----------------------------------------------------------------
// define the needed methods to execute the operations in the system (pwd, realpath, ls, ...) below

void pwd(VFS_Tree& myVFS_Tree)
{
	cout << myVFS_Tree.pwd(myVFS_Tree.current()) << endl;
}
void realpath(VFS_Tree& myVFS_Tree, string file)
{
	myVFS_Tree.realpath(file);
}
void cd(VFS_Tree& myVFS_Tree, string to)
{
	myVFS_Tree.cd(to);
}
void ls(VFS_Tree& myVFS_Tree, string command)
{
	if(command == "")
	{
		myVFS_Tree.ls();
	}
	else if(command == "sort")
	{
		myVFS_Tree.lsSort();
	}
	else
	{
		cout << "Command is not correct\n";
	}
}
void mkdir(VFS_Tree& myVFS_Tree, string folderName)
{
	myVFS_Tree.mkdir(folderName);
}
void touch(VFS_Tree& myVFS_Tree, string fileName, string sizeInString)
{
	myVFS_Tree.touch(fileName, stoi(sizeInString));
}
void find(VFS_Tree& myVFS_Tree, string name)
{
	myVFS_Tree.find(name);
}
void mv(VFS_Tree& myVFS_Tree, string fileName, string folderName)
{
	if(fileName[0] == '/' || folderName[0] == '/')
	{
		myVFS_Tree.mvPath(fileName, folderName);
	}else{
		myVFS_Tree.mv(fileName, folderName);
	}
}
void rm(VFS_Tree& myVFS_Tree, string name)
{
	if(name[0] == '/')
	{
		myVFS_Tree.rmPath(name);
	}else{
		myVFS_Tree.rm(name);
	}
}
void size(VFS_Tree& myVFS_Tree, string path)
{
	cout << myVFS_Tree.getSize(path) << " Bytes \n";
}
void emptybin(VFS_Tree& myVFS_Tree)
{
	myVFS_Tree.emptyBin();
}
void showbin(VFS_Tree& myVFS_Tree)
{
	myVFS_Tree.showBin();
}
void recover(VFS_Tree& myVFS_Tree)
{
	myVFS_Tree.recover();
}

void exportVFS(VFS_Tree& myVFS_Tree)
{
	myVFS_Tree.exportVFS();
}

void importVFS(VFS_Tree& myVFS_Tree)
{
	myVFS_Tree.importVFS();
}
