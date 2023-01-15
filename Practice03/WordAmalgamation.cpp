//在美国的很多报纸上，有一种单词游戏Jumble。这一游戏的目的是解字谜，为了找到答案中的字母，就要整理4个单词。请您编写一个整理单词的程序。
//即打乱顺序的字母寻找组成单词
//输入
//输入包含4个部分：
//1）字典，包含至少1个至多100个的单词，每个单词一行；
//2）一行内容为XXXXXX，表示字典结束；
//3）一个或多个你要整理的“单词”；
//4）一行内容为XXXXXX，表示文件的结束。
//所有的单词，无论是字典单词还是要整理的单词，都是小写英文字母，至少1个字母，至多6个字母（XXXXXX是由大写的X组成），字典中单词不排序，但每个单词只出现一次。
//输出
//对于输入中每个要整理的单词，输出在字典里存在的单词，单词的字母排列可以不同，
// 如果在字典中找到不止一个单词对应时要把他们按字典序进行排序。每个单词占一行。
// 如果没找到相对应的单词则输出NOT A VALID WORD，每输出对应的一组单词或NOT A VALID WORD后要输出******

//来源：POJ 1318

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
    char word[101][10], str1[10], str2[10];
    int i, j, length1, length2, s = 0;
    while (true) {
        cin >> word[s];
        if(strcmp(word[s++], "XXXXXX") == 0) break;
    }
    for(i = 0; i < s - 2; i++) {    //对字典进行选择排序
        for(j = i + 1; j < s - 1; j++) {
            if(strcmp(word[i], word[j]) > 0) {
                strcpy(str1, word[i]);
                strcpy(word[i], word[j]);
                strcpy(word[j], str1);
            }
        }
    }
    while ((cin >> str1) && strcmp(str1, "XXXXXX") != 0) {
        int flag = 1;
        length1 = strlen(str1);
        sort(str1, str1 + length1); //对待处理单词进行升序排序
        for(i = 0; i < s - 1; i++) {
            length2 = strlen(word[i]);
            strcpy(str2, word[i]);
            sort(str2, str2 + length2);
            if(strcmp(str1, str2) == 0) {
                cout << word[i] << '\n';
                flag = 0;
            }
        }
        if(flag) cout << "NOT A VALID WORD\n";
        cout << "******\n";
    }
}