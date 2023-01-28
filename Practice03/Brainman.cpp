//序列(2 8 0 3)可以通过9次相邻数字的互换来排序。然而，这一序列也可以用三次互换完成排序： 
//初始序列：2 8 0 3
//互换(8 0) 2 0 8 3
//互换(2 0) 0 2 8 3
//互换(8 3) 0 2 3 8
//因此，本题的问题是：对一个给出的序列进行排序，相邻数字的最小互换次数是多少？请您编写一个计算机程序来回答这个问题

//输入
//输入的第一行给出测试用例数。
//每个测试用例一行，首先给出序列的长度N（1maxn1000），然后给出序列的N个整数，整数所在的区间为[-1000000, 1000000]。行中的所有数字之间用空格隔开。
//输出
//对每个测试用例，在第一行输出"Scenario #i:"，其中i是从1开始的测试用例编号。然后在下一行给出对给出的序列排序所需的相邻数字的最小互换数。最后，再用一个空行表示测试用例输出结束

//来源：POJ 1804

#include<iostream>
using namespace std;

#define maxn 1000
int a[maxn];    //序列
int temp[maxn]; //临时数组
int n, t;

int ans;    // 逆序对数

void merge(int l, int m, int r) {   //合并有序序列a[l, m]和a[m + 1, r]
    int i = l;
    int j = m + 1;
    int k = i;  // 临时数据存储位置
    while (i <= m && j <= r) {
        if(a[i] > a[j]) {
            temp[k++] = a[j++];
            ans += m - i + 1;   //逆序对数
        }
        else {
            temp[k++] = a[i++];
        }
    }
    while (i <= m) temp[k++] = a[i++];  //剩余元素
    while (j <= r) temp[k++] = a[j++];  //剩余元素
    for(i = l; i <= r; i++) a[i] = temp[i]; //将结果存储至a中
}

void mergeSort(int l, int r) {
    if(l == r) return;
    else {
        int mid = (l + r) / 2;
        mergeSort(l, mid);
        mergeSort(mid + 1, r);
        merge(l, mid, r);
    }
}

int main() {
    cin >> t;
    for(int j = 1; j <= t; j++){
        ans = 0;
        cin >> n;
        for(int i = 0; i < n; i++) cin >> a[i];
        mergeSort(0, n - 1);
        cout << "Scenario #" << j << ":\n" << ans << "\n\n";
    }
    return 0;
}