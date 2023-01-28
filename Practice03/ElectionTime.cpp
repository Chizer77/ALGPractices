//在推翻了暴虐的农夫John的统治之后，奶牛们要进行他们的第一次选举，Bessie是N（1 ≤maxn≤ 50,000）头竞选总统的奶牛之一。
// 在选举正式开始之前，Bessie想知道谁最有可能赢得选举。
//选举分两轮进行。在第一轮中，得票最多的K头奶牛（1 ≤K≤maxn）进入第二轮。在第二轮选举中，得票最多的奶牛当选总统。
//本题给出在第一轮中预期奶牛i获得Ai票（1 ≤Ai≤ 1,000,000,000），在第二轮获得Bi票（1 ≤Bi≤ 1,000,000,000）（如果它成功的话），
// 请您确定哪一头奶牛有望赢得选举。幸运的是，在Ai列表中没有一张选票会出现两次；同样地，在Bi列表中也没有一张选票会出现两次
//输入
//第1行，两个空格分隔的整数N和K；
//第2..maxn+1行：第i+1行包含两个空格分隔的整数：Ai和Bi。
//输出
//第1行：预期赢得选举的奶牛的编号。

//来源：POJ 3664

#include<iostream>
#include<algorithm>
using namespace std;

#define maxn 50010
struct node {
    int topopular;
    int fir;
    int sec;
}cow[maxn];

int coma(node a, node b) {
    return a.fir > b.fir;
}
int comb(node a, node b) {
    return a.sec > b.sec;
}
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> cow[i].fir >> cow[i].sec;
        cow[i].topopular = i;
    }
    sort(cow, cow + n, coma);
    sort(cow, cow + k, comb);
    cout << cow[0].topopular + 1;
}