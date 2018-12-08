# Big-Number
The number type which can hold and operate(work with) bigger double values whose digits are more than milions or even billions.

Using it is very easy and simply. All you need to do is download the library to your computer, then use these libraries in your programs with ```c++ #include"number.hpp" ``` for example.

```c++
int main(){

  Digit<char> a;
  Digit<> b("5.32");  //<> indicates char

  std::cin>>a;
  std::cout<<a*b<<std::endl;

  return 0;
}
```
