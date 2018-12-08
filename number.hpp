
#include"digit.hpp"

#pragma once

template<class Double_T, class Char_T>
class Number{
    private:
    Digit<Char_T>* idigit_;
    char delim_;
    size_t size_;
    bool SEEK__;

    protected:
    Digit<Char_T>* digit_;

    public:
    Number();
    Number(const std::string& number, const char delim='.');
    Number(const char* number, const char delim='.');
    Number(double number);

    friend void operator<<(std::ostream& out, const Number<double, char>& Num);
    friend void operator>>(std::istream& in, Number<double, char>& Num);
    void operator[](int position) const;
    void operator+=(const Number& Num);
    void operator-=(const Number& Num);
    void operator*=(const Number& Num);
    void operator/=(const Number& Num);
    void operator^=(const Number& Num);
    void operator%=(const Number& Num);
    void operator=(const Number& Num);
    Number operator+(const Number& Num) const;
    Number operator-(const Number& Num) const;
    Number operator*(const Number& Num) const;
    Number operator/(const Number& Num) const;
    Number operator^(const Number& Num) const;
    Number operator%(const Number& Num) const;
    Number operator++() const;
    Number operator--() const;
    bool operator==(const Number& Num) const;
    bool operator>=(const Number& Num) const;
    bool operator>(const Number& Num) const;
    bool operator<=(const Number& Num) const;
    bool operator<(const Number& Num) const;
    bool operator!=(const Number& Num) const;

    ~Number();
};
