#include <iostream>
#include <string>

using namespace std;


string DecToBin(int value);

int main(int argc, char* argv[])
{
    const string wrongcount = "wrong parameters count\n";
    const string invvalue = "invalid value\n";
    const string notdigit = "not digit\n";

    if (argc != 2)
    {
        cout << wrongcount;
        return 0;
    }

    int dec = 0;
    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            cout << notdigit;
            return 0;
        }
    }

    dec = atoi(argv[1]);

    if (dec <= 0) 
    {
        cout << invvalue;
        return 0;
    }
 
            
    std::cout << DecToBin(dec) << std::endl;
    return 0;

}

string DecToBin(int value)
{
    if (value == 0)
    {
        return "0";
    }
     
    string bin = "";
    while (value > 0)
    {
        bin = ((value & 1) == 0 ? '0' : '1') + bin;
        value >>= 1;
    }

    return bin;
}