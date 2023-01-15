//您知道栈和队列吗？它们都是重要的数据结构。栈是“先进后出”（FILO）的数据结构，而队列是“先进先出”（FIFO）的数据结构。
//现在给出这样的问题：给出进入结构和离开结构的一些整数的次序（假定在栈和队列中都是整数），请您确定这是怎样的数据结构，是栈还是队列？
//请注意，本题设定在所有的整数没有进入数据结构前，没有整数被弹出。

//输入
//输入包含多个测试用例。输入的第一行是一个整数T (T≤100)，表示测试用例的个数。然后给出T个测试用例。
//每个测试用例包含3行：测试用例的第一行给出一个整数N，表示整数个数(1≤N≤100)。
// 测试案例的第二行给出用空格分隔开的N个整数，表示进入结构的次序（即，第一个数据最先进入）。
// 测试案例第三行给出用空格分隔开的N个整数，表示离开结构的次序（第一个数据是最先离开）。
//输出
//对于每个测试用例，在一行中输出判定的结果。如果结构只能是一个栈，则输出“stack”；如果结构只能是一个队列，输出“queue”；
// 如果结构既可以是栈，也可以是队列，则输出“both”；否则输出“neither”。

//来源：ZOJ 3210

//基本方法：
//按照出入结构的次序，若第i个进入结构的元素在第i个离开，则该结构满足“先进先出”的性质，则该结构为队列；
// 若第i个进入结构的元素在倒数第i个离开，则该结构满足“先进后出”的性质，则该结构为栈（0≤i≤n-1）

#include<iostream>
#define maxn 100 + 10
using namespace std;
int main() {
    int loop;
    cin >> loop;
    while (loop--) {
        int n, a[maxn];
        cin >> n;
        for(int i = 0; i < n; i++) cin >> a[i]; // 进入结构的次序
        bool isStack = true, isQueue = true;    // 初始标志
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;   //依次离开结构的数
            if(x != a[i]) isQueue = false;  //并不是先进先出
            if(x != a[n - i - 1]) isStack = false;  //并不是先进后出
        }
        if(isStack && isQueue) cout << "both\n";
        else if(isStack) cout << "stack\n";
        else if(isQueue) cout << "queue\n";
        else cout << "neither\n";
    }
}