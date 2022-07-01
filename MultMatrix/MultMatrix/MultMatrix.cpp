#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <iomanip>


const int Matrix_Length = 3;

void OpenMatrix(std::vector<std::vector<double>>& Arr, std::istream& filename)
{

    int i = 0;
    int j = 0;

    while (!filename.eof())
    {
        for (int i = 0; i < Matrix_Length; i++)
            for (int j = 0; j < Matrix_Length; j++)
                filename >> Arr[i][j];
    }

    //filename.close();
}

void MultMatrix(std::vector<std::vector<double>>& First_Arr, std::vector<std::vector<double>>& Second_Arr, std::vector<std::vector<double>>& Third_Arr)
{

    int i = 0;
    int j = 0;

    for (int i = 0; i < Matrix_Length; i++)
    {
        for (int j = 0; j < Matrix_Length; j++)
        {
            Third_Arr[i][j] = 0;
            for (int k = 0; k < Matrix_Length; k++)
            {
                Third_Arr[i][j] += First_Arr[i][k] * Second_Arr[k][j];
            }
        }
    }
}

void PrintMatrix(std::vector<std::vector<double>>& Third_Arr)
{

    int i = 0;
    int j = 0;

    for (int i = 0; i < Matrix_Length; i++)
    {
        for (int j = 0; j < Matrix_Length; j++)
        {
            std::cout << Third_Arr[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << std::setprecision(3);
}


int main(int argc, char* argv[])
{
    const std::string Wrong_Count = "wrong parameters count, usage: multmatrix.exe <firstmatrixfile.txt> <secondmatrixfile.txt>\n";
    const std::string Cant_Open = "file wasnt opened\n";
    const std::string Open_File = "files were opened\n";
    const std::string Empty_First_File = "first file is empty\n";
    const std::string Empty_Second_File = "second file is empty\n";
    std::vector <std::vector <double>> First_Arr(Matrix_Length, std::vector <double>(Matrix_Length));
    std::vector <std::vector <double>> Second_Arr(Matrix_Length, std::vector <double>(Matrix_Length));
    std::vector <std::vector <double>> Third_Arr(Matrix_Length, std::vector <double>(Matrix_Length));
    std::ifstream First_Matrix;
    std::ifstream Second_Matrix;
    if (argc != 3)
    {
        std::cout << Wrong_Count;
        return 0;
    }
    First_Matrix.open(argv[1]);
    Second_Matrix.open(argv[2]);


    if (!First_Matrix.is_open())
    {
        std::cout << Cant_Open;
        return 0;
    }

    if (First_Matrix.peek() == EOF)
    {
        std::cout << Empty_First_File;
        return 0;
    }

    if (!Second_Matrix.is_open())
    {
        std::cout << Cant_Open;
    }

    if (Second_Matrix.peek() == EOF)
    {
        std::cout << Empty_Second_File;
        return 0;
    }

    OpenMatrix(First_Arr, First_Matrix);

    OpenMatrix(Second_Arr, Second_Matrix);

    MultMatrix(First_Arr, Second_Arr, Third_Arr);

    PrintMatrix(Third_Arr);

    return 0;

}




