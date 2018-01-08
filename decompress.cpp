#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "LinearProbing.h"

using namespace std;

// Simple main
int main()
{
	int code = -1;


	string ITEM_NOT_FOUND = "!!??::";
	HashTable<string> H(ITEM_NOT_FOUND);
	int NOT_FOUND = -11;
	HashTable<int> Hcode(NOT_FOUND);

	char k = 0;

	for (int j = 0; j < 255; j++)
	{
		string sss = "";
		sss.push_back(k++);
		
		H.insert(sss,sss);
		Hcode.insert(++code, sss);
		//	cout << H.findPos(sss) << " " << H.findPos(sss)<<endl;
	}





	string fileReadName, writeFileName;
	getline(cin, fileReadName);
	getline(cin, writeFileName);



	string line;
	string allChars = "";
	ifstream myfile(fileReadName);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			allChars += line;
			
		}
		myfile.close();
	}
	else { cout << "ERROR while loading the file" << endl; }

	



	string zline;
	ifstream yourfile("Dictionary.txt");

	if (yourfile.is_open())
	{
		while (getline(yourfile, zline))
		{
			H.insert(zline,zline); 
			Hcode.insert(++code, zline);
		//	cout << zline << endl;
		}
		yourfile.close();
	}
	else { cout << "ERROR Copy Dictionary.txt to this directory from compression directory" << endl; }



	string buf; // Have a buffer string
	stringstream ss(allChars); // Insert the string into a stream


	ofstream outfile;
	outfile.open(writeFileName);


	while (ss >> buf)
	{
		//outfile << H.findIt(atoi(buf.c_str())) ;
		//cout << atoi(buf.c_str())<<" ";
		outfile <<H.findIt( Hcode.findPos2(atoi(buf.c_str())));
	}




	outfile.close();



	

	int z;



	cin >> z;

	return 0;
}
