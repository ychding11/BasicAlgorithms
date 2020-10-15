#include "utils.h"
#include "algorithms.h"
#include <string>
#include <vector>

using std::set;
using std::vector;
using std::string;
using namespace test;

// Test by eyes
void testPermutation()
{
    string str = "abc";
    set<string> ret;
    permutation(str, 0, 2, ret);
    printContainer(ret);
}

void testCatalanNumber()
{
    /* https://oeis.org/A000108 */
    uint64_t catalans[] =
    {
    1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440, 9694845, 35357670,
    129644790, 477638700, 1767263190, 6564120420, 24466267020, 91482563640, 343059613650, 1289904147324,
    4861946401452, 18367353072152, 69533550916004, 263747951750360, 1002242216651368, 3814986502092304
    };
}

void testSqrtOfPerfectSquare(int n = 100)
{
    int fail = 0, success = 0; 
    printTestName(sqrtOfPerfectSquare);
    for (int i = 0; i < n; ++i)
    {
        int ret = sqrtOfPerfectSquare(i * i);
        if (i != ret)
        {
            ++fail;
            printTestcaseResult(0, printParam(i * i), printParam(ret), printParam(i));
        }
        else
        {
            ++success;
            printTestcaseResult(1, printParam(i * i), printParam(ret), printParam(i));
        }
    }
    for (int i = n * n + 1; i < (n + 1) * (n + 1); ++i)
    {
        int ret = sqrtOfPerfectSquare(i);
        if (-1 != ret)
        {
            ++fail;
            printTestcaseResult(0, printParam(i), printParam(ret), printParam(-1));
        }
        else
        {
            ++success;
            printTestcaseResult(1, printParam(i), printParam(ret), printParam(-1));
        }
    }
    printTestResult(success, fail);
}

void testUnpairNumber(int testcases = 10, int numElements = 10)
{
    DataSource datasource;
    vector<int> nums(numElements), temp(numElements);
    datasource.fillInDistinctData(nums, 100);
    printContainer(nums);
    temp = nums;
    for (auto a : temp) nums.push_back(a);
    printContainer(nums);
    for (int i = 0; i < testcases; ++i)
    {
        nums.push_back(100 + i);
        int temp = unpairNumber(nums);
        if (100 + i != temp)
        {
            // test failed
            printTestcaseResult(0, printParam(nums), printParam(temp), printParam(100 + i));
        }
        else
        {
            // test success
            printTestcaseResult(1, printParam(nums), printParam(temp), printParam(100 + i));
        }
        nums.pop_back();
    }
    for (int i = 0; i < testcases; ++i)
    {
        nums.push_back(100 + i);
        nums.push_back(100 + i + 1);
        int x, y;
        unpairNumbers(nums, x, y);
        if (x != 100 + i && x != 100 + i + 1)
        {
            // test failed
            printTestcaseResult(0, printParam(nums), printParam(x, y), printParam(100 + i, 100 + i + 1));
        }
        else
        {
            // test success
            printTestcaseResult(1, printParam(nums), printParam(x, y), printParam(100 + i, 100 + i + 1));
        }
        nums.pop_back();
        nums.pop_back();
    }
}

int main()
{
    testSqrtOfPerfectSquare();
    //testPermutation();
    //testUnpairNumber();
}
