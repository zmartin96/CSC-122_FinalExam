#include "MyUtilities.h"

void MyUtilities::readData(const string& inFileName, int num)
{
    //check that file is valid and open it
    ifstream inFile;
    inFile.open(inFileName);
    if (!inFile) throw string(inFileName);
    
    int helper;
    while (inFile >> helper)
        numList.push_back(helper);
    cout << "\nThe values have been read\n";
    for (int i = 0; i < num; i++)
        cout << numList[i] << " "; //output in original order
    inFile.close();

}

void MyUtilities::print(const string& outFileName,int num)
{
    BST<int> tree;
    for (int i = 0; i < num; i++)
        tree.insert(numList[i]);

    //check that file is valid and open it
    fstream outFile;
    outFile.open(outFileName);
    if (!outFile) throw string(outFileName);

    //traverse the tree with all three methods
    tree.showInOrder(outFile);
    tree.showInOrder(cout);
    tree.showPreOrder(outFile);
    tree.showPreOrder(cout);
    tree.showPostOrder(outFile);
    tree.showPostOrder(cout);


    outFile.close();
}

void MyUtilities::writeData(const string& outFileName,int num)
{
    //check that file is valid and open it with ios binary flag
    fstream outFile;
    outFile.open(outFileName, ios::out | ios::binary);
    if (!outFile) throw string(outFileName);

    //write numList to file
    outFile.write(reinterpret_cast<char*>(&numList),num*sizeof(numList));

    outFile.close();
}

void MyUtilities::readBinaryData(const string& inFileName,int num)
{
    //check that file is valid and open it with ios binary flag
    fstream inFile;
    inFile.open(inFileName, ios::in | ios::binary);
    if (!inFile) throw string(inFileName);

    //read to numList
    inFile.read(reinterpret_cast<char*>(&numList), num*sizeof(numList));

    cout << "\nThe values have been doubled\n";
    for (int i = 0; i < num; i++)
    {
        numList[i] = numList[i] * 2; //double each number
        cout << numList[i] << " "; //output in original order
    }
    
    inFile.close();
}

void MyUtilities::displayMenu()
{
    string inFile = "",
        binaryFile = "numbers.dat";
    char quit=' ';
    int num;

    //user entered data
    cout << "Enter the name of the data file to read from: ";
    cin >> inFile;
    cout << "Enter the number of numbers to read: ";
    cin >> num;
    //q to quit per the directions
    do
    {
        cout << "Enter q to quit: ";
        cin >> quit;
    } while (toupper(quit) != 'Q');


    readData(inFile, num);
    writeData(binaryFile,num);
    readBinaryData(binaryFile,num);
    print("numbers.txt",num);
}
