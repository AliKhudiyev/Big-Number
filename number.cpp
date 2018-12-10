
#ifndef _NUMBER_
#define _NUMBER_
#include"number.hpp"
#endif

template<class Char_T>
void Number<Char_T>::init(const std::string& number, const std::string& inumber, const char delim){
    
    delete idigit_;
    delete digit_;
    
    std::string inum=inumber, num=number;
        
    if(inumber[0]=='+' || inumber[0]=='-') inum=inumber.substr(1, inumber.size()-1);
    idigit_=new Digit<Char_T>(inum, delim);
    isign_=inumber[0]=='-'? -1 : 1 ;
    isize_=inum.size();

    if(number[0]=='+' || number[0]=='-') num=number.substr(1, number.size()-1);
    digit_=new Digit<Char_T>(num, delim);
    sign_=number[0]=='-'? -1 : 1 ;
    size_=num.size();
}

template<class Char_T>
size_t Number<Char_T>::isize() const{
    return isize_;
}

template<class Char_T>
char Number<Char_T>::delimeter() const{
    return delim_;
}

template<class Char_T>
size_t Number<Char_T>::size() const{
    return size_;
}

template<class Char_T>
bool Number<Char_T>::seek() const{
    return SEEK__;
}

template<class Char_T>
const std::string Number<Char_T>::type() const{
    return type_;
}

template<class Char_T>
const std::string Number<Char_T>::info() const{
    std::string info;

    info="The number of digits of imaginary number : ";
    info+=std::to_string(isize_);
    info+=" \nThe number of digits of real number : ";
    info+=std::to_string(size_);
    info+=" \nThe delimeter : ";
    info+=delim_;
    info+=" \nSeek position : ";
    if(SEEK__){
        info+="SEEK_BEG";
    } else{
        info+="SEEK_ORG";
    }
    info+=" \nType : ";
    info+=type_;
    info+=" \n";

    return info;
}

std::ostream& operator<<(std::ostream& out, const Number<char>& Num){
    char sgn='-', isgn='-';
    if(Num.sign_==1) sgn='+';
    if(Num.isign_==1) isgn='+';
    out<<sgn<<*Num.digit_<<isgn<<*Num.idigit_<<"*"<<Num.imaginary_number_;
    return out;
}

std::istream& operator>>(std::istream& in, Number<char>& Num){
    std::string number, inumber;
    in>>number>>inumber;
    Num.init(number, inumber);
    return in;
}

    // INCOMPLETED OPERATORS WHICH MAY POSSIBLE OPERATE WRONGLY !

template<class Char_T>
Char_T Number<Char_T>::operator[](int position) const{
    ;
}

template<class Char_T>
void Number<Char_T>::operator+=(const Number& Num){
    if(sign_==Num.sign_ && isign_==Num.isign_){
        *digit_+=*Num.digit_;
        *idigit_+=*Num.idigit_;
    } else if(sign_!=Num.sign_ && isign_!=Num.isign_){
        if((*digit_<*Num.digit_)) sign_*=-1;
        if(*idigit_<*Num.idigit_) isign_*=-1;
        *digit_-=*Num.digit_;
        *idigit_-=*Num.idigit_;
    } else if(sign_!=Num.sign_){
        if(*digit_<*Num.digit_) sign_*=-1;
        *digit_-=*Num.digit_;
        *idigit_+=*Num.idigit_;
    } else{
        if(*idigit_<*Num.idigit_) isign_*=-1;
        *digit_+=*Num.digit_;
        *idigit_-=*Num.idigit_;
    }
}

template<class Char_T>
void Number<Char_T>::operator-=(const Number& Num){
    *digit_-=*Num.digit_;
    *idigit_-=*Num.idigit_;
}

template<class Char_T>
void Number<Char_T>::operator*=(const Number& Num){
    Digit<Char_T> tmp;

    tmp=(*digit_)*(*Num.digit_)-(*idigit_)*(*Num.idigit_);
    *idigit_=(*digit_)*(*Num.idigit_)+(*idigit_)*(*Num.digit_);
    *digit_=tmp;
}

template<class Char_T>
void Number<Char_T>::operator/=(const Number& Num){
    // *digit_+=*Num.digit_;
    // *idigit_+=*Num.idigit_;
}

template<class Char_T>
void Number<Char_T>::operator^=(const Number& Num){
    ;
}

template<class Char_T>
void Number<Char_T>::operator%=(const Number& Num){
    ;
}

template<class Char_T>
void Number<Char_T>::operator=(const Number& Num){
    
    delete idigit_;
    delete digit_;

    idigit_=new (std::nothrow) Digit<Char_T>;

    *idigit_=*Num.idigit_;
    isize_=Num.isize_;
    isign_=Num.isign_;

    digit_=new (std::nothrow) Digit<Char_T>;

    *digit_=*Num.digit_;
    delim_=Num.delim_;
    size_=Num.size_;
    SEEK__=Num.SEEK__;
    type_=Num.type_;
    sign_=Num.sign_;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator+(const Number& Num) const{
    Number<Char_T> result;
    result=*this;
    result+=Num;
    return result;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator-(const Number& Num) const{
    Number<Char_T> result;
    result=*this;
    result-=Num;
    return result;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator*(const Number& Num) const{
    Number<Char_T> result;
    result=*this;
    result*=Num;
    return result;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator/(const Number& Num) const{
    ;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator^(const Number& Num) const{
    ;
}

template<class Char_T>
Number<Char_T> Number<Char_T>::operator%(const Number& Num) const{
    ;
}

// template<class Char_T>
// Number<Char_T> Number<Char_T>::operator++(const Number& Num) const{
//     ;
// }

// template<class Char_T>
// Number<Char_T> Number<Char_T>::operator--(const Number& Num) const{
//     ;
// }

template<class Char_T>
bool Number<Char_T>::operator==(const Number& Num) const{
    if(*digit_==*Num.digit_ && *idigit_==*Num.idigit_ &&
        sign_==Num.sign_ && isign_==Num.isign_) return true;
    return false;
}

template<class Char_T>
bool Number<Char_T>::operator>=(const Number& Num) const{
    if(((*digit_)*(*digit_)+(*idigit_)*(*idigit_))>=
        ((*Num.digit_)*(*Num.digit_)+(*Num.idigit_)*(*Num.idigit_))) return true;
    return false;
}

template<class Char_T>
bool Number<Char_T>::operator>(const Number& Num) const{
    if(((*digit_)*(*digit_)+(*idigit_)*(*idigit_))>
        ((*Num.digit_)*(*Num.digit_)+(*Num.idigit_)*(*Num.idigit_))) return true;
    return false;
}

template<class Char_T>
bool Number<Char_T>::operator<=(const Number& Num) const{
    if(((*digit_)*(*digit_)+(*idigit_)*(*idigit_))<=
        ((*Num.digit_)*(*Num.digit_)+(*Num.idigit_)*(*Num.idigit_))) return true;
    return false;
}

template<class Char_T>
bool Number<Char_T>::operator<(const Number& Num) const{
    if(((*digit_)*(*digit_)+(*idigit_)*(*idigit_))<
        ((*Num.digit_)*(*Num.digit_)+(*Num.idigit_)*(*Num.idigit_))) return true;
    return false;
}

template<class Char_T>
bool Number<Char_T>::operator!=(const Number& Num) const{
    if(!(*this==Num)) return true;
    return false;
}
