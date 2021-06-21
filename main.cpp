#include <iostream>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;
long total_count(double delay_time,double operating_delay);
string hexadecimal(long num);
void display();
void display2(string Count);
int main() {
    std::cout << std::fixed << std::setprecision(8);
    double crystal_freq;
    double time_delay;
    cout<<"Enter crytal freq(KHZ) & Time delay(sec)";
    cin>>crystal_freq>>time_delay;
    cout<<"Given,crytal frequency = "<<crystal_freq<<endl;
    cout<<"      Optimal frequency: "<<crystal_freq<<"/2"<<" = "<<double (crystal_freq/2)<<endl;
    cout<<"      Tdelay = "<<time_delay<<" sec"<<endl;
    cout<<"T = 1/f = 1/("<<double (crystal_freq/2)<<"*10^6 Hz)= ";
    double operating_freq = (1.0/ (crystal_freq/2) ) * pow(10,-6);
    cout<<operating_freq<<" sec"<<endl;
    display();
    long count=total_count(time_delay,operating_freq);
    cout<<"==> Count = "<<hexadecimal(count)<<" H"<<endl;
    display2(hexadecimal(count));
    return 0;
}

long total_count(double delay_time,double operating_delay){
    cout<<"==> "<<delay_time<<" = 17* "<<operating_delay<<" + 24* "<<operating_delay<<"*count"<<endl;
    cout<<"==> Count = ( "<<delay_time<<" - 17* "<<operating_delay<<") / 24* "<<operating_delay<<endl;
    cout<<"==> Count = "<<double(delay_time - 17*operating_delay)<<" / "<<double (24*operating_delay)<<endl;
    cout<<"==> Count = "<<double((delay_time - 17*operating_delay)/(24*operating_delay))<<endl;
    long res =ceil( (delay_time - 17*operating_delay)/(24*operating_delay) );
    cout<<"==> Count = ("<<res<<")"<<endl;
    return res;
}


string hexadecimal(long num){
    if (num >= 0 && num <=9) {
        return  to_string(num);
    }
    else if(num >= 10 && num <16){
        string firstLetter(1,'A' + num - 10);
        return firstLetter;
    }
    else {
        unsigned long long rem = num % 16;
        return hexadecimal(num / 16)+hexadecimal(rem) ;

    }
}
 void display(){
     cout<<"-----------------------------------------------------"<<endl;
     cout<<"Using 16 bit register"<<endl;
     cout<<"-----------------------------------------------------"<<endl;
     cout<<"        Program                                  T states"<<endl;
     cout<<"        -------                                  -------"<<endl;
     cout<<"Delay: LXI B,count                                 10T    "<<endl;
     cout<<"Back:  DCX B                                       6T    "<<endl;
     cout<<"       MOV A,B                                     4T    "<<endl;
     cout<<"       ORA C                                       4T    "<<endl;
     cout<<"       JNZ Back                                  True | False "<<endl;
     cout<<"                                                   10T | 7T   "<<endl;
     cout<<"       RET                                        10T"<<endl;
     cout<<"-----------------------------------------------------"<<endl;
     cout<<" Calculating the value of count"<<endl;
     cout<<"-----------------------------------------------------"<<endl;
     cout<<"   Tdelay = 20*T + 24*T*count - 3T"<<endl;
     cout<<"==>Tdelay = 17*T + 24*T*count "<<endl;
}

void display2(string Count){
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Final program:"<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Delay: LXI B," <<Count                                <<endl;
    cout<<"Back:  DCX B                                         "<<endl;
    cout<<"       MOV A,B                                      "<<endl;
    cout<<"       ORA C                                     "<<endl;
    cout<<"       JNZ Back                                  "<<endl;
    cout<<"       RET                                        "<<endl;
    cout<<"-----------------------------------------------------"<<endl;
}