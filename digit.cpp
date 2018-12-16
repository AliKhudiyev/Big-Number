#include"exception.hpp"
#include<sstream>
#include<vector>
#include<unistd.h>
#include<cstring>

#ifndef DGTCPP
#define DGTCPP
#include"digit.hpp"

template<class Char_T>
void Digit<Char_T>::parse_number(const std::string& number, const char delim){
    auto current=this;
    // if number already exists delete all of its digits
    // except the first one
    delete current->next_;
    current->next_=nullptr;
    // temporary values
    // tmp - to hold a digit at a time temporarily
    // is_delimeter - to indicate if there is a delimeter in the number string
    // pass - to indicate if the number string consists of only 0's
    Char_T tmp;
    bool is_delimeter=false;
    bool pass=true;
    // digit parser
    for(const auto& digit: number){
        if(!is_delimeter && digit=='0' && current->prev_==nullptr){ continue; }
        else if(pass){ pass=false; }
        tmp=digit-'0';
        if(!is_delimeter && tmp=='.'-48) is_delimeter=true;
        if(current->prev_==nullptr && is_delimeter){
            current->digit_=0;
            current->next_=new (std::nothrow) Digit<Char_T>(current);
            if(current->next_==nullptr){ exit(1); }
            current=current->next_;
        }
        current->digit_=tmp;
        current->next_=new (std::nothrow) Digit<Char_T>(current);
        if(current->next_==nullptr){ exit(1); }
        current=current->next_;
    }
    if(pass){
        current->digit_=0;
        current->next_=new (std::nothrow) Digit<Char_T>(current);
        if(current->next_==nullptr){ exit(1); }
        current=current->next_;
    }
    if(!is_delimeter){
        current->digit_='.'-'0';
        current->next_=new (std::nothrow) Digit<Char_T>(current);
        if(current->next_==nullptr){ exit(1); }
        current=current->next_;
    }
    current->digit_=0;
    for(current;current->prev_->digit_==0;){
        current=current->prev_;
        delete current->next_;
        current->next_=nullptr;
    }
}

template<class Char_T>
void Digit<Char_T>::parse_number(const char* number, const char delim){
    std::string s_number;
    for(size_t i=0;i<strlen(number);++i){
        s_number+=number[i];
    }
    parse_number(s_number,delim);
}

template<class Char_T>
void Digit<Char_T>::parse_number(double number){
    std::string s_number=std::to_string(number);
    parse_number(s_number,'.');
}

template<class Char_T>
void Digit<Char_T>::init_number(unsigned long nb_digit, unsigned char init_val){
    std::string number(nb_digit, init_val%10+'0');
    parse_number(number,'.');
}

template<class Char_T>
void Digit<Char_T>::trim(){
    auto it=this;
    auto cit=this;
    unsigned cnt=0;
    
    for(it;it->digit_==0;it=it->next_, ++cnt);
    if(cnt==1 && it->digit_=='.'-48) cnt=0;
    if(cnt!=0){
        for(cit, it;cit && it;cit=cit->next_, it=it->next_){
            cit->digit_=it->digit_;
        }
        it=cit->prev_;
    } else{
        for(it=this;it->next_;it=it->next_);
    }
    for(it;it->digit_==0;it=it->prev_);
    delete it->next_->next_;
    it->next_->next_=nullptr;
}

template<class Char_T>
void Digit<Char_T>::trim(unsigned beg_, unsigned end_){
    auto it=this;
    auto cit=this;
    for(unsigned i=0;i<beg_;++i, cit=cit->next_);
    for(unsigned i=beg_;i<end_;++i, it=it->next_, cit=cit->next_){
        it->digit_=cit->digit_;
    }   it=nullptr;
}

template<class Char_T>
Char_T Digit<Char_T>::add_carry(Char_T digit) const{
    return digit_+digit>9? 1 : 0 ;
}

template<class Char_T>
Char_T Digit<Char_T>::mult_carry(Char_T digit, Char_T carry) const{
    return (digit_*digit+carry)>9? (digit_*digit+carry)/10 : 0 ;
}

template<class Char_T>
std::ostream& Digit<Char_T>::read(std::ostream& out, long prec) const{
    bool pass=false;
    for(auto it=this;it;it=it->next_){
        if(prec>=0 && (pass || it->digit_+48=='.')){
            if(!pass){
                if(prec==1) prec+=2;
                else prec+=1;
            }
            pass=true;
            --prec;
        }
        if(pass && prec==0) break;
        out<<static_cast<char>(it->digit_+'0');
    }
    return out;
}

template<class Char_T>
std::istream& Digit<Char_T>::write(std::istream& in){
    std::string number;
    in>>number;
    Set(number);
    return in;
}

/*
* Setters and Getters
*/

template<class Char_T>
void Digit<Char_T>::add_front(Char_T digit){
    auto it=this;
    for(it;it->prev_;it=it->prev_);
    it->prev_=new (std::nothrow) Digit<Char_T>;
    it->prev_->next_=it;
    it->prev_->digit_=digit;
}

template<class Char_T>
void Digit<Char_T>::append(Char_T digit){
    auto it=this;
    for(it;it->next_;it=it->next_);
    // std::cout<<"Appending "<<(int)digit<<" after the digit "<<(char)(it->digit_+48)<<'\n';
    it->next_=new (std::nothrow) Digit(it);
    it->next_->digit_=digit;
    // std::cout<<"Appended successfully!\n";
}

template<class Char_T>
void Digit<Char_T>::insert(Char_T digit){
    ;
}

template<class Char_T>
void Digit<Char_T>::set(Char_T digit){
    digit_=digit;
}

template<class Char_T>
void Digit<Char_T>::Set(const std::string& number, const char delim){
    parse_number(number,delim);
}

template<class Char_T>
unsigned Digit<Char_T>::get() const{
    return digit_;
}

template<class Char_T>
Char_T Digit<Char_T>::get_c() const{
    return digit_;
}

template<class Char_T>
Digit<Char_T>* Digit<Char_T>::get_next() const{
    return next_;
}

template<class Char_T>
Digit<Char_T>* Digit<Char_T>::get_prev() const{
    return prev_;
}

template<class Char_T>
std::string Digit<Char_T>::to_string() const{
    std::string number;
    auto it=this;
    for(it;it;it=it->next_){
        number+=static_cast<char>(it->digit_+48);
    }
    return number;
}

/*
* Overloaded operators
*/

std::ostream& operator<<(std::ostream& out, const Digit<char>& Dgt){
    return Dgt.read(out);
}

std::istream& operator>>(std::istream& in, Digit<char>& Dgt){
    return Dgt.write(in);
}

template<class Char_T>
unsigned Digit<Char_T>::operator[](int position) const{
    unsigned digit=0;
    int pos=0;
    /*
    if(SEEK__){
        if(position<0){
            throw Exception("Negative position from SEEK_BEG!");
        } else{
            for(auto it=this;it->next_;it=it->next_, ++pos){
                if(position==pos){
                    digit=it->digit_;
                    break;
                }
            }
            if(position>pos){
                throw Exception("Out of up boundary position from SEEK_BEG!");
            }
        }
    } else{
        auto it=this;
        for(it;static_cast<unsigned>(it->digit_)>=0 && 
            static_cast<unsigned>(it->digit_)<=9;it=it->next_);
        if(position>=0){
            for(pos=-1;pos!=position && it->next_;++pos, it=it->next_);
        } else{
            for(pos=0;pos!=position && it->prev_;--pos, it=it->prev_);
        }
        if(position!=pos){
            throw Exception("Out of boundary postions from SEEK_ORG!");
        } else digit=it->digit_;
    }
    */
    return digit;
}

template<class Char_T>void Digit<Char_T>::operator=(const Digit& Dgt){
    std::string digits;
    for(auto num=&Dgt;num;num=num->next_){
        digits+=num->digit_+48;
    }
    Set(digits);
}

template<class Char_T>void Digit<Char_T>::operator+=(const Digit& Dgt){
    *this=*this+Dgt;
}

template<class Char_T>void Digit<Char_T>::operator-=(const Digit& Dgt){
    *this=*this-Dgt;
}

template<class Char_T>void Digit<Char_T>::operator*=(const Digit& Dgt){
    Digit<Char_T> result(0);
    Digit<Char_T> number;
    Char_T tmp, carry=0;
    unsigned cnt=1, comma_cnt1=0, comma_cnt2=0;

    number=Dgt;

    auto res=this;
    auto num=&number;

    // std::cout<<"Number : "<<*num<<'\n';
    // std::cout<<"*Res : "<<*res<<'\n';

    for(res;res->next_;res=res->next_, ++cnt){
        if(comma_cnt1 || res->digit_=='.'-48) ++comma_cnt1;
    }
    for(num;num->next_;num=num->next_){
        if(comma_cnt2 || num->digit_=='.'-48) ++comma_cnt2;
    }

    unsigned t0=0;
    for(auto cnum=num;cnum;cnum=cnum->prev_){
        // std::cout<<"king cnum value : "<<(int)cnum->digit_<<'\n';
        if(cnum->digit_=='.'-48){ /*std::cout<<"=====CONT, 1\n";*/ continue; }
        Digit<Char_T> temporary(cnt,0,true);
        auto temp=&temporary;
        // std::cout<<"Temporary : "<<*temp<<'\n';
        for(temp;temp->next_;temp=temp->next_);

        for(auto cres=res, ctemp=temp;cres && ctemp;cres=cres->prev_){
            if(cres->digit_=='.'-48){ /*std::cout<<"=====CONT, 2\n";*/ continue; }
            
            // std::cout<<"\ncres->digit : "<<(int)cres->digit_<<", ";
            // std::cout<<"cnum->digit : "<<(int)cnum->digit_<<"\n-->\n";

            tmp=cnum->digit_*cres->digit_+carry;
            carry=0;
            if(tmp>9){
                carry=(tmp-tmp%10)/10;
                tmp%=10;
            }
            ctemp->digit_=tmp;
            // std::cout<<"current ctemp digit : "<<(char)(ctemp->digit_+48)<<'\n';
            ctemp=ctemp->prev_;
            if(!cres->prev_){ ctemp->digit_=carry; carry=0; }
        }
        // std::cout<<"current temporary : "<<temporary<<'\n';
        for(unsigned tzero=0;tzero<t0;++tzero){
            temp->prev_->append(0);
        }
        temp->append('.'-48);
        temp->append(0);
        ++t0;
        // std::cout<<"added temporary : "<<temporary<<'\n';
        result+=temporary;
        // std::cout<<"current RESULT : "<<result<<'\n';
    }
    // std::cout<<"comma counter : "<<comma_cnt1+comma_cnt2<<'\n';
    if(result.digit_!=0){
        Digit<Char_T>* pdigit=nullptr;
        unsigned counter=0, total=comma_cnt1+comma_cnt2;
        auto cres=&result;
        res=cres;
        for(res;res->digit_!='.'-48;res=res->next_, ++counter);
        if(counter<=comma_cnt1+comma_cnt2){
            // std::cout<<"if accepted!\n";
            pdigit=new Digit<Char_T>;
            *pdigit=result;
            for(unsigned cnt=counter;cnt<=total;++cnt) pdigit->add_front(0);
            for(;pdigit->prev_;pdigit=pdigit->prev_);
            cres=pdigit;
        
            for(cres;cres->digit_!='.'-48;cres=cres->next_);
            for(unsigned comma_cnt=0;comma_cnt<comma_cnt1+comma_cnt2;++comma_cnt){
                cres->digit_=cres->prev_->digit_;
                cres=cres->prev_;
            }   cres->digit_='.'-48;
        } else{
            for(cres;cres->digit_!='.'-48;cres=cres->next_);
            for(unsigned cnt=0;cnt<total;++cnt){
                cres->digit_=cres->prev_->digit_;
                cres=cres->prev_;
            }   cres->digit_='.'-48;
        }
        for(cres;cres->prev_;cres=cres->prev_);
        result=*cres;
        delete pdigit;
    }
    result.trim();
    *this=result;
}

template<class Char_T>void Digit<Char_T>::operator/=(const Digit& Dgt){
    ;
}

template<class Char_T>void Digit<Char_T>::operator^=(const Digit& Dgt){
    ;
}

template<class Char_T>void Digit<Char_T>::operator%=(const Digit& Dgt){
    *this=*this%Dgt;
}

template<class Char_T>const Digit<Char_T> Digit<Char_T>::operator+(const Digit& Dgt) const{
    // The variable named "result" is the bigger number
    // "result" is the final number or result of the calculation
    Digit<Char_T> result(0);
    Digit<Char_T> smaller_number;
    if(*this>Dgt){
        *result.next_=*this;
        smaller_number=Dgt;
    } else{
        *result.next_=Dgt;
        smaller_number=*this;
    }
    auto res=&result;
    auto num=&smaller_number;
    Char_T carry=0, tmp;

    // These 3 lines of codes are to make sure that
    // There are 2 distinct Digit pointers(it and num) holding
    // The last values of 2 numbers with the same positions
    // Which of one corresponds to the last position of one of 2 numbers
    for(num;num->digit_!='.'-48;num=num->next_);
    for(res;res->digit_!='.'-48;res=res->next_);
    for(num, res;num->next_ && res->next_;num=num->next_, res=res->next_);
    // Actual process of subtracting
    for(auto cnum=num, cres=res;cnum && cres;cnum=cnum->prev_, cres=cres->prev_){
        // iF pointer points to delimeter(. in this case)
        // Then pass the whole process
        if(cnum->digit_=='.'-48) continue;
        // Storing temporary value(tmp), and the 'carry bit'
        tmp=cnum->digit_+cres->digit_+carry;
        // Modification on the value of tmp if needed
        // Then the current digit of the final number or result is equal to tmp
        carry=0;
        if(tmp>9){ tmp-=10; carry=1; }
        cres->digit_=tmp;
        // Copying the first part of the big number to the result with modification(s) if needed
        if(!cnum->prev_ && carry!=0){
            for(cres;cres->prev_;){
                cres=cres->prev_;
                tmp=cres->digit_+carry;
                carry=0;
                if(tmp>9){ tmp-=10; carry=1; }
                cres->digit_=tmp;
            }
        }
        if(!cres->prev_ && carry==1){
            result.digit_=carry;
            break;
        }
    }
    for(auto cnum=num->next_;cnum;cnum=cnum->next_){
        res->append(cnum->digit_);
    }
    // Trimming useless 0's from the front and the back of the final number
    result.trim();

    return result;
}

template<class Char_T>Digit<Char_T> Digit<Char_T>::operator-(const Digit& Dgt) const{
    // The variable named "result" is the bigger number
    // "result" is the final number or result of the calculation
    Digit<Char_T> result(0);
    Digit<Char_T> number;
    if(*this>Dgt){
        number=Dgt;
        result=*this;
    } else{
        number=*this;
        result=Dgt;
    }
    auto num=&number;
    auto res=&result;
    Char_T tmp, carry=0;
    // Reconstructing the numbers to have same number of digits after the point(.)
    for(num;num->digit_!='.'-48;num=num->next_);
    for(res;res->digit_!='.'-48;res=res->next_);
    for(num, res;num->next_ && res->next_;num=num->next_, res=res->next_){
        if(!res->next_->next_ && num->next_->next_) res->append(0);
    }
    // Actual process of subtracting
    for(res;res && num;res=res->prev_, num=num->prev_){
        if(res->digit_=='.'-48) continue;
        tmp=res->digit_-carry-num->digit_;
        carry=0;
        if(tmp<0){
            tmp+=10;
            carry=1;
        }
        res->digit_=tmp;
    }
    for(res;res;res=res->prev_){
        if(carry!=0){
            tmp=res->digit_-carry;
            if(tmp<0) tmp+=10;
            else carry=0;
            res->digit_=tmp;
        } else if(!res->prev_ || carry==0) break;
    }
    // Trimming useless 0's from the front and the back of the final number
    // result.trim();

    return result;
}

template<class Char_T>Digit<Char_T> Digit<Char_T>::operator*(const Digit& Dgt) const{
    Digit<Char_T> result;
    result=*this;

    result*=Dgt;

    return result;
}

template<class Char_T>Digit<Char_T> Digit<Char_T>::operator/(const Digit& Dgt) const{
    ;
}

template<class Char_T>Digit<Char_T> Digit<Char_T>::operator^(const Digit& Dgt) const{
    ;
}

template<class Char_T>Digit<Char_T> Digit<Char_T>::operator%(const Digit& Dgt) const{
    Digit<Char_T>* result=new (std::nothrow) Digit<Char_T>;
    *result=*this;

    for(;*result>=Dgt;*result=(*result)-Dgt);

    return *result;
}

template<class Char_T>
bool Digit<Char_T>::operator<=(const Digit& Dgt) const{
    return !((*this)>Dgt);
}

template<class Char_T>
bool Digit<Char_T>::operator<(const Digit& Dgt) const{
    return !((*this)>=Dgt);
}

template<class Char_T>
bool Digit<Char_T>::operator>=(const Digit& Dgt) const{
    return (*this)>Dgt || (*this)==Dgt;
}

template<class Char_T>
bool Digit<Char_T>::operator!=(const Digit& Dgt) const{
    return !((*this)==Dgt);
}

template<class Char_T>
bool Digit<Char_T>::operator>(const Digit& Dgt) const{
    int is_greater=0;
    auto it=this;
    auto pdig=&Dgt;
    for(it, pdig;it && pdig;it=it->next_, pdig=pdig->next_){
        if(it->digit_+48=='.' && pdig->digit_+48!='.'){
            is_greater=-1;
            break;
        } else if(it->digit_+48!='.' && pdig->digit_+48=='.'){
            is_greater=1;
            break;
        } else if(it->digit_+48=='.' && pdig->digit_+48=='.' && is_greater==0){
            continue;
        } else if(it->digit_+48=='.' && pdig->digit_+48=='.' && is_greater!=0){
            break;
        } else if(is_greater==0){
            if(it->digit_>pdig->digit_) is_greater=1;
            else if(it->digit_==pdig->digit_) is_greater=0;
            else is_greater=-1;
        }
        if((it->next_==nullptr && pdig->next_!=nullptr) ||
            it->next_!=nullptr && pdig->next_==nullptr){
            break;
        }
    }
    return is_greater<=0? false : true ;
}

template<class Char_T>
bool Digit<Char_T>::operator==(const Digit& Dgt) const{
    auto it=this;
    auto pdig=&Dgt;
    for(it, pdig;true;it=it->next_, pdig=pdig->next_){
        if(it==nullptr && pdig==nullptr) break;
        else if(((!it && pdig) || (it && !pdig)) || 
          it->digit_!=pdig->digit_) return false;
    }
    return true;
}

template<class Char_T>
Digit<Char_T>::~Digit(){
    auto it=this->next_;
    if(it){
        auto curr=it;
        delete curr;
        curr=nullptr;
    }
}

#endif
