#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../StreamVec/StreamToString.h"

SCENARIO("Trying to copy stream  to vector")
{
	std::vector<float> WorkingVector{};
	WHEN("Trying to processing stream that contain float elements")
	{
		std::istringstream ss{ "1.4 12.1" };
		const std::vector<float> v{ 1.4, 12.1 };
		CopyStreamToFloatVector(WorkingVector, ss);
		THEN("Vector is same as stream")
		{
			REQUIRE(WorkingVector == v);
			REQUIRE(ss.eof());
		}
	}
	WHEN("Trying to processing empty stream")
	{
		std::istringstream ss{};
		std::domain_error ex = std::domain_error("Failed to copy stream's content to float vector");
		//CopyStreamToFloatVector(WorkingVector, ss);
		THEN("Vector is empty")
		{
			REQUIRE_THROWS(CopyStreamToFloatVector(WorkingVector, ss), ex);
		}
	}
	WHEN("Trying to processing stream that contain one element")
	{
		std::istringstream ss{ "10" };
		CopyStreamToFloatVector(WorkingVector, ss);
		THEN("Vector is same as stream")
		{
			REQUIRE(WorkingVector[0] == 10);
			REQUIRE(ss.eof());
		}
	}
}

SCENARIO("Trying to process MinElement tests")
{
	std::vector<float> WorkingVec{ 3, 2, 4, 5 };
	const auto minVal = MinElement(WorkingVec);
	REQUIRE(minVal == 2);
	WorkingVec = { -3, 2 };
	const auto min = MinElement(WorkingVec);
	REQUIRE(min == -3);
}

SCENARIO("Trying to processing available vector")
{

	//const auto newVec = MultMin(vector, minVal);
	std::vector<float> WorkingVec{ 3, 2, 4, 5 };
	const auto minVal = MinElement(WorkingVec);
	const std::size_t VecSize = std::size(WorkingVec);
	WHEN("Trying to multiply vectors elements on minimum value")
	{
		std::vector <float> newVec = GetMultipliedFloatVectorByValue(WorkingVec, minVal);
		//GetMultipliedFloatVectorByValue(WorkingVec, minVal);
		THEN("Vector has correct values")
		{
			REQUIRE(newVec.size() == 4);
			REQUIRE(newVec[0] == 6);
			REQUIRE(newVec[1] == 4);
			REQUIRE(newVec[2] == 8);
			REQUIRE(newVec[3] == 10);
		}
	}

	
	WHEN("zero vector")
	{
		WorkingVec = { 2 };
		const float minval = MinElement(WorkingVec);
		std::vector <float> vec = GetMultipliedFloatVectorByValue(WorkingVec, minval);
		//GetMultipliedFloatVectorByValue(WorkingVec, minVal);
		THEN("Vector has correct values")
		{
			REQUIRE(vec.size() == 1);
			REQUIRE(vec[0] == 4);
		}
	}
}