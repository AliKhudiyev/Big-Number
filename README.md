# Big-Number
The number type which can hold and operate(work with) bigger double values whose digits are more than milions or even billions.

Using it is very easy and simply. All you need to do is download the library to your computer, then use these libraries in your programs with ```#include"number.hpp"``` for example.

```c++
#include<iostream>
#include"number.hpp"

int main(){

  Number<char> a(4, 8), b("-4", "53.25");
  Number<> sum;   // same with Number<char> sum;
  
  cin>>sum;
  cout<<((a+b==sum)? "Yes" : "No")<<'\n';   // Comparing abs values

  return 0;
}
```
