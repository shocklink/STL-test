# STL-test

* Quick STL usage:
http://net.pku.edu.cn/~yhf/UsingSTL.htm

* online compiler: https://www.tutorialspoint.com/compile_cpp_online.php

or g++ -o main .cpp

* 仿函数(functor)，就是使一个类的使用看上去象一个函数。其实现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了。

* 我們已經知道仿函數通過繼承unary_function和binary_function可以變成可配接對象，那麽普通函數或者類的成員函數如何變成可配接對象呢？這就需要用到標題中的三個函數了。
ptr_fun、mem_fun和mem_fun_ref or bind

