#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "BST.h"
using namespace std;

class MyUtilities
{
private:
    vector<int> numList;// , numList2;
    void readData(const string& inFileName, int num),
        readBinaryData(const string& inFileName,int num),
		writeData(const string& outFileName,int num),
        print(const string& outFileName, int num);
public:
    void displayMenu();
};