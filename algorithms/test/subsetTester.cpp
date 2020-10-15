#include "utils.h"
#include "algorithms.h"
#include<set>
#include<limits>

using std::set;
using std::numeric_limits;
using namespace test;

void testMinSubsetDifference(int maxElementValue = 10, int maxElementNum = 3, int testcases = 3)
{
    int fail = 0, success = 0; 
    DataSource datasource;
    while (--testcases >= 0) 
    {
    vector<int> nums(maxElementNum);
    datasource.fillInData(nums, maxElementValue);
    vector<int> sums = allSubsetSum(nums);
    set<int> sets;
    int sum = 0; 
    int minDiff = numeric_limits<int>::max();
    for (auto a : nums)
    {
        sum += a;
    }
    for (auto a : sums)
    {
        sets.insert(a);
    }
    
    for (auto a : sets)
    {
        if (abs(sum - a - a) < minDiff)
            minDiff = abs(sum - a - a);
    }
    printContainer(nums);
    printContainer(sums);
    printContainer(sets);
    printTestName(minSubsetDifference);
    if (minDiff != minSubsetDifference(nums))
    {
            ++fail;
            std::cout << "- [Test Failed]";
            std::cout << "  Min Subset sum different Test." << std::endl;
            std::cout << "- -------------" << std::endl;
            printContainer(nums);
            std::cout << "- Target difference: " << minDiff << std::endl;
            std::cout << "- -------------" << std::endl;
    }
    else
    {
            ++success;
    }
    printTestResult(success, fail);
    }
}

int main(int argc, char* argv[])
{
    int maxElementValue = 10;
    int maxElementNum = 3;
    if (argc >= 2)
        maxElementNum = atoi(argv[1]);
    if (argc == 3)
        maxElementValue = atoi(argv[2]);

    testMinSubsetDifference();

    DataSource datasource;
    vector<int> nums(maxElementNum);
    datasource.fillInData(nums, maxElementValue);
    printContainer(nums);
    vector<int> sums = allSubsetSum(nums);
    printContainer(sums);
    set<int> sets;
    for (auto a : sums) sets.insert(a);
    printContainer(sets);
    vector<int> exludeDataset = datasource.dataSetExlude(sets, maxElementValue);
    printContainer(exludeDataset);
    
    printTestName(subsetExist);
    // Prepare test dataset ok, begin to test.
    int fail = 0, success = 0; 
    for (auto a : exludeDataset)
    {
        if (subsetExist(nums, a))
        {
            ++fail;
            std::cout << "- [Test Failed]";
            std::cout << "  Exlude dataset Test." << std::endl;
            std::cout << "- -------------" << std::endl;
            printContainer(nums);
            std::cout << "- Target sum: " << a << std::endl;
            std::cout << "- -------------" << std::endl;
        }
        else
        {
            ++success;
        }
    }
    for (auto a : sums)
    {
        if (!subsetExist(nums, a))
        {
            ++fail;
            std::cout << "- [Test Failed]";
            std::cout << "  Include dataset Test." << std::endl;
            std::cout << "- -------------" << std::endl;
            printContainer(nums);
            std::cout << "- Target sum: " << a << std::endl;
            std::cout << "- -------------" << std::endl;
        }
        else
        {
            ++success;
        }
    }
    printTestResult(success, fail);
}
