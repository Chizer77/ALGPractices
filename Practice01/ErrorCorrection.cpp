//当一个布尔矩阵的每行和每列总和为偶数时，该布尔矩阵具有奇偶均势的特性，即包含偶数个1。例如，一个4 × 4具有奇偶均势特性的矩阵：
//1 0 1 0
//0 0 0 0
//1 1 1 1
//0 1 0 1
//行的总和是2, 0, 4 和 2。列的总和是2, 2, 2 和 2。
//请您编写一个程序，输入矩阵，并检查其是否具有奇偶均势特性。如果没有，程序还要检查是否可以通过仅改变矩阵中的一个数字使得矩阵具有奇偶均势特性。如果不能，则把矩阵归类为“Corrupt”。

//输入
//输入包含一个或多个测试用例，每个测试用例的第一行是一个整数n(n<100)，表示矩阵的大小。后面的n行，每行n个数，矩阵中的每个数不是0就是1。输入以n为0作为结束。
//输出
//对于输入的每个矩阵，输出一行。如果该矩阵具有奇偶均势特性，则输出“OK”。
// 如果奇偶均势特性可以通过改变1个数字产生，则输出“Change bit (i,j)”，其中i是要改变数字所在的行，j是要改变数字所在的列；否则输出“Corrupt”。

#include<iostream>
using namespace std;
#define MAXN 512    //矩阵容量
int n;  //矩阵规模
int a[MAXN][MAXN], row[MAXN], col[MAXN];    //矩阵为a, 其中i行数和为row[i], j列数和为col[j]


int read_case() {   //输入矩阵并初始化row[], col[]
    int i, j;
    cin >> n;
    if(n == 0) return 0;
    for(i = 0; i < n; i++) {
        row[i] = 0;
        col[i] = 0;
        for(j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    return 1;
}

void solve_case() { //判断奇偶均势性
    int cc, cr, i, j, k;
    for(i = 0; i < n; i++) {    //计算每行每列数和
        for(j = 0; j < n; j++) {
            row[i] += a[i][j];
            col[j] += a[i][j];
        }
    }
    cr = cc = 0;
    for(k = 0; k < n; k++) {    //累计行数和（列数和）为奇数的行（列）数cr(cc)
        if(row[k] & 1) {
            cr++;
            i = k;  //i用于记录最后一行为奇数的行序号
        }
        if(col[k] & 1) {
            cc++;
            j = k;  //j用于记录最后一列为奇数的列序号
        }
    }
    if(cc == 0 && cr == 0) cout << "OK\n";  //无奇数行与列
    else if(cc == 1 && cr == 1) cout << "Change bit (" << i+1 << ',' << j+1 << ")\n";   //仅有一行奇数行与列
    else cout << "Corrupt\n";
}

int main() {
    while (read_case()) solve_case();
    return 0;
}