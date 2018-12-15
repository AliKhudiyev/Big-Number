
#pragma once

#include"digit.hpp"

#define SEEK_BEG true
#define SEEK_ORG false

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
    void init(const char* number, const char* inumber="0", const char delim='.');
    void init(double number, double inumber=0);

    public:
    Number(): 
        Number("0") {}
    Number(const std::string& number, const std::string& inumber="0", const char delim='.'): 
        idigit_(nullptr), digit_(nullptr), delim_(delim), 
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        init(number, inumber, delim);
    }
    Number(const char* number, const char* inumber="0", const char delim='.'): 
        idigit_(nullptr), digit_(nullptr), delim_(delim),
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        init(number, inumber, delim);
    }
    Number(double number, double inumber=0.0): 
        idigit_(nullptr), digit_(nullptr), delim_('.'),
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        init(number, inumber);
    }
    Number(long number, long inumber=0): 
        Number(number+0.0, inumber+0.0) {}
    Number(int number, int inumber=0): 
        Number(number+0.0, inumber+0.0) {}
    explicit Number(unsigned long nb_digit, unsigned long init_val);
    explicit Number(unsigned long nb_digit, char digit, bool reverse);

    /*
    * Setters
    */

    void seek(bool SEEK);

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
    * Comparison functions
    */

    bool real_equal(const Number& Num) const;
    bool real_nequal(const Number& Num) const;
    bool real_greater(const Number& Num) const;
    bool real_greater_equal(const Number& Num) const;
    bool real_less(const Number& Num) const;
    bool real_less_equal(const Number& Num) const;

    bool img_equal(const Number& Num) const;
    bool img_nequal(const Number& Num) const;
    bool img_greater(const Number& Num) const;
    bool img_greater_equal(const Number& Num) const;
    bool img_less(const Number& Num) const;
    bool img_less_equal(const Number& Num) const;

    /*
    * Overloaded operators
    */

    friend std::ostream& operator<<(std::ostream& out, const Number<char>& Num);
    friend std::istream& operator>>(std::istream& in, Number<char>& Num);
    Char_T operator[](int position) const;
    Number<Char_T>& operator+=(const Number& Num);
    Number<Char_T>& operator-=(const Number& Num);
    Number<Char_T>& operator*=(const Number& Num);
    Number<Char_T>& operator/=(const Number& Num);
    Number<Char_T>& operator^=(const Number& Num);
    Number<Char_T>& operator%=(const Number& Num);
    virtual void operator=(const Number& Num);
    const Number operator+(const Number& Num) const;
    const Number operator-(const Number& Num) const;
    const Number operator*(const Number& Num) const;
    const Number operator/(const Number& Num) const;
    const Number operator^(const Number& Num) const;
    const Number operator%(const Number& Num) const;
    Number& operator++();
    Number& operator--();
    virtual bool operator==(const Number& Num) const;
    virtual bool operator>=(const Number& Num) const;
    virtual bool operator>(const Number& Num) const;
    virtual bool operator<=(const Number& Num) const;
    virtual bool operator<(const Number& Num) const;
    virtual bool operator!=(const Number& Num) const;

    virtual ~Number(){
        delete idigit_;
        delete digit_;
    }
};

#include"number.cpp"
