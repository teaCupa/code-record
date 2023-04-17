//
// Created by teagm on 2023/4/14.
//

#include <iostream>
#include <string>
using namespace std;

class MyDate{
private:
    unsigned year,month,day;
public:
    explicit MyDate(const string& s){
        unsigned format;
        char sep;
        // 1/1/1900
        if(s.find_first_of('/')!=string::npos){
            format = 0;
        }
        // January 1, 1900 或 Jan 1, 1900
        else if(s.find_first_of(',')!=string::npos){
            format =1;
            sep = ',';
        }
        // Jan 1 1900
        else {
            format = 1;
            sep =' ';
        }

        switch (format) {
            string::size_type idx;
            string::size_type idx2;
            case 0:
                idx = s.find_first_of('/');
                idx2 = s.find_last_of('/');
                day = stoi(s.substr(0,idx));
                month = stoi(s.substr(idx+1,idx2-idx));
                year = stoi(s.substr(idx2+1));
                break;
            case 1:
                if(s.find("Jan") < s.size()) month = 1;
                else if( s.find("Feb") < s.size() )  month = 2;
                else if( s.find("Mar") < s.size() )  month = 3;
                else if( s.find("Apr") < s.size() )  month = 4;
                else if( s.find("May") < s.size() )  month = 5;
                else if( s.find("Jun") < s.size() )  month = 6;
                else if( s.find("Jul") < s.size() )  month = 7;
                else if( s.find("Aug") < s.size() )  month = 8;
                else if( s.find("Sep") < s.size() )  month = 9;
                else if( s.find("Oct") < s.size() )  month =10;
                else if( s.find("Nov") < s.size() )  month =11;
                else if( s.find("Dec") < s.size() )  month =12;

                string::size_type i=s.find_first_of("123456789");

                if(sep == ','){
                    idx = s.find_first_of(',');
                }else{   // Jan  1 1900   以1作为' '的查找起始点
                    idx=s.find_first_of(' ',i+1);
                }
                day = stoi(s.substr(i,idx-i));
                year = stoi(s.substr(idx+1));
        }
    }

    void print() {
        cout << "day: " << day << ", "
             << "month: " << month << ", "
             << "year: " << year << endl;
    }
};

int main(){
    /// 对于下面3种日期格式，使用format和sep两个变量进行分类
//    MyDate date("1/1/1900");     //format=0
//    MyDate date("January 1 , 1900");  //format=1,sep=','
    MyDate date("January  1  1900"); //format=1,sep=' '
    date.print();
}

