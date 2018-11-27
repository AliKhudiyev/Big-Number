
#include<string>
#include<iostream>

#pragma once

#define Num_T Char_T
#define SEEK_BEG true
#define SEEK_ORG false

template<class Char_T=char>
class Digit{
    private:
    mutable Char_T digit_;
    Digit* next_;
    Digit* prev_;
    bool SEEK__;

    void parse_number(const std::string& number, const char delim);     //susp: memory leak
    void parse_number(const char* number, const char delim);
    void parse_number(double number);
    void trim();    //susp: memory leak
    void trim(unsigned beg_, unsigned end_);    //susp: memory leak
    Char_T add_carry(Char_T digit) const;
    Char_T mult_carry(Char_T digit, Char_T carry) const;

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
    void seek(bool SEEK_);
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
    Digit():
        Digit(.0) {}
    explicit Digit(const std::string& number, const char delim='.'):
        next_(nullptr), prev_(nullptr), SEEK__(SEEK_BEG) 
    {
        parse_number(number, delim);
    }
    // explicit Digit(const char* number, const char delim='.'):
    //     next_(nullptr), prev_(nullptr), SEEK__(SEEK_BEG) 
    // {
    //     parse_number(number, delim);
    // }
    explicit Digit(double number):
        next_(nullptr), prev_(nullptr), SEEK__(SEEK_BEG) 
    {
        parse_number(number);
    }
    Digit(Digit<Char_T>* prev):
        Digit() { prev_=prev; }
    explicit Digit(unsigned long nb_digit, Char_T init_val=0);

    void debug_print(){
        std::cout<<"===Debug Print of Digit===\n";
        for(auto it=this;it;it=it->next_){
            std::cout<<static_cast<char>(it->digit_+'0');
        }
        std::cout<<'\n';
    }

    /*
    * Overloaded operators
    */
    friend std::ostream& operator<<(std::ostream& out, const Digit<char>& D);   //+
    friend std::istream& operator>>(std::istream& in, Digit<char>& D);          //+
    unsigned operator[](int position) const;  //+
    void operator=(const Digit& D);     //susp: memory leak
    void operator+=(const Digit& D);    //-
    void operator-=(const Digit& D);    //-
    void operator*=(const Digit& D);    //-
    void operator/=(const Digit& D);    //-
    void operator^=(const Digit& D);    //-
    void operator%=(const Digit& D);    //-
    Digit& operator+(const Digit& D) const;   //+
    Digit& operator-(const Digit& D) const;   //-
    Digit& operator*(const Digit& D) const;   //needs to be checked
    Digit& operator/(const Digit& D) const;   //-
    Digit& operator^(const Digit& D) const;   //-
    Digit& fctl();                      //+
    Digit& operator%(const Digit& D) const;   //-
    bool operator<=(const Digit& D) const;    //+
    bool operator<(const Digit& D) const;     //+
    bool operator>=(const Digit& D) const;    //+
    bool operator!=(const Digit& D) const;    //+
    bool operator>(const Digit& D) const;     //+
    bool operator==(const Digit& D) const;    //+

    ~Digit();
};

#include"digit.cpp"
