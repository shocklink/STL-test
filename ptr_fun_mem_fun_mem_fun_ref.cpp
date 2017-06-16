/* 
http://www.itread01.com/articles/1476783924.html

我們已經知道仿函數通過繼承unary_function和binary_function可以變成可配接對象，
那麽普通函數或者類的成員函數如何變成可配接對象呢？這就需要用到標題中的三個函數了。

上述代碼中，首先調用not2(ptr_fun(sortFun))，用ptr_fun對普通函數sortFun進行配接；
其次調用mem_fun_ref(&sortObj::memComp_const)和not2(mem_fun(&sortObj::memComp))對sortObj類的成員函數進行配接。

這裏有的童鞋可能有疑問：memComp明明只有一個形參，為什麽用not2而不是not1？成員函數在別調用的時候，會自動傳進this指針的，所以這裏還是兩個參數。
mem_fun和mem_fun_ref都是對類的成員函數進行配接，那麽它們有什麽區別嗎？
	相信細心的童鞋已經看出來了，當容器中存放的是對象實體的時候用mem_fun_ref，當容器中存放的是對象的指針的時候用mem_fun。


Summary:
	ptr_fun -> 對function進行adapt, 普通的函數轉換為一個函數對象
	mem_fun/_ref -> 對functor進行adapt, 一個類的成員函數，轉化為函數對象
	bind -> 對not不相容
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>     //ostream_iterator
#include <functional>   //not2

using namespace std;

class sortObj
{
public:
        bool memComp(const sortObj *other)
        {   
                return *this < *other;
        }   

        bool memComp_const(const sortObj &other) const
        {   
                return *this < other;
        }   
public:
        sortObj(int v) : value(v){}
        ~sortObj(){}

        friend bool operator<(const sortObj &lhs, const sortObj &rhs)
        {   
                return lhs.value < rhs.value;
        }

        friend ostream & operator<<(ostream &os, const sortObj &obj)
        {
                return os << obj.value << endl;
        }
private:
        int value;
};

bool sortFun(const sortObj &lhs, const sortObj &rhs)
{
        return lhs < rhs;
}

//把指針轉換成對象
sortObj & ptrToObj(sortObj *ptr)
{
        return *ptr;
}

int main()
{
        sortObj objArray[] = {
                sortObj(7),
                sortObj(4),
                sortObj(2),
                sortObj(9),
                sortObj(1)
        };
        vector<sortObj> objVec(objArray, objArray + sizeof(objArray) / sizeof(sortObj));

        //配接普通函數(降序)
        sort(objVec.begin(), objVec.end(), not2(ptr_fun(sortFun)));
        copy(objVec.begin(), objVec.end(), ostream_iterator<sortObj>(cout, ""));
        cout << endl;

        srand(time(NULL));
        random_shuffle(objVec.begin(), objVec.end());   //打亂順序
        //配接對象的成員函數(升序)
        sort(objVec.begin(), objVec.end(), mem_fun_ref(&sortObj::memComp_const));
        copy(objVec.begin(), objVec.end(), ostream_iterator<sortObj>(cout, ""));
        cout << endl;

        //配接指針的成員函數(降序)
        vector<sortObj *> objVecPtr;
        objVecPtr.push_back(new sortObj(7));    //內存泄漏了，不要在意這些細節
        objVecPtr.push_back(new sortObj(4));
        objVecPtr.push_back(new sortObj(2));
        objVecPtr.push_back(new sortObj(9));
        objVecPtr.push_back(new sortObj(1));
        sort(objVecPtr.begin(), objVecPtr.end(), not2(mem_fun(&sortObj::memComp)));
        transform(objVecPtr.begin(), objVecPtr.end(), ostream_iterator<sortObj>(cout, ""), ptrToObj);

        return 0;
}
