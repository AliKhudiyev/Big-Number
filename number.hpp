
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

    public:
    Number(): 
        Number("0") {}
    Number(const std::string& number, const std::string& inumber="0", const char delim='.'): 
        idigit_(nullptr), digit_(nullptr), delim_(delim), 
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        init(number, inumber, delim);
    }
    Number(const char* number, const char* inumber, const char delim='.'): 
        idigit_(nullptr), digit_(nullptr), delim_(delim),
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        std::string num, inum;
        for(size_t i=0;i<strlen(number);++i) num+=number[i];
        for(size_t i=0;i<strlen(inumber);++i) inum+=inumber[i];
        init(num, inum, delim);
    }
    Number(double number, double inumber=0.0): 
        idigit_(nullptr), digit_(nullptr), delim_('.'),
        SEEK__(SEEK_BEG), type_("A Number") 
    {
        ;
    }
    Number(long number, long inumber=0);
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
    * Individual operation functions
    */

    Number& post_add(const Number& Num);
    Number& pre_add(const Number& Num);
    Number& post_add(double rnum, double inum=0);
    Number& pre_add(double rnum, double inum=0);
    Number& post_add(long rnum, long inum=0);
    Number& pre_add(long rnum, long inum=0);

    Number& Rpost_add(const std::string& rnum);
    Number& Rpre_add(const std::string& rnum);
    Number& Rpost_add(double rnum);
    Number& Rpre_add(double rnum);
    Number& Rpost_add(long rnum=1);
    Number& Rpre_add(long rnum=1);

    Number& Ipost_add(const std::string& inum);
    Number& Ipre_add(const std::string& inum);
    Number& Ipost_add(double inum);
    Number& Ipre_add(double inum);
    Number& Ipost_add(long inum=1);
    Number& Ipre_add(long inum=1);

    /*
    * Comparison functions
    */

    bool real_equal(const Number& Num) const;
    bool real_nequal(const Number& Num) const;
    bool real_greater(const Number& Num) const;
    bool real_greater_than(const Number& Num) const;
    bool real_less(const Number& Num) const;
    bool real_less_than(const Number& Num) const;

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
