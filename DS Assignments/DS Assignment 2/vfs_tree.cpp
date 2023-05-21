#include "vfs_tree.h"
#include<sstream>
#include <fstream>
#include <string>

//fucntion to get the time and change it to the required format
time_t t = time(nullptr);
string formatDate(time_t t) {
  char buffer[80];
  strftime(buffer, 80, "%d-%m-%y", localtime(&t));
  return string(buffer);
}

//************* Position Methods *************//

Position::Position(Inode* inode) : inode(inode) {}

Position::Position() {}

Position::~Position() { }

Position Position:: parent() const { return Position(inode->parent); }

bool Position::isRoot() const { return inode->parent == nullptr; }

bool Position::isExternal() const{ return inode->children.isEmpty(); }

MyVector<Position*> Position::childrenPositions() const {
    MyVector<Position*> childrenVec;
    MyVector<Inode*> children = inode->children; //capturing the children of the position's node
    for (int i = 0; i < children.getSize(); i++) {
        childrenVec.pushBack(new Position(children[i])); //filling the children position with positions
    }
    return childrenVec;
}


//************* VFS_Tree Methods *************//


VFS_Tree::VFS_Tree()
{
	Inode* rootNode = new Inode("/", 0, false, formatDate(t));
	_root = new Position(rootNode);
	currentNode = _root; //set the current to the root at the beginning
    prevPos = currentNode;
	n = 1;
}

VFS_Tree::~VFS_Tree()
{}

bool VFS_Tree::empty() const { return n == 1; } //the tree is empty if it only has the root

Position* VFS_Tree::root() const { return _root; }

Position* VFS_Tree::current() const { return currentNode; }

Position* VFS_Tree::find(string name) const {
    bool isFound = false;
    MyStack<Position*> stack;
    Position* lastfound;
    // Start the search from the root inode
    stack.push(_root);

    // pushing the children and their descendants into the stack and getting them back
    while (!stack.empty()) {
        Position* curr = stack.top();
        stack.pop();

        // check if the current inode matches the given name
        if (curr->getNode()->fname == name) {
            realpath(name);
            isFound = true;
            lastfound = curr;
        }

        //add children of the current inode to the stack for further search
        MyVector<Position*> childrenPos = curr->childrenPositions();
        for (int i = 0; i < childrenPos.getSize(); i++) {
            Position* child = childrenPos[i];
            stack.push(child);
        }
    }
    if(isFound){
        return lastfound;
    }else{
        cout << "No file/folder with this name \n";
        return NULL;
    }
}


void VFS_Tree::touch(string filename, int size)
{
    bool isFound = false;
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    //loop through the nodes of the current directory
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* child = childrenPos[i];
        Inode* childNode = child->getNode();
        // check if there is a file with the same name
        if (childNode->getName() == filename && !childNode->isFolder()){ 
            cout << "There is a file with the same name\n";
            isFound = true;
        }
    }
    if(!isFound) // if there is no file with the same name, create it
    {
        Inode* newFile = new Inode(filename, size, true, formatDate(t));
        newFile->parent = currentNode->getNode();
        currentNode->getNode()->children.pushBack(newFile);
        n++;
    }

    
}

void VFS_Tree::mkdir(string foldername)
{
    bool isFound = false;
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    //loop through the nodes of the current directory
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* child = childrenPos[i];
        Inode* childNode = child->getNode();
        // check if there is a folder with the same name
        if (childNode->getName() == foldername && childNode->isFolder()){
            cout << "There is a folder with the same name\n";
            isFound = true;
        }
    }
    if(!isFound) // if there is no folder with the same name, create it
    {
        Inode* newFolder = new Inode(foldername, 10, false, formatDate(t));
        newFolder->parent = currentNode->getNode();
        currentNode->getNode()->children.pushBack(newFolder);
        n++;
    }
}

void VFS_Tree::ls()
{
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    if(childrenPos.getSize() > 0)
    {
        for (int i = 0; i < childrenPos.getSize(); i++) {
            Position* child = childrenPos[i];
            Inode* childNode = child->getNode();
            string type = (childNode->isFolder()) ? "dir" : "file"; //getting the type of the node
            // printing the node attributes
            cout << type << " "<<  childNode->fname << " " << childNode->size << " " << childNode->date << endl;
        }
    }
    else{cout << "This directory is empty \n";}
}

void VFS_Tree:: lsSort()
{
    MyVector<Inode*> children = currentNode->inode->children;
    for (int i = 0; i < children.getSize()-1; i++)
    {
        for (int j = 0; i < children.getSize() - i - i; i++)
        {
            // swapping the nodes descendingly
            if(children[j]->size < children[j+1]->size)
            {
                Inode* temp = children[j];
                children[j] = children[j+1];
                children[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < children.getSize(); i++)
    {
        string type = (children[i]->isFolder()) ? "dir" : "file";
        cout << type << " "<<  children[i]->fname << " " << children[i]->size << " " << children[i]->date << endl;
    }

}

void VFS_Tree::cd(string arg)
{
    if(arg == "..") // go to the parent dir if current is not the root
    {
        if(currentNode != _root)
        {
            prevPos = currentNode;
            currentNode = new Position(currentNode->inode->parent);
        }
    }
    else if(arg == "-") // go to the last visited dir
    {
        Position* tempPos = currentNode;
        currentNode = prevPos;
        prevPos = tempPos;
    }
    else if(arg[0] == '/' && arg.size() > 1) //check if the argument is a full path
    {
        prevPos = currentNode;
        currentNode = _root;
        stringstream ss(arg);
        string component;
        // go through the directories of the path argument
        while (getline(ss, component, '/')) {
            if (!component.empty()) {
                MyVector<Position*> childrenPos = currentNode->childrenPositions();
                for (int i = 0; i < childrenPos.getSize(); i++) {
                    Position* child = childrenPos[i];
                    Inode* childNode = child->getNode();
                    if (childNode->getName() == component && childNode->isFolder()){
                        currentNode = child;
                    }
                }
            }
        }
        if (currentNode->getNode()->getName() != component) //check if the desired path is not reached
        {
            currentNode = prevPos;
            cout << "The path is not correct \n";
        }
    }
    else if(arg == "" || arg[0] == '/') // go to the root dir
    {
        prevPos = currentNode;
        currentNode = _root;
    }
    // change the dir to another one within this dir
    else
    {
        MyVector<Position*> childrenPos = currentNode->childrenPositions();
        for (int i = 0; i < childrenPos.getSize(); i++) {
            Position* child = childrenPos[i];
            Inode* childNode = child->getNode();
            // checking if the dir is found
            if (childNode->getName() == arg && childNode->isFolder()){
                prevPos = currentNode;
                currentNode = child;
            }
        }
    }
    
}

void VFS_Tree::realpath(string name) const
{
    bool isFound;
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* child = childrenPos[i];
        Inode* childNode = child->getNode();
        // check if the file exists, add its name to its dir name and return the full path
        if (childNode->getName() == name && !childNode->isFolder()){
            cout << pwd(currentNode) << "/" << name << endl;
            isFound = true;
        }
    }
    if(!isFound){ cout << "No file with the provided name within this directory \n"; }
}

string VFS_Tree::pwd(Position* current) const
{
    string path = "";

    if(current->getNode() == _root->getNode()) // if the current dir is the root
    {
        path += "/";
    }else
    {
        MyStack<Position*> pathStack;
        // keep adding the nodes to the stack from this dir until reaching the root
        while (!current->isRoot())
        {   
            pathStack.push(current);
            Position* currParentPos = new Position(current->inode->parent);
            current = currParentPos;
        }
        // modifying the path
        while (!pathStack.empty())
        {
            path += "/";
            path += pathStack.top()->inode->fname;
            pathStack.pop();
        }
    }

    return path;
}

void VFS_Tree::mv(string filename, string foldername)
{
    Position* requiredFile = NULL;
    int fileIndex;
    Position* requiredFolder = NULL;
    MyVector<Position*> childrenPos = currentNode->childrenPositions();

    // loop through currrent dir to check if the file and the folder exist
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* childPos = childrenPos[i];
        Inode* childNode = childPos->getNode();
        if (childNode->getName() == filename && !childNode->isFolder()){
            requiredFile = childPos;
            fileIndex = i;
        }
        if (childNode->getName() == foldername && childNode->isFolder()){
            requiredFolder = childPos;
        }
    }

    // if the file and the folder exist, move the node to the folder    
    if(requiredFile && requiredFolder)
    {
        currentNode->getNode()->children.erase(fileIndex);
        requiredFolder->getNode()->children.pushBack(requiredFile->getNode());
        requiredFile->getNode()->parent = requiredFolder->getNode();
    }
    else
    {
        if(!requiredFile && !requiredFolder){cout << "The file and the Folder are not found \n";}
        else if (!requiredFolder){cout << "This Folder is not found \n";}
        else {cout << "This file is not found \n";}
    }
}

void VFS_Tree::mvPath(string fileName, string folderName)
{
    string nowDir = pwd(currentNode);
    Position* requiredFile = NULL;
    int fileIndex;
    Position* requiredFolder = NULL;
    string filepath, filefile, folderpath, folderfolder;

    size_t lastSlash = fileName.rfind('/');
    if (lastSlash != string::npos) {   // check if the slash was found
        filepath = fileName.substr(0, lastSlash);   // extract the path
        filefile = fileName.substr(lastSlash + 1);   // extract the file
    } else {
        filepath = "";
        filefile = fileName;
    }
    size_t lastSlash2 = folderName.rfind('/');
    if (lastSlash != string::npos) {   // check if the slash was found
        folderpath = folderName.substr(0, lastSlash2);   // extract the path
        folderfolder = folderName.substr(lastSlash2 + 1);   // extract the file
    } else {
        folderpath = "";
        folderfolder = folderName;
    }

    // loop through file's dir to check if the file exists
    cd(filepath);
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* childPos = childrenPos[i];
        Inode* childNode = childPos->getNode();
        if (childNode->getName() == filefile && !childNode->isFolder()){
            requiredFile = childPos;
            fileIndex = i;
        }
    }
    if(requiredFile){currentNode->getNode()->children.erase(fileIndex);}

    // loop through folder's dir to check if the folder exists
    cd(folderpath);
    childrenPos = currentNode->childrenPositions();
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* childPos = childrenPos[i];
        Inode* childNode = childPos->getNode();
        if (childNode->getName() == folderfolder && childNode->isFolder()){
            requiredFolder = childPos;
        }
    }
    // move the file to the folder
    if(requiredFolder){
        requiredFolder->getNode()->children.pushBack(requiredFile->getNode());
        requiredFile->getNode()->parent = requiredFolder->getNode();
    }
    // return back to the same dir
    cd(nowDir);

}

void VFS_Tree::rm(string name)
{
    Position* required = NULL;
    int requiredIndex;
    MyVector<Position*> childrenPos = currentNode->childrenPositions();
    // loop through the current dir to check if the file or folder exists
    for (int i = 0; i < childrenPos.getSize(); i++) {
        Position* childPos = childrenPos[i];
        Inode* childNode = childPos->getNode();
        if (childNode->getName() == name){
            required = childPos;
            requiredIndex = i;
        }
    }

    if(bin.getSize() == 20) // check that the bin is not full
    {
        cout << "Bin is full \n";
    }
    // remove the node and decrement the tree nodes number
    else if(required)
    {
        currentNode->getNode()->children.erase(requiredIndex);
        if(required->getNode()->isFolder())
        {
            MyStack<Position*> binStack;
            binStack.push(required);

            while (!binStack.empty()) {
                Position* curr = binStack.top();
                binStack.pop();
                n--;
                //Add children of the current inode to the stack for further search
                MyVector<Position*> childrenPos = curr->childrenPositions();
                for (int i = 0; i < childrenPos.getSize(); i++) {
                    Position* child = childrenPos[i];
                    binStack.push(child);
                }
            }
        }
        bin.enqueue(required);
        n--;

    }
    else{cout << "The file/folder is not found\n";}

}

void VFS_Tree::rmPath(string name)
{
    string nowDir = pwd(currentNode);
    string filepath, filefile;

    size_t lastSlash = name.rfind('/');
    if (lastSlash != string::npos) {   // check if the slash was found
        filepath = name.substr(0, lastSlash);   // extract the path
        filefile = name.substr(lastSlash + 1);   // extract the file
    } else {
        filepath = "";
        filefile = name;
    }

    // go to the file's or folder's dir, call the rm function and return back to the same dir
    cd(filepath);
    rm(filefile);
    cd(nowDir);

}

void VFS_Tree::emptyBin()
{
    while (!bin.isEmpty())
    {
        bin.dequeue();   
    }
}


void VFS_Tree::showBin()
{
    if(bin.isEmpty())
    {
        cout << "Bin is empty \n";
    }
    else
    {
        Position* firstDeleted = bin.getFront();
        cout << pwd(firstDeleted) << endl;
    }
}

void VFS_Tree::recover()
{
    // get the first deleted node
    Position* firstDeleted = bin.getFront();
    Position* firstDeletedParent = new Position(firstDeleted->inode->parent);

    // if it is a folder, return it along with its descendants. If not, return the file node
    if(firstDeleted->inode->isFolder())
    {
        firstDeletedParent->inode->children.pushBack(firstDeleted->inode);
        bin.dequeue();
        MyStack<Position*> binStack;
        binStack.push(firstDeleted);

        while (!binStack.empty()) {
            Position* curr = binStack.top();
            binStack.pop();
            n++;
            //Add children of the current inode to the stack for further search
            MyVector<Position*> childrenPos = curr->childrenPositions();
            for (int i = 0; i < childrenPos.getSize(); i++) {
                Position* child = childrenPos[i];
                binStack.push(child);
            }
        }
    }
    else
    {
        firstDeletedParent->inode->children.pushBack(firstDeleted->inode);
        bin.dequeue();
    }
}

int VFS_Tree::getSize(string name) {
    // Search for the node with the given name starting from the root node
    MyStack<Inode*> nodeStack;
    nodeStack.push(_root->getNode());

    while (!nodeStack.empty()) {
        Inode* currentNode = nodeStack.top();
        nodeStack.pop();

        // Check if the current node has the desired name
        if (currentNode->fname == name) {
            // If it is a file, return its size
            if (currentNode->isFile) {
                return currentNode->size;
            }
            // If it is a folder, calculate the total size of the folder and its subfiles
            else {
                int totalSize = currentNode->size;
                MyVector<Inode*> children = currentNode->children;
                for (int i = 0; i < children.getSize(); i++) {
                    nodeStack.push(children[i]);
                    totalSize += getSize(children[i]->fname);
                }
                return totalSize;
            }
        }
        // If the current node is a folder, push its children into the stack
        else if (!currentNode->isFile) {
            MyVector<Inode*> children = currentNode->children;
            for (int i = 0; i < children.getSize(); i++) {
                nodeStack.push(children[i]);
            }
        }
    }

    // If the node is not found, return an error
    cout << "Error: Node not found" << endl;
    return -1;
}

void VFS_Tree::exportVFS()
{
    ofstream myfile("vfs.dat");
    // check the file openning
    if (!myfile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }
    MyStack<Inode*> nodeStack;
    MyVector<Inode*> nodeVector;
    nodeStack.push(_root->getNode());
    // store all the tree nodes in a vector
    while (!nodeStack.empty()) {
        Inode* currentNode = nodeStack.top();
        nodeStack.pop();

        Position* currentPos = new Position(currentNode);
        nodeVector.pushBack(currentNode);

        MyVector<Inode*> children = currentNode->children;
        for (int i = 0; i < children.getSize(); i++) {
            nodeStack.push(children[i]);
        }
    }
    // looping through the vector and exporting the data into a file
    for (int i = 0; i < nodeVector.getSize(); i++)
    {
        Inode* currentNode = nodeVector[i];
        Position* currentPos = new Position(currentNode);
        myfile << pwd(currentPos) << "," << currentNode->size << "," << currentNode->date << endl;
    }
    myfile.close();
}

void VFS_Tree::importVFS()
{
        string line;
        ifstream myfile("vfs.dat");
        // check the file openning 
        if (!myfile.is_open()) {
            cout << "Unable to open file." << endl;
            return;
        }
        //dummy code for the root node which is the first line
        getline(myfile, line); 
        istringstream ss(line);
        string name, sizeStr, date, path, file;
        getline(ss, name, ',');
        getline(ss, sizeStr, ',');
        getline(ss, date);
        _root->inode->setDate(date);

        while (getline(myfile, line)) {
            // split the line by comma and assign the substrings to variables
            istringstream ss(line);
            string name, sizeStr, date, path, file;
            getline(ss, name, ',');
            getline(ss, sizeStr, ',');
            getline(ss, date);
            int size = stoi(sizeStr);
            
            // parsing the first attribute to extract the path and the filename
            size_t lastSlash = name.rfind('/');
            if (lastSlash != string::npos) {
                path = name.substr(0, lastSlash);
                file = name.substr(lastSlash + 1);
            } else {
                path = "";
                file = name;
            }
            cd(path);

            // check if it contains . then it's a file. if not, it is a folder
            size_t dot_pos = file.find('.');
            if (dot_pos != string::npos)
            {
                touch(file, size);
                currentNode->inode->children[currentNode->inode->children.getSize()-1]->setDate(date);
            }
            else
            {
                mkdir(file);
                currentNode->inode->children[currentNode->inode->children.getSize()-1]->setDate(date);
            }   
        }
        cd("");
}


