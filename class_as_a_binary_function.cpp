#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>     //ostream_iterator
#include <functional>   //binary_function, not2

using namespace std;

//第一個參數，第二個參數，返回值
struct myLess : public binary_function<int, int, bool> //如果不繼承binary_function, 則下面的not2無法使用
{
        bool operator()(int lhs, int rhs) const
        {   
                return lhs < rhs;
        }   
};

int main()
{
        int IntArray[] = {7,4,2,9,1};
        sort(IntArray, IntArray + sizeof(IntArray) / sizeof(int), not2(myLess()));
        copy(IntArray, IntArray + sizeof(IntArray) / sizeof(int), ostream_iterator<int>(cout, "\n"));
        return 0;
}
