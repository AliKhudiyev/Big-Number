# Big-Number
The number type which can hold and operate(work with) bigger double values whose digits are more than milions or even billions.

## Number hieararchy and its specifications.
There are 3 main classes you can use:
1. Number
2. Double
3. Int

Double and Int classes inherits from the Number class. The reason is any instance of Number is considered as a number which has
both real and imaginary part(even if one or both of them are 0). However, instances of Double and Int are considered as a real number, and more specifically "double" and "int" respectively.

Each individual class has its own specifaction(s).

## User-friendly functions.
- info : To get full information about the number
- type : To get its type(i.e. "Natural number")
- size : To get digit-character length for its real part(i.e. 5 for 32.70 )
- isize : To get digit-character length for its imaginary part
- seek : To get if SEEK is in the beginning position or not
- delimeter : To get its delimeter(i.e. '.' for number -5.70)
- `+` , `-` , `*` , `/` , `+=` , `-=` , `++` , `--` , `>` , `==` and many more overloaded arithmetic functions
- `<<` and `>>` stream operators


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
