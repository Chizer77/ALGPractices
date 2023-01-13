// 求最长回文子串

// Manacher算法（马拉车算法）

#include<iostream>
#include<string>
#include <cstring>

using namespace std;

// 方法一：中心扩散
// 遍历字符，以每个字符为中心向两边扩散寻找最长回文串

int expend_method01(string s, int left, int right){
    // 以left为左边界,right为右边界寻找最长回文串
    int len = s.length();
    int i = left;
    int j = right;
    while (i >= 0 && j < len) {
        if(s[i] == s[j]) {
            i--;    //向左扩散
            j++;    //向右扩散
        }
        else break;
    }
    return (j - 1) - (i + 1) + 1;   // i，j均需减一的原因是在上一循环时i,j是先自减和自增后才判断,因此跳出循环时s[i] != s[j]，字符串长度 = right - left + 1
}

string longestPalindrome_method01(string s) {    // 返回最长的回文子串
    int len = s.length();
    if(len < 2) return s;

    int maxLen = 1; //最长回文子串的长度
    int begin = 0;  //最长回文子串的起始位置

    for(int i = 0; i < len - 1; i++) {  //边界为 len - 1 的原因是最后一个字符无后续字符，也就不存在以最后一个字符为中心的回文串
        int oddLen = expend_method01(s, i, i);   //左边界为 i ,右边界为 i 开始向两边扩散寻找最长回文子串，回文串长度为奇数
        int evenLen = expend_method01(s, i, i + 1);  //左边界为 i ,右边界为 i + 1 开始向两边扩散寻找最长回文子串回文串长度为偶数

        int curMaxLen = max(oddLen, evenLen);   //取更长的一条
        if(curMaxLen > maxLen) {    //记录当前最长回文子串
            maxLen = curMaxLen;
            //begin计算方法可在纸上验证
            begin = i - (maxLen - 1) / 2;  //由于有除法向下取整的特性,可将长度为奇数和偶数的起始位置计算方法合并
        }
    }
    return s.substr(begin, maxLen);
}


//方法二：动态规划
//与中心扩散相似，但实际比较的是字符串两端的字符，若相同则比较子串的两端，以此类推，直至j - i < 3,即串长为2或3时无需比较其子串
string longestPalindrome_method02(string s) {
    int len = s.length();
    if(len < 2) return s;

    int maxLen = 1;
    int begin = 0;

    bool dp[len][len];
    for(int i = 0; i < len; i++) dp[i][i] = true;   //对角线初始化,实际并没有用到对角线的值

    for(int j = 1; j < len; j++) {  // j = 1 原因：右边界为0时不存在子串，j表示子串右边界
        for(int i = 0; i < j; i++) {    //边界是 i < j 原因：s的左边界始终小于右边界，i表示子串左边界
            if(s[i] != s[j]) {
                dp[i][j] = false;
            } else {    //两端字符相等的情况
                if(j - i < 3) { //串长小于4，无需比较子串两端
                    dp[i][j] = true;
                }
                else {
                    dp[i][j] = dp[i + 1][j - 1];    //参考子串两端
                }
            }
            if(maxLen < j - i + 1 && dp[i][j]) {    //是回文串且比最长回文子串长度长
                maxLen = j - i + 1;
                begin = i;
            }
        }
    }
    return s.substr(begin, maxLen);
}


//马拉车算法
//具体化版本并非最简，但时间复杂度同样是O(n)

string addDividers(string s, char divider) {
    if(s.find(divider) != -1) return "Input ERROR! Divider already exists in the string.\n";
    string ss;
    for(char i : s) {
        ss += divider;
        ss += i;
    }
    ss += divider;
    return ss;
}

string longestPalindrome_method03(string s) {
    int len = s.length();
    if(len < 2) return s;

    int maxLen = 1; //原字符串的最长回文子串长度
    int begin = 0;  //原字符串的最长回文子串起始位置

    string str = addDividers(s, '#');   //在字符串间插入字符’#‘且原字符串中不存在#
    int sLen = len * 2 + 1; //处理后的字符串长度

    int p[sLen];    //以处理后的字符串下标i为中心的回文半径
    memset(p, 0, sizeof(p));

    int maxRight = 0;   //通过中心扩散能够扩散的最右边的下标
    int center = 0; //与maxRight对应的中心字符下标

    for(int i = 0; i < sLen; i++) {
        if(i < maxRight) {
            int mirror = 2 * center - i;    // 对应i在center对称的位置
            p[i] = min(maxRight - i, p[mirror]);    //状态转移方程，结合了p[mirror] < maxRight - i 和 p[mirror] > maxRight - i对应的p[i]结果
        }

        //其余情况
        //用中心扩散更新p[i]的值
        int left = i - (p[i] + 1);  //现子串的左边界
        int right = i + (p[i] + 1); //现子串的右边界
        while(left >= 0 && right < sLen && str[left] == str[right]) {
            p[i]++; //增加回文半径
            left--;
            right++;
        }

        //更新maxRight和center
        if(maxRight < i + p[i]) {
            maxRight = i + p[i];
            center = i;
        }

        //更新最长回文子串长度和起始位置
        if(p[i] > maxLen) {
            //可在纸上验证maxLen和begin的值
            maxLen = p[i];
            begin = (i - maxLen) / 2;
        }
    }
    return s.substr(begin, maxLen);
}


int main() {
    string s;
    cin >> s;   //输入字符串

    // 方法一
    // cout << longestPalindrome_method01(s);

    // 方法二
    // cout << longestPalindrome_method02(s);

    // 方法三
    // cout << longestPalindrome_method03(s);
}