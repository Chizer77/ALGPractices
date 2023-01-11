//给出一个次数从8到0的多项式的系数，请以可读的形式将该多项式规范地输出，没有必要的字符就不用输出。
// 例如，给出系数0, 0, 0, 1, 22, -333, 0, 1, 和 -1，输出x^5 + 22x^4 - 333x^3 + x–1。

//规范规则如下：
//1. 多项式的各项按照指数的递减顺序输出；
//2. 次数出现在“^”之后；
//3. 常数项仅输出常数；
//4. 如果所有的项都是以0作为系数，则仅输出常数0；否则仅输出非零系数的项；
//5. 在二元操作符 + 和 - 的两边要有一个空格；
//6. 如果第一个项的系数是正数，在该项前没有符号；如果第一个项的系数是负数，在该项前是减号；例如，-7x^2 + 30x + 66。
//7. 负系数项以被减的非负项的形式出现，（如上所述，第一个项是负系数项时是例外）。例如，不能输出x^2 + -3x，应该输出x^2 - 3x。
//8. 常量1和-1仅在常数项出现。例如，不能输出-1x^3 + 1x^2 + 3x^1–1，应该输出-x^3 + x^2 + 3x–1。

//输入
//输入包含一行或多行的系数，系数间由一个或多个空格分隔开。每行有9个系数，每个系数是绝对值小于1000的整数。
//输出
//输出给出格式化的多项式，每个多项式一行。

#include<iostream>

using namespace std;
#define n 9 //多项式系数
inline int fab(int k) { //返回k的绝对值
    return k < 0 ? -k : k;
}

int main() {
    int a[n];
    while(cin >> a[0]) {    //从高到低输入系数
        for(int i = 1; i < n; i++) {
            cin >> a[i];
        }
        bool first = true; //首项标志
        for(int i = 0; i < n; i++) {
            if(a[i]) {
                if(first) { //处理首项
                    if(a[i] == -1 && i < n - 1) {   //首项系数为-1，且不是常数项
                        cout << '-';
                    }
                    else if(a[i] != 1 || i == n - 1) {  //首项系数不为1，或是常数项
                        cout << a[i];
                    }
                    if(i == n - 2) {   //若指数为1，则不输出指数，指数大于1时，输出指数
                        cout << 'x';
                    }
                    else if(i < n - 1) {
                        cout << "x^" << n - i - 1;
                    }
                    first = false;
                }
                else {  //若是第一个非零系数之后的非零系数，先输出运算符，再输出系数的绝对值
                    cout << ' ' << (a[i] < 0 ? '-' : '+') << ' ';
                    if(fab(a[i]) != 1 || i == n - 1) {  //系数不为1或是常数项则输出系数
                        cout << fab(a[i]);
                    }
                    if(i == n - 2) {    //若指数为1时，则不输出指数，指数大于1时，输出指数
                        cout << 'x';
                    }
                    else if(i < n - 1) {
                        cout << "x^" << n - i - 1;
                    }
                }
            }
        }
        if(first) { //无首项
            cout << 0;
        }
        cout << endl;
    }
    return 0;
}