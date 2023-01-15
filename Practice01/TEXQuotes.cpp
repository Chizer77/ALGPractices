//输入
//输入由若干行包含偶数个双引号(" )字符的文本组成。输入由EOF字符结束。
//输出
//除了下述情况，输出的文本要和输入的一样：
//每对双引号中的第一个 " 被替换为两个` 字符，并且，每对双引号中的第二个 " 被替换为两个 ' 字符。

//来源：POJ 1488，UVA 272

#include<iostream>
using namespace std;
const char p[][5] = {"``", "''"};

int main() {
    int k = 0;
    char c;
    while ((c = getchar()) != EOF) {
        if(c == '\"') {
            cout << p[k];
            k = !k;
        }
        else putchar(c);
    }
    return 0;
}