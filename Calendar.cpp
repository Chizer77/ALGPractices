//输入包含若干行，每行包含一个正整数，表示2000年1月1日后的天数。输入最后一行是−1, 程序不必处理。可以假设输出的年份不会超过9999。
//对每个测试用例，输出一行，该行给出对应的日期和星期几。格式为“YYYY-MM-DD DayOfWeek”, 
//其中 “DayOfWeek”必须是下面中的一个：“Sunday”，“Monday”，“Tuesday”，“Wednesday”，“Thursday”，“Friday”或“Saturday”。
//2000年1月1日是星期六

#include<iostream>
#include<iomanip>
using namespace std;
const char wstr[][20] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

//计算year年的天数
int DayOfYear(int year) {
    if(year % 100 == 0)
        return year % 400 == 0 ? 366 : 365;
    return year % 4 == 0 ? 366 : 365;
}

//计算month月在year年的天数
int DayOfMonth(int month, int year) {
    if(month == 2) 
        return DayOfYear(year) == 366 ? 29 : 28;
    int d;
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: d = 31;break;
        default:
        d = 30;
    }
    return d;
}

int main() {
    int n;
    cin >> n;
    while(n >= 0) {
        int year, month, day, week;
        week = n % 7;   //星期数
        year = 2000;
        month = 1;
        day = 1;
        while(n) {
            if(n >= DayOfYear(year)) {   //枚举到指定年份
                n -= DayOfYear(year);
                year++;
            }
            else if (n >= DayOfMonth(month, year)) {    //再枚举到指定月份
                n -= DayOfMonth(month, year);
                ++month;
            }
            else {  //最后剩余天数
                day += n;
                n = 0;
            }
        }
        cout.fill('0');
        cout << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day << ' ' << wstr[week] << '\n';
        cin >> n;
    }
}