#include "utils.h"
#include "algorithms.h"
#include<set>

using std::set;
using namespace test;

template<typename T>
bool isSame(const vector<T> &set1, const vector<T> &set2)
{
   int n = set1.size();
   int m = set2.size();
   if (m != n) return false;
   for (int i = 0; i < n; ++i)
   {
       if (set1[i] != set2[i]) return false;
   }
   return true;
}

template<typename T>
bool isContained(const vector<T> &set1, const vector<T> &set2)
{
   int n = set1.size();
   int m = set2.size();
   if (m != n) return false;
   for (int i = 0; i < n; ++i)
   {
       T temp = set1[i];
       for (int j = 0; j < n; ++j)
       {
            if(set2[j] == temp) return true;
       }
   }
   return false;
}

int main()
{
    DataSource datasource;
    int fail = 0, success = 0; 
    vector<int> prvDataSet;
    for (int i = 0; i < 10; ++i)
    {
        vector<int> nums(10);
        datasource.fillInData(nums, 100);
        printContainer(nums);
        if (isSame(prvDataSet, nums))
        {
            ++fail;
            std::cout << "- [Test Failed]";
            std::cout << "  Generate Random dataset Test." << std::endl;
            std::cout << "- -------------" << std::endl;
            printContainer(prvDataSet);
            printContainer(nums);
            std::cout << "- -------------" << std::endl;
        }
        else ++success;

        prvDataSet = nums;
        set<int> sets;
        for (auto a : nums) sets.insert(a);
        vector<int> dataset1 = datasource.dataSetExlude(sets, 100);
        if (isContained(dataset1, nums))
        {
            ++fail;
            std::cout << "- [Test Failed]";
            std::cout << "  Generate Exlude dataset Test." << std::endl;
            std::cout << "- -------------" << std::endl;
            printContainer(prvDataSet);
            printContainer(nums);
            std::cout << "- -------------" << std::endl;
        }
        else ++success; 
    }
    std::cout << "Test result  : "
              << success << " cases success,"
              << fail << " cases fail."
              << std::endl;
}
