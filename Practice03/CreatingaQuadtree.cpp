//输入
//第一行给出一个整数N > 0，表示测试用例的个数。接下来的N行给出一个用空格分隔的列表，首先给出一个整数n（n > 1），n是2的幂次，表示矩阵的大小；
// 然后给出m *2对整数(ik , jk)，使得：
//a)  ik是列的下标；
//b)  jk是行的下标；
//c)  1≤ik, jk≤n；
//d)  两个连续对(ik-1 , jk-1)和(ik , jk)，其中k是偶数，分别表示第1/2k区域的左上角和右下角的位置；
//e) 如果m是奇数，则(im, jm)被忽略；
//输出
//输出N行。每行或者是每个测试用例产生的四叉树；或者是“Size is invalid”，如果矩阵的大小不是2的幂。
// 四叉树是由一连串的0和1来表示。对每个黑色节点，在输出中添加一个“0”；对每个白色节点，在输出中添加一个“1”；对每个灰色节点，在输出中添加一个“*”，
// 并对每个子节点重复这一过程。在输出中不用考虑根。先序遍历这个四叉树。

//来源：UVA 11941

//基本方法：
//1. 判别矩阵合法与否
//2. 构造与01位图g[ ][ ]相对应的四叉树
//3. 计算四叉树的先序串

#include<iostream>
#include<sstream>
#include<string>
#include <cstring>

using namespace std;

char g[1024][1024]; //整个区域的相邻矩阵，值为1表示白像素，值为2表示黑像素
char node[1024*1024];   //四叉树中节点k的值，3表示分支结点，1表示黑色结点，0表示白色结点

//从节点k（代表左上角为(lx, ly)，右下角(rx, ry)的子矩阵）出发，构建以其为根的四叉树
int build(int k, int lx, int ly, int rx, int ry) {
    if(lx == rx && ly == ry) return node[k] = 1 << g[lx][ly];   //(lx, ly) == (rx, ry)表示为叶节点，对1左移表示node[k] = 2 的 g[lx][ly]次方
    int mx = (lx + rx) / 2;
    int my = (ly + ry) / 2; //计算当前区域的中间坐标(mx, my)
    int v = 0;  //计算四个子区域或等的结果v,或等
    v |= build(k * 4, lx, ly, mx, my);  //左上角子区域
    v |= build(k * 4 + 1, mx + 1, ly, rx, my);  //右上角子区域
    v |= build(k * 4 + 2, lx, my + 1, mx, ry);   //左下角子区域
    v |= build(k * 4 + 3, mx + 1, my + 1, rx, ry);  //右下角区域
    return node[k] = v; //返回k结点的值
}

void dfs(int u) {   //先序遍历输出结果串
    if(node[u] == 3) {  //点u为分支结点
        if(u > 1) putchar('*');
        dfs(4 * u);
        dfs(4 * u + 1);
        dfs(4 * u + 2);
        dfs(4 * u + 3);
    } else {    //u为1，则输出子矩阵全黑标志；u为2，则输出子矩阵全白标志
        if(node[u] == 1) putchar('0');
        else putchar('1');
    }
}

int main() {
    int testcase;
    int n, sx, sy, ex, ey;  //矩阵大小n, 子区域左上角sx, sy; 右下角ex, ey
    char line[32767];
    scanf("%d", &testcase);
    while (getchar() != '\n');
    while(testcase--) {
        gets(line);
        stringstream sin(line); //将line中字符放入sin对象中
        string token;
        sin >> n;   //从列表串中截取矩阵大小n
        if(__builtin_popcount(n) != 1 || n <= 1) {  //若n不是2的幂（n不大于1或有不止1个二进制位为1），则输出非法信息
            puts("Size is invalid!");
            continue;
        }
        memset(g, 0, sizeof(g));
        while(sin >> token) {   //从列表串截取当前白色区域的左上角坐标（sx, sy）
            sscanf(token.c_str(), "(%d,%d)", &sx, &sy);
            if(sin >> token) {
                sscanf(token.c_str(), "(%d,%d)", &ex, &ey);   //右下角坐标
                sx--;
                sy--;
                ex--;
                ey--;
                for(int i = sx; i <= ex; i++) { //在该区域标记为1
                    for(int j = sy; j <= ey; j++) {
                        g[i][j] = 1;
                    }
                }
            }
        }
        build(1, 0, 0, n - 1, n - 1);   //以1为根节点建树
        dfs(1);
        puts("");
    }
    return 0;
}


