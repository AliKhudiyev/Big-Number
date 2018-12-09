
#pragma once

#include"digit.hpp"

template<class Char_T=char>
class Number{
    static const char imaginary_number_='i';

    private:
    Digit<Char_T>* idigit_;
    size_t isize_;
    char isign_;

    protected:
    Digit<Char_T>* digit_;
    char delim_;
    size_t size_;
    bool SEEK__;
    std::string type_;
    char sign_;

    void init(const std::string& number, const std::string& inumber="0", const char delim='.');

    public:
    Number(): 
        Number("0") {}
    Number(const std::string& number, const std::string& inumber="0", const char delim='.'): 
        idigit_(nullptr), digit_(nullptr), delim_(delim), 
        SEEK__(SEEK_BEG), type_("Real Number") 
    {
        init(number, inumber, delim);
    }
    Number(const char* number, const char* inumber, const char delim='.');
    Number(double number, double inumber=0.0);

    /*
    * Getters
    */

    size_t isize() const;
    virtual char delimeter() const;
    virtual size_t size() const;
    virtual bool seek() const;
    virtual const std::string type() const;
    virtual const std::string info() const;

    /*
    * Overloaded operators
    */

    friend std::ostream& operator<<(std::ostream& out, const Number<char>& Num);
    friend std::istream& operator>>(std::istream& in, Number<char>& Num);
    virtual Char_T operator[](int position) const;
    virtual void operator+=(const Number& Num);
    virtual void operator-=(const Number& Num);
    virtual void operator*=(const Number& Num);
    virtual void operator/=(const Number& Num);
    virtual void operator^=(const Number& Num);
    virtual void operator%=(const Number& Num);
    virtual void operator=(const Number& Num);
    /*const */Number operator+(const Number& Num) const;
    /*const */Number operator-(const Number& Num) const;
    /*const */Number operator*(const Number& Num) const;
    /*const */Number operator/(const Number& Num) const;
    /*const */Number operator^(const Number& Num) const;
    /*const */Number operator%(const Number& Num) const;
    /*const */Number operator++() const;
    /*const */Number operator--() const;
    virtual bool operator==(const Number& Num) const;
    virtual bool operator>=(const Number& Num) const;
    virtual bool operator>(const Number& Num) const;
    virtual bool operator<=(const Number& Num) const;
    virtual bool operator<(const Number& Num) const;
    virtual bool operator!=(const Number& Num) const;

    ~Number(){
        delete idigit_;
        delete digit_;
    }
};

#include"number.cpp"
