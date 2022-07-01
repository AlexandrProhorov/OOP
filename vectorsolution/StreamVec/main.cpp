#include "Header.h"
#include "StreamToString.h"




int main()
{
    std::vector <float> vector;
    std::vector <float> finvec;
   /* const auto minVal = MinElement(vector);
    //const auto& newVec = GetMultipliedFloatVectorByValue(vector, minVal);
    std::vector <float> newVec = GetMultipliedFloatVectorByValue(vector, minVal);
    //CopyStreamIntoVector(std::cin, vector);
    CopyStreamToFloatVector(vector, std::cin);
    /*if (vector.size() == 0)
    {
        std::cout << Error_Stream;
        return 0;
    }
    MinElement(vector);
    GetMultipliedFloatVectorByValue(vector, minVal);
    //Print(newVec, vector);
	*/

	try
	{
		std::vector <float> vec{};
		CopyStreamToFloatVector(vec, std::cin);

		const auto minVecEl = MinElement(vec);

		std::vector <float> newVec = GetMultipliedFloatVectorByValue(vec, minVecEl);

		std::cout << "Source vector: ";
		PrintFloatVec(vec, std::cout);
		std::cout << std::endl;
		std::cout << "Result vector: ";
		PrintFloatVec(newVec, std::cout);
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}


