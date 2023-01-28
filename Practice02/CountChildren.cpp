//有N个小孩围成一圈，给他们从1开始依次编号，现指定从第W个开始报数，报到第S个时，该小孩出列，然后从下一个小孩开始报数，
// 仍是报到第S个出列，如此重复下去，直到所有的小孩都出列（总人数不足S个时将循环报数），求小孩出列的顺序。
//输入
//第一行输入小孩的人数N（maxn≤64）。
//接下来每行输入一个小孩的名字(人名不超过15个字符) 。
//最后一行输入W, S (W<maxn)，用逗号“,”间隔。
//输出
//按人名输出小孩按顺序出列的顺序，每行输出一个人名。

//来源：POJ 3750

#include<iostream>
#include<string>
#define maxn 65
using namespace std;

int main() {
    int n;
    cin >> n;
    string name[maxn];
    int p[maxn];
    for(int i = 0; i < n; i++) {
        cin >> name[i];
        p[i] = i;
    }
    int w, s;
    char c;
    cin >> w >> c >> s;
    w = (w - 1) % n;    //初始位置
    do {
        w = (w + s - 1) % n;    //出列位置
        cout << name[p[w]] << '\n';
        for(int i = w; i < n - 1; i++) {    //w之后的人编号往前移一位
            p[i] = p[i + 1];
        }
    } while (--n);
    return 0;
}