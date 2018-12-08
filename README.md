# Big-Number
The number type which can hold and operate(work with) bigger double values whose digits are more than milions or even billions.

```c++
int main(){

  Digit<char> a;
  Digit<> b("5.32");  //<> indicates char

  std::cin>>a;
  std::cout<<a*b<<std::endl;

  return 1;
}
```
