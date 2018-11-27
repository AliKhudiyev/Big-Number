#include"exception.hpp"
#include<sstream>
#include<vector>
#include<unistd.h>

#ifndef DGTCPP
#define DGTCPP
#include"digit.hpp"

template<class Char_T>
void Digit<Char_T>::parse_number(const std::string& number, const char delim){
    auto current=this;
    Char_T tmp;
    bool is_delimeter=false;
    bool pass=true;
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
        current->next_=nullptr;
    }
}

template<class Char_T>
void Digit<Char_T>::parse_number(const char* number, const char delim){
    //parsing
}

template<class Char_T>
void Digit<Char_T>::parse_number(double number){
    std::ostringstream number_;
    number_<<number;
    //parse_number(number_->str(),'.');
}

template<class Char_T>
void Digit<Char_T>::trim(){
    auto it=this;
    for(it;it->digit_==0 && it->digit_!='.'-48;it=it->next_){}
    auto cit=this;
    if(it!=cit && it->digit_!='.'-48){
        for(auto it1=it;it1;cit=cit->next_, it1=it1->next_){
            cit->digit_=it1->digit_;
        }   cit=nullptr;
    }
    for(it=this;it->next_;it=it->next_);
    for(it;it->digit_==0 && it->digit_!='.'-48;it=it->prev_){
        ;
    }
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
void Digit<Char_T>::seek(bool SEEK_){
    SEEK__=SEEK_;
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

/*
* Overloaded operators
*/

std::ostream& operator<<(std::ostream& out, const Digit<char>& D){
    for(auto it=&D;it;it=it->next_){
        out<<static_cast<char>(it->digit_+'0');
    }
    return out;
}

std::istream& operator>>(std::istream& in, Digit<char>& D){
    std::string number;
    in>>number;
    D.Set(number);
    return in;
}

template<class Char_T>
unsigned Digit<Char_T>::operator[](int position) const{
    unsigned digit;
    int pos=0;
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
    return digit;
}

template<class Char_T>void Digit<Char_T>::operator=(const Digit& D){
    std::string digits;
    for(auto num=&D;num;num=num->next_){
        digits+=num->digit_+48;
    }
    // std::cout<<" Operator = string : "<<digits<<'\n';
    Set(digits);
}

template<class Char_T>void Digit<Char_T>::operator+=(const Digit& D){
    ;
}

template<class Char_T>void Digit<Char_T>::operator-=(const Digit& D){
    ;
}

template<class Char_T>void Digit<Char_T>::operator*=(const Digit& D){
    ;
}

template<class Char_T>void Digit<Char_T>::operator/=(const Digit& D){
    ;
}

template<class Char_T>void Digit<Char_T>::operator^=(const Digit& D){
    ;
}

template<class Char_T>void Digit<Char_T>::operator%=(const Digit& D){
    ;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator+(const Digit& D) const{
    Digit<Char_T>* number=new (std::nothrow) Digit<Char_T>;
    *number=(*this)>D? *this : D ;
    Digit<Char_T>* it=new (std::nothrow) Digit<Char_T>;
    *it=(*this)>D? D : *this ;
    auto num=number;
    Char_T carry=0, tmp;

    for(it;it->digit_!='.'-48;it=it->next_);
    for(num;num->digit_!='.'-48;num=num->next_);
    for(it, num;it->next_ && num->next_;it=it->next_, num=num->next_);
    for(auto cit=it, cnum=num;cit && cnum;cit=cit->prev_, cnum=cnum->prev_){
        if(cnum->digit_=='.'-48) continue;
        tmp=cit->digit_+cnum->digit_+carry;
        carry=cit->add_carry(cnum->digit_+carry);
        if(tmp>9) tmp-=10;
        cnum->digit_=tmp;
        if(!cit->prev_ && carry!=0){
            for(cnum;cnum->prev_;){
                cnum=cnum->prev_;
                tmp=cnum->digit_+carry;
                carry=cnum->add_carry(carry);
                if(tmp>9) tmp-=10;
                cnum->digit_=tmp;
            }
        }
        if((!cit->prev_ || !cnum->prev_) && carry==1){
            cnum->add_front(carry);
            break;
        }
    }
    if(number->prev_) num=number->prev_;
    for(auto cit=it->next_;cit;cit=cit->next_){
        num->append(cit->digit_);
    }
    for(num;num->prev_;num=num->prev_);    number=num;

    return *number;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator-(const Digit& D) const{
    Digit<Char_T>* it=new (std::nothrow) Digit<Char_T>;
    *it=(*this)>D? D : *this ;
    Char_T tmp, carry=0;
    Digit<Char_T>* result=new (std::nothrow) Digit<Char_T>;
    Digit<Char_T>* num=new (std::nothrow) Digit<Char_T>;
    *num=(*this)>D? *this : D ;

    // std::cout<<"it : "<<*it<<"\nnum : "<<*num<<'\n';

    for(it;it->digit_!='.'-48;it=it->next_);
    for(num;num->digit_!='.'-48;num=num->next_);
    for(it,num;it->next_ && num->next_;it=it->next_, num=num->next_);
    // std::cout<<"num addr / "<<num<<", "<<(int)num->digit_<<"\nit /"<<it<<", "<<(int)it->digit_<<'\n';
    for(num;num->next_;num=num->next_){
        it->append(0);
        it=it->next_;
    }
    for(it;it->next_;it=it->next_){
        num->append(0);
        num=num->next_;
    }
    // std::cout<<"num : "<<*num<<", it : "<<*it<<'\n';
    for(it,num;it && num;it=it->prev_, num=num->prev_){
        // std::cout<<"=====BOC=====\n";
        // std::cout<<(char)(num->digit_+48)<<" - "<<(char)(it->digit_+48)<<'\n';
        if(num->digit_=='.'-'0'){
            // std::cout<<"Continue\n";
            // std::cout<<"=====EOC=====\n";
            continue;
        }
        if(num->digit_-carry-it->digit_<0){
            // std::cout<<"carry : 1\n";
            num->digit_=num->digit_+10-carry-it->digit_;
            // std::cout<<"updated digit : "<<(char)(num->digit_+48)<<'\n';
            carry=1;
        } else{
            // std::cout<<"carry : 0\n";
            num->digit_=num->digit_-carry-it->digit_;
            // std::cout<<"updated digit : "<<(char)(num->digit_+48)<<'\n';
            carry=0;
        }
        if(!num->prev_){
            // std::cout<<"num->prev = nullptr\n";
            *result=*num;
            break;
        } else if(!it->prev_){
            // std::cout<<"\tit->prev = nullptr\n";
            // std::cout<<"num is "<<*num<<'\n';
            for(num;num->prev_;){
                num=num->prev_;
                if(carry==1){
                    num->digit_=num->digit_>0? num->digit_-1 : 9 ;
                    if(num->digit_!=9) carry=0;
                }
            }
            *result=*num;
            break;
        }
        // std::cout<<"=====EOC=====\n";
    }

    return *result;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator*(const Digit& D) const{
    //Digit<Char_T>* number=new (std::nothrow) Digit<Char_T>;
    //*number=D;
    Digit<Char_T>* result=new (std::nothrow) Digit<Char_T>;
    auto it=this;
    auto res=result;
    auto num=&D;

    // Digit<Char_T>* result=new (std::nothrow) Digit<Char_T>;
    // auto res=result;
    Char_T carry=0, tmp;
    unsigned point_position=0;
    bool pass=false;

    for(it;it->next_;it=it->next_){
        if(pass || it->digit_=='.'-'0'){
            ++point_position;
            pass=true;
        }
    }   pass=false;
    for(num;num->next_;num=num->next_){
        if(pass || num->digit_=='.'-'0'){
            ++point_position;
            pass=true;
        }
    }
    // std::cout<<"Point position : "<<point_position<<'\n';
    unsigned index=0;
    std::vector<Digit<Char_T>*> Res;

    // for(auto cit=it;cit;cit=cit->prev_){
    //     std::cout<<(char)(cit->digit_+48)<<' ';
    // }   std::cout<<"\n\n";

    for(it;it;it=it->prev_){
        // std::cout<<"=====BOC=====\n";
        if(it->digit_=='.'-48){
            // std::cout<<"CONTINUE\n";
            // std::cout<<"=====EOC=====\n";
            continue;
        }
        Digit<Char_T>* Tmp=new (std::nothrow) Digit<Char_T>;
        Res.push_back(new (std::nothrow) Digit<Char_T>);
        // std::cout<<"New allocated Number / "<<Res[index]<<'\n';
        // std::cout<<"Currently calculating : "<<(char)(it->digit_+48)<<'\n';
        for(auto cnum=num;cnum;cnum=cnum->prev_){
            // std::cout<<"\t * "<<(char)(cnum->digit_+48)<<'\n';
            if(cnum->digit_=='.'-48){
                // std::cout<<"Continue\n";
                continue;
            }
            tmp=it->digit_*cnum->digit_+carry;
            carry=tmp/10;//it->mult_carry(cnum->digit_,carry);
            if(tmp>9) tmp%=10;
            // std::cout<<"tmp : "<<(int)tmp<<", carry : "<<(int)carry<<'\n';
            Res[index]->digit_=tmp;
            // std::cout<<"New front : "<<(char)(Res[index]->digit_+48)<<'\n';
            if(cnum->prev_ || carry){
                // std::cout<<"if accepted\n";
                // if(!cnum->prev_){ std::cout<<"\twith the cnum digit : "<<(char)(cnum->digit_+48)<<'\n'; }
                // Res[index]->prev_=new (std::nothrow) Digit<Char_T>;
                // Res[index]->prev_->next_=Res[index];
                // Res[index]=Res[index]->prev_;
                if(!cnum->prev_){
                    // std::cout<<"\tif accepted with the carry value of "<<(int)carry<<"\n";
                    // std::cout<<"\tRes index prev addr : "<<Res[index]->prev_<<'\n';
                    Res[index]->add_front(carry);
                    Res[index]=Res[index]->prev_;
                    break;
                }
                Res[index]->prev_=new (std::nothrow) Digit<Char_T>;
                Res[index]->prev_->next_=Res[index];
                Res[index]=Res[index]->prev_;
            }
        }
        // std::cout<<"Res["<<index<<"] : "<<*Res[index]<<'\n';
        for(unsigned i=0;i<index;++i){
            // std::cout<<"Appending 0's..\n";
            Res[index]->append(0);
            // std::cout<<"More 0's?\n";
        }
        Res[index]->append('.'-48);
        Res[index]->append(0);
        // std::cout<<"\tCompleted ||| Res["<<index<<"] : "<<*Res[index]<<'\n';
        ++index;
        // std::cout<<"=====EOC===== "<<index<<"\n\n";
        if(!it->prev_){
            // std::cout<<">>>BREAK!\n";
            break;
        }   carry=0;
    }
    // std::cout<<"Came out from for cycle\n";
    *result=(*Res[0])+(*Res[1]);
    // std::cout<<"Last step\n";
    for(unsigned i=2;i<index;++i){
        *result=(*result)+(*Res[i]);
    }
    auto cresult=result;
    for(cresult;cresult->digit_!='.'-48;cresult=cresult->next_);
    for(unsigned pos=0;pos<point_position;++pos){
        cresult->digit_=cresult->prev_->digit_;
        cresult=cresult->prev_;
    }
    cresult->digit_='.'-48;
    result->trim();

    return *result;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator/(const Digit& D) const{
    ;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator^(const Digit& D) const{
    ;
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::fctl(){
    Digit<Char_T>* number=new (std::nothrow) Digit<Char_T>;
    Digit<Char_T> tmp("1");
    Digit<Char_T> one("1");
    *number=*this;
    for(;*this>tmp;tmp=tmp+one){
        *number=*number*(*this-tmp);
    }
}

template<class Char_T>Digit<Char_T>& Digit<Char_T>::operator%(const Digit& D) const{
    Digit<Char_T>* result=new (std::nothrow) Digit<Char_T>;
    *result=*this;

    for(;*result>=D;*result=(*result)-D);

    return *result;
}

template<class Char_T>
bool Digit<Char_T>::operator<=(const Digit& D) const{
    return !((*this)>D);
}

template<class Char_T>
bool Digit<Char_T>::operator<(const Digit& D) const{
    return !((*this)>=D);
}

template<class Char_T>
bool Digit<Char_T>::operator>=(const Digit& D) const{
    return (*this)>D || (*this)==D;
}

template<class Char_T>
bool Digit<Char_T>::operator!=(const Digit& D) const{
    return !((*this)==D);
}

template<class Char_T>
bool Digit<Char_T>::operator>(const Digit& D) const{
    int is_greater=0;
    auto it=this;
    auto pdig=&D;
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
bool Digit<Char_T>::operator==(const Digit& D) const{
    auto it=this;
    auto pdig=&D;
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
