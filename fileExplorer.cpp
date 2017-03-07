#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void goToLine(string fileName, int lineNumber)
{
	fstream fileStream;
	fileStream.open(fileName, std::fstream::app);
	for (int i = 0; i<lineNumber - 1; i++) fileStream << "\n";
	fileStream << "Here I am on line number " << lineNumber << endl;
}

void addStringToEndofFile(string fileName, string str)
{
	fstream fileStream;
	fileStream.open(fileName, std::fstream::app);
	if (fileStream.is_open())
	{
		fileStream << str << endl;
		fileStream.close();
	}
	else
		cout << "Error!" << endl;
}

void replaceEntierFile(string fileName, string str)
{
	fstream fileStream;
	fileStream.open(fileName, std::fstream::out);
	if (fileStream.is_open())
	{
		fileStream << str << endl;
		fileStream.close();
	}
	else
		cout << "Error!" << endl;
}

int getLineOfString(string fileName, string strSearch)
{
	ifstream iFileStream(fileName);
	string line;
	int lineNumber = 0;
	size_t pos;
	while (getline(iFileStream, line))
	{
		lineNumber++;
		pos = line.find(strSearch); // search
		if (pos != string::npos) // string::npos is returned if string is not found
		{
			cout << "Found! at line: " << lineNumber << " and pos: " << pos << endl;
			break;
		}
	}
	return lineNumber;
}

void replaceLineOfFile(string fileName, int lNumber, string replaceStr)
{
	fstream fileStream;
	fileStream.open(fileName, fstream::in);
	string line;
	int lineNumber = 0, totalChar = 0;
	int seekSize = 0;

	while (getline(fileStream, line))
	{
		if (lineNumber == lNumber)
		{
			break;
		}
		else
		{
			totalChar += line.length();
			lineNumber++;
		}
	}
	fileStream.close();
	cout << "Line:" << lineNumber << endl;

	// Magic goes here :)
	fstream ffile;
	ffile.open(fileName);
	//ffile.seekp(lNumber);
	ffile.seekp(totalChar+1);
	long pos1 = ffile.tellp();
	cout << pos1 << endl;
	char *charReplaceStr = new char[replaceStr.length() + 1];
	for (int i = 0; i<replaceStr.length(); ++i) {
		charReplaceStr[i] = replaceStr[i];
	}
	ffile.write("\n", 1);
	ffile.write(charReplaceStr, replaceStr.length());
	ffile.close();

}

int main()
{
	
	string fileName = "fileName.txt";
	string stringToAdd = "Hey";
	string replaceStr = "Hi";
	addStringToEndofFile(fileName,stringToAdd);
	//replaceEntierFile(fileName, stringToAdd);
	//int l = getLineOfString(fileName, stringToAdd);
	//cout << "Line number:" << l << endl;
	replaceLineOfFile(fileName, 4, replaceStr);
	system("pause");
	return 0;
}