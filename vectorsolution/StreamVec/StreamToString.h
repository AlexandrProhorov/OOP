#pragma once
#include "Header.h"

//void CopyStreamIntoVector(std::istream& stream, std::vector<float>& vector);
void CopyStreamToFloatVector(std::vector<float>& vec, std::istream& is);
std::vector <float> GetMultipliedFloatVectorByValue(std::vector <float>& vector, float val);
float MinElement(std::vector <float>& vector);
void PrintFloatVec(std::vector <float>& vec, std::ostream& os);
const std::string Error_Stream = "Bad input - please, enter some numbers \n";
const std::string Sorted = "Sorted stream: \n";
const std::string Unsorted = "Unsorted stream: \n";
const std::domain_error FailedToPrint("Failed to print");
const std::domain_error FailedToCopy("Failed to copy");
