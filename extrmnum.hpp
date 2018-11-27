
#pragma once

#include"number.hpp"

typedef std::vector<unsigned> u_vec;
typedef std::vector<char> c_vec;

template<class Double_T, class Char_T>
class Extreme_Number: public Number<Double_T, Char_T>{
    private:
    u_vec* udigit;
    c_vec* cdigit;
    std::string e_presentation;

    void init();

    public:
    Extreme_Number();
    Extreme_Number(int);
    Extreme_Number(const char* _syntax_);
    Extreme_Number& calculate(const char* _syntax_);
    u_vec uget() const;
    c_vec cget() const;
    ~Extreme_Number();
};