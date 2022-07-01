#include "Header.h"
#include "StreamToString.h"


void CopyStreamToFloatVector(std::vector<float>& vec, std::istream& is)
{
    std::istream::sentry s(is);
    if (!s)
    {
        throw std::domain_error(FailedToCopy);
    }
    vec.clear();
    std::copy(std::istream_iterator<float>(is), std::istream_iterator<float>(), std::back_inserter(vec));
}

float MinElement(std::vector <float>& vec)
{
    const auto endIt = vec.end();
    const auto minIt = std::min_element(vec.begin(), endIt);
    if (minIt == endIt)
    {
        return 0;
    }
    else
    {
        return *minIt;
    }
}

std::vector <float> GetMultipliedFloatVectorByValue(std::vector <float>& vec, float val)
{
    std::vector <float> newVec;
    newVec.resize(vec.size());
    std::transform(vec.begin(), vec.end(), newVec.begin(), [=](const auto& v) { return v * val; });
    return newVec;
}

void PrintFloatVec(std::vector <float>& vec, std::ostream& os)
{
    std::ostream::sentry s(os);
    if(!s)
    {
        throw std::domain_error(FailedToPrint);
    }
    os << std::setprecision(3);
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<float>(os, " "));
}
