//hello
#include <iostream>
#include "MyUtilities.h"
#include <vector>
#include <fstream>
using namespace std;


int main()
{
	try 
	{
		MyUtilities a;
		a.displayMenu();
	}
	catch (string s)
	{
		cout << "The file \"" << s << "\" could not be opened!";
	}
	return 0;

}
