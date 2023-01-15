//本题的目标是计算如下的布尔表达式：
//表达式： ( V | V ) & F & ( F | V )
//其中‘V’表示True，‘F’表示False。表达式可以包含下述的运算符：‘!’表示not，‘&’表示and，‘|’表示 or，并允许使用括号。
//为了执行表达式的运算，要考虑运算符的优先级：not的优先级最高，or的优先级最低。程序要产生V 或 F，是输入文件中每个表达式的结果。

//输入
//一个表达式不超过100个符号。符号间可以用任意个空格分开，或者根本没有空格，所以表达式总的长度，也就是字符的个数，是未知的。
//在输入文件中表达式的个数是一个变量，不大于20。每个表达式在一行中，如下所示。
//输出
//对测试用例中的每个表达式，输出“Expression”，后面跟着序列号，“:”，然后是相应的测试表达式的结果值。每个测试表达式一行。

//来源：POJ 2106

#include<iostream>
using namespace std;
const int maxn = 100 + 10;
int val[maxn], vtop;    // val为数值栈，vtop为栈顶指针
int op[maxn], otop;     // op为运算符栈，otop为栈顶指针

//按优先级给运算符赋值,其中 ( = 0, | = 1, & = 2, ! = 3, ) = 4，数值越高优先级越高，其中)由于优先级最高可不进行转换
void insert(int b) {    //根据op栈顶的'!'对数值b进行运算，并入val栈
    while (otop && op[otop - 1] == 3) {
        b = !b;
        --otop;
    }
    val[vtop++] = b;
}

void cal() {    //双目运算
    int b = val[--vtop];
    int a = val[--vtop];
    int opr = op[--otop];
    int c = a & b;  // 默认为&运算
    if(opr == 1) c = a | b;
    insert(c);  // 将运算结果入val栈,顺便清除！运算
}

int main() {
    int loop = 0;   //测试序号
    char c;
    while ((c = getchar()) != EOF) {
        vtop = otop = 0;
        do {
            if(c == '(') op[otop++] = 0;
            else if(c == ')') {
                while (otop && op[otop - 1] != 0) cal();
                --otop; // ( 出栈
                insert(val[--vtop]);    //(去除后再进行！去除并插入val栈
            }
            else if(c == '!') op[otop++] = 3;
            else if(c == '&') { //将op栈顶的&和！弹出运算，再将2压入运算符栈
                while (otop && op[otop - 1] >= 2) cal();
                op[otop++] = 2;
            }
            else if(c == '|') { //将op栈顶的&，！和|弹出运算，再将1压入运算符栈
                while (otop && op[otop - 1] >= 1) cal();
                op[otop++] = 1;
            }
            else if(c == 'V' | c == 'F') insert(c == 'V' ? 1 : 0);
        } while ((c = getchar()) != '\n' && c != EOF);  //c在同一运算式中，且不是结尾
        while (otop) cal(); //若还未运算完则继续运算
        cout << "Expression " << ++loop << ": " << (val[0] ? 'V' : 'F') << '\n';
    }
}
