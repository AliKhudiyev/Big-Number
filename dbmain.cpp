#include<iostream>
#include<fstream>
#include"number.hpp"
#include<stdio.h>

#define _NUMERIC_STRING_
#define MAX_DIGIT_LIMIT 500
#define USUAL_DIGIT_LIMIT 100
#define MIN_DIGIT_LIMIT 1
// #define _INCLUDED_NUMBER_LIBRARY_

#include"numerical.hpp"
// #include"amath.hpp"

const Digit<> PI_(_PI_.substr(0,3000));
const Digit<> E_(_E_.substr(0,3000));
const Digit<> PHI_(_PHI_.substr(0,3000));

using namespace std;

int main(){
    
    const string num1="25134234344564352343293057043987252487521404.58";
    const string num2="25134234344564352343293057043987252487521404,58";
    // const string num="12";

    // Digit<>* dig=new Digit<>(num);
    // Digit<>* cdig=dig;
    
    // cout<<"Dig : "<<*dig<<'\n';
    // cout<<"Copy Dig : "<<*cdig<<'\n';
    // cout<<cdig->get()<<", ";
    // dig->set(7);
    // cout<<cdig->get()<<'\n';

    Digit<> dig1(2), dig2(3), dig3;
    cout<<"Enter a number : ";
    cin>>dig1;
    cout<<"First number : "<<dig1<<"\n";
    cout<<"Enter a number : ";
    cin>>dig2;
    cout<<"Second number : "<<dig2<<"\n";
    // cout<<"Enter a number : ";
    // cin>>dig3;
    // cout<<"Third number : "<<dig3<<"\n";

    // Digit<> dig4=dig1+dig2;//dig1*(dig2+dig3);
    for(unsigned i=0;i<1;++i){
        dig1+=dig2;
        cout<<dig1<<'\n';
    }

    // int opt;
    // cout<<"Enter an operator option: ";
    // cout<<"\n1.<=\n2.<\n3.>=\n4.>";
    // cout<<"\n5.==\n6.!=\n";
    // cin>>opt;
    
    // switch(opt){
    //     case 1:
    //         cout<<dig1<<" <= "<<dig2<<" : "<<(dig1<=dig2)<<'\n';
    //         break;
    //     case 2:
    //         cout<<dig1<<" < "<<dig2<<" : "<<(dig1<dig2)<<'\n';
    //         break;
    //     case 3:
    //         cout<<dig1<<" >= "<<dig2<<" : "<<(dig1>=dig2)<<'\n';
    //         break;
    //     case 4:
    //         cout<<dig1<<" > "<<dig2<<" : "<<(dig1>dig2)<<'\n';
    //         break;
    //     case 5:
    //         cout<<dig1<<" == "<<dig2<<" : "<<(dig1==dig2)<<'\n';
    //         break;
    //     case 6:
    //         cout<<dig1<<" != "<<dig2<<" : "<<(dig1!=dig2)<<'\n';
    //         break;
    //     default: break;
    // }
    // int position;
    // cout<<"\nThe number : "<<dig1<<'\n';
    // cout<<"Do you want to set SEEK_ORG as a default?(1/0) ";
    // cin>>position;
    // if(position){ dig1.seek(SEEK_ORG); }
    // cout<<"Enter a position : ";
    // cin>>position;
    // try{
    //     dig1[position];
    //     cout<<"Position "<<position<<" holds "<<dig1[position]<<'\n';
    // } catch(Exception& e){
    //     cerr<<e.get_error();
    // }

    return 0;
}
