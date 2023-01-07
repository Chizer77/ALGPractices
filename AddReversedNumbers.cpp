//  输入
//  输入由N个测试用例组成。输入的第一行仅给出正整数N，然后给出若干测试用例。
//  每个测试用例一行，由2个由空格分开的正整数组成。这是要相加的要被反向的数。
//  输出
//  对每个测试用例，输出一行，仅包含一个整数，将两个反向数进行求和，之后再反向。在输出时把前导0略去。
//  本题设定没有0因为反向而丢失

#include<iostream>
#include<cstring>
using namespace std;
int Num[3][1000];   //  Num[0][0]存储被加数长度，Num[0][1...Num[0][0]]储存被加数；Num[1][0]存储加数长度，Num[1][1...Num[1][0]]储存加数
                    //  ，Num[2][0]储存和数长度，Num[2][1...Num[2][0]]储存和数

void Read(int Ord) {    //Ord = 0表示被加数，Ord = 1表示加数
    int flag = 0;
    string temp;
    cin >> temp;    //输入数
    for(int i = temp.length() - 1; i >= 0; i--) {
        if(temp[i] > '0') flag = 1; //尾部的零均不保存
        if(flag) {
            Num[Ord][++Num[Ord][0]] = temp[i] - '0';    //Num[Ord][0]表示该数长度，初始为0
        }
    }
    for(int i = Num[Ord][0], j = 1; i > j; i--, j++) {  //将数反向存储
        flag = Num[Ord][i]; //交换两数
        Num[Ord][i] = Num[Ord][j];
        Num[Ord][j] = flag;
    }
}

//将两数相加
void Add() {
    Num[2][0] = max(Num[0][0], Num[1][0]);  //选择加数与被加数之间更长的数长度
    for(int i = 1; i <= Num[2][0]; ++i) {   //两数逐位相加
        Num[2][i] = Num[0][i] + Num[1][i];
    }
    for(int i = 1; i <= Num[2][0]; ++i) {   //逐位进位处理
        Num[2][i+1] += Num[2][i] / 10;
        Num[2][i] %= 10;
    }
    if(Num[2][Num[2][0] + 1] > 0) Num[2][0]++;  //若有溢出位则长度加一
}

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        memset(Num, 0, sizeof(Num));    //每次初始化数组
        Read(0);
        Read(1);
        Add();
        //反向输出，并去除前导零
        int flag = 0;
        for(int i = 1; i <= Num[2][0]; i++) {
            if(Num[2][i] > 0) flag = 1;
            if(flag) cout << Num[2][i];
        }
        cout << endl;
    }
}