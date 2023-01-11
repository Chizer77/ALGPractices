//给出一个DNA碱基序列的集合，确定在所有序列中都出现的最长的碱基序列。
//输入
//输入的第一行给出了整数n，表示测试用例的数目。每个测试用例由下述两部分组成：
//一个正整数m (2≤m≤10) ，给出该测试用例中碱基序列的数目。
//m行，每行给出一个60碱基的碱基序列。
//输出
//对于输入的每个测试用例的所有的碱基序列，输出最长的相同的碱基子序列。
// 如果最长的相同的碱基子序列的长度小于3，则输出“no significant commonalities” 来代替碱基子序列。
// 如果相同最长长度的子序列有多个，则仅输出按字母排序的第一个。

#include<iostream>
#include<cstring>
using namespace std;

const int maxm = 10 + 5;    //碱基序列数目上限
const int maxs = 60 + 5;    //碱基序列串长上限

int main() {
    int loop;
    cin >> loop;
    while (loop--) {
        int m;
        char p[maxm][maxs];
        cin >> m;
        for(int i = 0; i < m; ++i) cin >> p[i];
        int len = 0;    //最长子串长度
        char ans[maxs]; //最长子串
        for(int i = 0; i < strlen(p[0]); i++) { //枚举子串起始位置
            for(int j = i + 2; j < strlen(p[0]); j++) { //枚举子串结束位置,i+2原因是最小子序列长度因大于3
                char s[maxs];
                strncpy(s, p[0] + i, j - i + 1);
                s[j - i + 1] = '\0';
                bool ok = true;
                for(int k = 1; ok && k < m; k++) {  //确定s是否为p[1]...p[m]的公共子串
                    if(strstr(p[k], s) == NULL) ok = false;
                }
                if(ok && (j - i + 1 > len || j - i + 1 == len && strcmp(ans, s) > 0)) { //s比ans串更长，或虽s与ans同长但按字母排序s的子串更靠前，则将s赋值给ans
                    len = j - i + 1;
                    strcpy(ans, s);
                }
            }
        }
        if(len < 3) cout << "no significant commonalities\n";
        else cout << ans << '\n';
    }
    return 0;
}