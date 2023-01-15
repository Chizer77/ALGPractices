//  问题描述：找到一个符合下述条件的最小数，使这个数各位数连续相乘的结果得到题目所给的数；即，该数的乘法持久性的第一步就得到给定的数。
//  输入
//  每个测试用例一行，给出一个最多可达1000位数字的十进制数。在最后一个测试用例后的一行给出-1。
//  输出
//  对每个测试用例，输出一行，给出一个满足上述条件的整数；或者输出一个语句，说明没有这样的数，格式如样例输出。

//来源：POJ 2325，UVA10527

#include<iostream>
#include <cstring>

using namespace std;

#define N 1010
char str[N], ans[N];    //数串str[], 整商串ans[]

int num[3 * N]; //存储满足条件的整数

int count(int i) {  //计算和返回str[]代表的整数除以i的结果；若能整除则返回1和整商串str[],否则返回0
    int j, mod = 0, k = 0;  //当前余数mod，ans[]的指针k
    char *q;    //商对应的数串
    for(j = 0; str[j] != '\0'; j++) {   //模拟除法过程
        mod = mod * 10 + str[j] - '0';  //计算商的当前位，送入ans[]
        ans[k++] = mod / i + '0';
        mod %= i;   //计算余数
    }
    ans[k] = '\0';
    q = ans;
    while(*q == '0') q++;   //去除前导0
    if(mod != 0) return 0;  //不能整除于i
    for(j = 0; *q != '\0'; j++, q++) {  //将商串赋给str，用于下一次除法
        str[j] = *q;
    }
    str[j] = '\0';
    return 1;
}

int main() {
    int i, j;
    while((cin >> str) && str[0] != '-') {
        j = 0;
        if(str[1] == '\0') {    //若输入的是个位数"x"，则直接输出"1x"
            cout << 1 << str[0] << '\n';
            continue;   //处理下一个用例
        }
        for(i = 9; i > 1; i--) {
            while(count(i)) {//若当前数能被9整除，则i进入num[], 直到当前数无法整除i为止
                num[j++] = i;
            }
        }
        if(strlen(str) > 1) {   //说明没有被除尽
            cout << "There is no such number.\n";
            continue;
        }
        while(j > 0) {  //逆向输出num[],原因：要找到符合条件的最小数
            cout << num[--j];
        }
        cout << '\n';
    }
    return 0;
}