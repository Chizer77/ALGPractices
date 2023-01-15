//Smith夫妇要去海边渡假，在他们出发前，他们要选择一家宾馆。他们从互联网上获得了一份宾馆的列表，要从中选择一些既便宜又离海滩近的侯选宾馆。侯选宾馆M要满足两个需求：
//1. 离海滩比M近的宾馆要比M贵。
//2. 比M便宜的宾馆离海滩比M远。
//输入
//有若干组测试用例，每组测试用例的第一行给出一个整数N（1≤N≤10000），表示宾馆的数目，
// 后面的N行每行给出两个整数D和C（1≤D, C≤10000），用于描述一家宾馆，D表示宾馆距离海滩的距离，C表示宾馆住宿的费用。
// 本题设定没有两家宾馆有相同的D和C。用N = 0表示输入结束，对这一测试用例不用进行处理。
//输出
//对于每个测试用例，输出一行，给出一个整数，表示所有的侯选宾馆的数目

#include<iostream>
#include<algorithm>
using namespace std;

#define maxn 10000
struct hotel {
    int dist;
    int cost;
}h[maxn];

bool compar(hotel &a, hotel &b) {   //以dist为第一关键字排序
    if(a.dist == b.dist) return a.cost < b.cost;
    return a.dist < b.dist;
}

int main() {
    int n;
    while ((cin >> n) && n) {
        for(int i = 0; i < n; i++) cin >> h[i].dist >> h[i].cost;
        sort(h, h + n, compar); //结构体排序
        int min = INT_MAX;
        int ans = 0;
        for(int i = 0; i < n; i++) {
            if(h[i].cost < min) {   //若cost更小则进入预选
                ans++;
                min = h[i].cost;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
