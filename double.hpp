
#pragma once

#include"number.hpp"

template<class Char_T>
class Double: public Number<Char_T>{
    private:
    ;

    public:
    Double();
    Double(const std::string& number, const char delim='.');
    Number(const char* number, const char delim='.');
    Double(double number);

    char delimeter() const;
    size_t size() const;
    bool SEEK() const;
    const std::string type() const;

    ~Double();
};
