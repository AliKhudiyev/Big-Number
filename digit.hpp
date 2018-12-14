
/*
 * Digit.hpp header file.
 * Generic/Template Digit class to contains the whole digits of any type of number
 * Excluding the imaginary numbers, any decimal digits can be hold
 * This header file contains many of operations which user shouldn't be able to use on his own
 * The limit of digit storage is the number of bytes of the free storage in the user's ram
 * Not too much efficient to hold and work with many and very very big numbers
 * Recommended to hold ~150 digits at once in order to not lose efficiency too much
*/

#include<string>
#include<iostream>

#pragma once

template<class Char_T>
class Number;

template<class Char_T=char>
class Digit{
    private:
    mutable Char_T digit_;
    Digit* next_;
    Digit* prev_;
    
    /*
    * Constructures are private in order to prevent the user
    * to construct an instance of Digit class directly
    * However, having such an instance is constructuble
    * through the frind class which is Number
    */

    Digit(): 
        next_(nullptr), prev_(nullptr) {}
    Digit(int number): 
        Digit(number+0.0) {}
    explicit Digit(const std::string& number, const char delim='.'):
        next_(nullptr), prev_(nullptr) 
    {
        parse_number(number, delim);
    }
    explicit Digit(const char* number, const char delim='.'):
        next_(nullptr), prev_(nullptr) 
    {
        parse_number(number, delim);
    }
    explicit Digit(double number):
        next_(nullptr), prev_(nullptr) 
    {
        parse_number(number);
    }
    explicit Digit(Digit<Char_T>* prev):
        next_(nullptr), prev_(prev) {}
    explicit Digit(unsigned long nb_digit, unsigned long init_val): 
        next_(nullptr), prev_(nullptr) 
    {
        init_number(nb_digit, init_val);
    }
    explicit Digit(unsigned long nb_digit, char digit, bool reverse): 
        digit_(digit), next_(nullptr), prev_(nullptr) 
    {
        auto it=this;
        for(unsigned long nb=1;nb<nb_digit;++nb){
            it->next_=new (std::nothrow) Digit<Char_T>(it);
            it=it->next_;
            it->digit_=digit;
        }
    }

    void parse_number(const std::string& number, const char delim);     //susp: memory leak
    void parse_number(const char* number, const char delim);
    void parse_number(double number);
    void init_number(unsigned long nb_digit, unsigned char init_val);
    void trim();    //+ no memory leak
    void trim(unsigned beg_, unsigned end_);    //susp: memory leak
    Char_T add_carry(Char_T digit) const;
    Char_T mult_carry(Char_T digit, Char_T carry) const;
    void read(std::ostream& out) const;
    void write(std::istream& in);

    protected:
    /*
    * Setters and Getters
    * For debug purposes these are public for now
    * They can better be either protected or private
    */
    void add_front(Char_T digit);
    void append(Char_T digit);
    void insert(Char_T digit);
    void set(Char_T digit);
    void Set(const std::string& number, const char delim='.');
    unsigned get() const;
    Char_T get_c() const;
    Digit* get_next() const;
    Digit* get_prev() const;

    /*
    * General info
    * ---
    */
    bool is_convertible_to_int();
    bool is_convertible_to_long();
    bool is_convertible_to_llong();
    bool is_convertible_to_float();
    bool is_convertible_to_double();
    bool is_convertible_to_ldouble();

    public:
    friend class Number<Char_T>;

    std::string to_string() const;

    /*
    * Overloaded operators
    */
    friend std::ostream& operator<<(std::ostream& out, const Digit<char>& Dgt);   //+
    friend std::istream& operator>>(std::istream& in, Digit<char>& Dgt);          //+
    unsigned operator[](int position) const;  //+
    void operator=(const Digit& Dgt);     //susp: memory leak
    void operator+=(const Digit& Dgt);    //+ no memory leak
    void operator-=(const Digit& Dgt);    //+ no memory leak
    void operator*=(const Digit& Dgt);    //+ no memory leak
    void operator/=(const Digit& Dgt);    //-
    void operator^=(const Digit& Dgt);    //-
    void operator%=(const Digit& Dgt);    //+ no memory leak
    const Digit operator+(const Digit& Dgt) const;       //+ no memory leak
    Digit operator-(const Digit& Dgt) const;   //+ no memory leak
    Digit operator*(const Digit& Dgt) const;   //+ no memory leak
    Digit operator/(const Digit& Dgt) const;   //-
    Digit operator^(const Digit& Dgt) const;   //-
    Digit operator%(const Digit& Dgt) const;   //+ no memory leak
    bool operator<=(const Digit& Dgt) const;    //+ no memory leak
    bool operator<(const Digit& Dgt) const;     //+ no memory leak
    bool operator>=(const Digit& Dgt) const;    //+ no memory leak
    bool operator!=(const Digit& Dgt) const;    //+ no memory leak
    bool operator>(const Digit& Dgt) const;     //+ no memory leak
    bool operator==(const Digit& Dgt) const;    //+ no memory leak

    ~Digit();
};

#include"digit.cpp"
