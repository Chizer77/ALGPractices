//输入
//首先输入一个词典，词典中包含不超过100000个词条，每个词条占据一行。每一个词条包括一个英文单词和一个外语单词，在两个单词之间用一个空格隔开。
// 而且在词典中不会有某个外语单词出现超过两次。
// 词典之后是一个空行，然后给出不超过100000个外语单词，每个单词一行。输入中出现单词只包括小写字母，而且长度不会超过10。
//输出
//在输出中，你需要把输入的单词翻译成英文单词，每行输出一个英文单词。如果某个外语单词不在词典中，就把这个单词翻译成“eh”。

//来源：POJ 2503

#include<cstdio>
#include<cstring>
using namespace std;
#define maxn (100000 + 10)    //最大词条数
#define maxs (10 + 5) //单词最大长度
char dict[maxn][2][maxs];   //词典
int n;  //词典长度

bool isblank(char s[]) {    //判断是否到达空行
    int k = strlen(s);
    while (--k >= 0) {
        if(s[k] >= 'a' && s[k] <= 'z') return false;
    }
    return true;    //是空行
}

void swap(char a[], char b[]) {
    char t[maxs];
    strcpy(t, a);
    strcpy(a, b);
    strcpy(b, t);
}

//类似归并排序
void sort(int a, int b, char s[][2][maxs]) {    //按照外文单词的字典序进行排序
    if(a >= b) return;
    char t[maxs];
    strcpy(t, s[(a + b)/2][1]); //取中间词条的外文单词
    int i = a - 1;  //左指针
    int j = b + 1;  //右指针
    do {    //右移左指针，直到指向的第一个外文单词不小于中间词条外文单词的词条i
        do {
            ++i;
        } while (strcmp(t, s[i][1]) > 0);
        do {    //左移右指针，直到指向的第一个外文单词不大于中间词条外文单词的词条j
            --j;
        } while (strcmp(t, s[j][1]) < 0);
        if(i < j) {
            swap(s[i][0], s[j][0]);
            swap(s[i][1], s[j][1]);
        }
    } while (i < j);    //直到中间词条找到插入位置
    sort(a, j, s);  //递归左子序列
    sort(j + 1, b, s);  //递归右子序列
}

int find(char s[]) {    //二分查找外文单词s
    int l = 0, r = n;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if(strcmp(dict[mid][1], s) <= 0) {  //s在dict的右区间
            l = mid;
        }
        else r = mid;
    }
    if(strcmp(dict[l][1], s)) return -1;    //找不到
    return l;   //找到，返回位置
}

int main() {
    char s[maxs + maxs];
    n = 0;
    gets(s);    //读入第一个词条
    while (!isblank(s)) {
        sscanf(s, "%s%s", dict[n][0], dict[n][1]);   //读入英文单词和外文单词
        ++n;
        gets(s);
    }
    sort(0, n - 1, dict);
    while (scanf("%s", s) != EOF) {
        int k = find(s);
        if(k < 0) printf("%s\n", "eh");
        else printf("%s\n", dict[k][0]);
    }
    return 0;
}
