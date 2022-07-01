#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



int main(int argc, char* argv[])
{
	const string argcount = "wrong parameters count, use this format: CopyFile.exe <input.txt> <output.txt>\n";
	const string openfile = "files were opened\n";
	const string aintopenfile = "files wasnt opened\n";
	if (argc != 3)
	{
		cout << argcount;
		return 1;
	}
	char ch;
	ifstream filein;
	filein.open(argv[1]);
	ofstream fileout;
	fileout.open(argv[2]);

	if ((fileout.is_open()) && (filein.is_open()))
	{
		cout << openfile;
		while ((!filein.eof()) && filein.get(ch))
		{
			fileout.put(ch);
			fileout.flush();
		}

	}
	else
	{
		cout << aintopenfile;
		return 1;
	}

	filein.close();
	fileout.close();
	system("pause");
	return 0;
	
}