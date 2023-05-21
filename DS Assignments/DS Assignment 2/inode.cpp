#include "inode.h"

Inode::Inode(string name, int fSize, bool isFile, string date) : fname(name), size(fSize), isFile(isFile), date(date)
{
    parent = nullptr;
}

void Inode::setDate(string newDate)
{
    date = newDate;
}