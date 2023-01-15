//给出两个字符串a和b，定义a*b是它们的串联。
// 例如，如果a="abc"，b="def"，则a*b="abcdef"。
// 如果把串联视为相乘，非负整数指数则定义为：a^0=""（空串），而a^(n+1)=a*(a^n)。
//输入
//每个测试用例是在一行中给出一个可打印字符的字符串s。s的长度将至少为1，并且不会超过1000000（一百万）个字符。在最后一个测试用例后面，给出包含句点的一行。
//输出
//对于每个s，请输出大的n，使得对某个字符串a，s=a^n。
//提示
//本题海量输入，为避免超时，请使用scanf替代cin。

//来源：POJ 2406

#include<iostream>
#include<cstring>
using namespace std;

typedef long long ll;
char s[1001000];    //输入字符串
int mod = 10009;
int len, k = 131;
ll myHash[1001000];   //存储第i个字符为尾的前缀的散列值

ll cal(int x, ll y) {  //计算y的x次方 % mod的结果(将x视为二进制数)
    ll re = 1;
    while (x) {
        if(x & 1) re = (re * y) % mod;  //当前位为1，则累乘当前位的权并取模
        x >>= 1;    //次幂x右移一位
        y = (y * y) % mod;  //计算该位的权后取模
    }
    return re;
}

bool check(int x) { //若所有长度为x的子串hash值都相等，则返回ture，否则返回false
    ll cc = cal(x, ll(k));  //计算k的x次方 % mod的值
    for(int i = (x << 1); i <= len; i += x) {   //左移一位相当于x乘2
        if((myHash[i] - (myHash[i - x] * cc) % mod + mod) % mod != myHash[x]) return false;
    }
    return true;
}

int main() {
    while (true) {
        scanf("%s", s + 1); //输入字符串，并以1为起始位置
        len = strlen(s + 1);
        if(len == 1 && s[1] == '.') return 0;   //空串则输出0
        for(int i = 1; i <= len; i++) { //计算每个字符的散列值
            myHash[i] = (myHash[i - 1] * k + s[i]) % mod;   //s[i]即该字符的ASCII码值
        }
        for(int i = 1; i <= len; i++) { //枚举所有可能的子串长度
            if(len % i == 0 && check(i)) {  //找到可划分的子串长度i且所有子串散列值相等
                printf("%d\n", len / i);
                break;
            }
        }
    }
}