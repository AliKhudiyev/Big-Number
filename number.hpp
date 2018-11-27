
#include"digit.hpp"

#pragma once

template<class Double_T, class Char_T>
class Number{
    private:
    Digit<Char_T>* digit_;
    char delim_;
    size_t size_;

    ;

    public:
    Number();
    Number(const std::string& number, const char delim='.');
    Number(const char* number, const char delim='.');
    Number(double number);

    ~Number();
};
