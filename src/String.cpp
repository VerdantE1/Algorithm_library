//
// Created by 25238 on 3/31/2025.
//

#include "string/String.h"

namespace frank{

/**
 * @param s 输入字符串，允许空字符串
 *
 * @功能 查找最长回文子串，生成回文判断DP表
 *
 * @算法 动态规划：
 *   - dp[i][j]表示s[i..j]是否为回文
 *   - 状态转移：s[i]==s[j] && dp[i+1][j-1]
 *   - 时间复杂度O(n2)，空间复杂度O(n2)
 *
 * @返回值 tuple<
 *   int:       最长回文长度,
 *   string:    最长回文内容,
 *   bool[][] : dp表（dp[i][j]=true表示s[i..j]是回文）
 * >
 *
 * @用法示例 auto [len, str, dp] = longestPalinSubstr("babad");
 *
 * @注意事项
 * ◆ DP表内存消耗大（n>1e4慎用）
 * ◆ 多个最长回文时返回最后出现者
 * ◆ 空输入返回(0, "", 空表)
 *
 * @相关函数 isPalindrome() 快速单次判断
 */
std::tuple<int, std::string,std::vector<std::vector<bool>>> longestPalinSubstr(const std::string &s) {
    int n = s.size();
    if (n == 0) return {0, "",{}};

    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    int start = 0;
    int max_len = 1;

    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
        if (i < n - 1 && s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            max_len = 2;
        }
    }

    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                max_len = len;
            }
        }
    }

    return {max_len, s.substr(start, max_len),dp};
}



/**
 * @brief 查找字符串数组中的最长公共前缀
 *
 * @param strs 输入字符串数组，允许包含空字符串或空数组
 * @return string 所有字符串的公共前缀，空数组返回空字符串
 *
 * @details [算法原理]
 * 纵向扫描法：
 * 1. 以第一个字符串为基准，逐字符遍历
 * 2. 对每个字符位置j，检查所有字符串的j位置字符
 * 3. 遇到不匹配字符或字符串长度不足时终止
 *
 * @complexity [复杂度分析]
 * - 时间复杂度：O(n*m)（n=数组长度，m=最短字符串长度）
 * - 空间复杂度：O(1)（仅使用常数额外空间）
 *
 * @example [使用示例]
 * string res = longestCommonPrefix({"flower","flow","flight"}); // 返回"fl"
 * string res2 = longestCommonPrefix({}); // 返回""
 *
 * @note [注意事项]
 * 1. 输入空数组时直接返回空字符串
 * 2. 所有字符串完全相同时返回第一个字符串
 * 3. 数组中存在空字符串时立即返回空结果
 */
string longestCommonPrefix(const vector<string>& strs) {
    if (strs.empty()) return "";

    const string& s0 = strs[0];
    for (int j = 0; j < s0.size(); ++j) {
        for (const string& s : strs) {
            if (j == s.size() || s[j] != s0[j]) {
                return s0.substr(0, j);
            }
        }
    }
    return s0;
}


/**
 * @brief [功能概述] 计算两个字符串之间的最小编辑距离
 *
 * @param word1 原始字符串，允许为空
 * @param word2 目标字符串，允许为空
 * @return int 将word1转换为word2所需的最少操作次数，操作包括插入、删除、替换
 *
 * @details [算法原理]
 * 采用动态规划解法：
 * - 定义dp[i][j]表示将word1前i个字符转换为word2前j个字符的最小操作数
 * - 边界条件：任意字符串长度为0时，操作数为另一字符串长度
 * - 状态转移：
 *   a. 字符相等：dp[i][j] = dp[i-1][j-1]
 *   b. 字符不等：dp[i][j] = 1 + min(插入, 删除, 替换)
 *
 * @complexity [复杂度分析]
 * - 时间复杂度：O(n*m)，n/m为输入字符串长度
 * - 空间复杂度：O(n*m)，可优化至O(min(n,m))（当前实现未优化）
 *
 * @example [使用示例]
 * int dist = minDistance("kitten", "sitting"); // 返回3
 * 操作序列：
 * kitten -> sitten (替换k->s)
 * sitten -> sittin (替换e->i)
 * sittin -> sitting (插入g)
 */
int minDistance(string word1, string word2) {
    int n = word1.size(); int m = word2.size();

    if(n * m ==0) return n+m;  //空串处理

    vector<vector<int>> dp(n+1,vector<int>(m+1,0x3f3f3f));

    for(int i =0;i<n;i++) dp[i][0] = i; //变到空字符 删除
    for(int j =0;j<m;j++) dp[0][j] = j; //变到j串  增加

    for(int i =1;i<=n ;i++){
        for(int j =1;j<=m;j++){
            //若两字符串最后一个字符相等   处理word1[0...i] word2[0...j]
            if(word1[i-1] == word2[j-1])  dp[i][j] = dp[i-1][j-1]; //第i个字符是word1里面的索引i-1
            else{
                dp[i][j] = min(dp[i][j],dp[i-1][j]+1); //删除i串的最后一个
                dp[i][j] = min(dp[i][j],dp[i-1][j-1]+1); //替换i串最后一个，使得最后一个字符相等
                dp[i][j] = min(dp[i][j],dp[i][j-1]+1); //插入一个i串使得与j串相等
            }
        }
    }

    return dp[n][m];
}


int strStr(string s, string p) {
    int n = s.size(), m = p.size();
    if(m == 0) return 0;
    //设置哨兵
    s.insert(s.begin(),' ');
    p.insert(p.begin(),' ');
    vector<int> next(m + 1);
    //预处理next数组
    for(int i = 2, j = 0; i <= m; i++){
        while(j and p[i] != p[j + 1]) j = next[j];
        if(p[i] == p[j + 1]) j++;
        next[i] = j;
    }
    //匹配过程
    for(int i = 1, j = 0; i <= n; i++){
        while(j and s[i] != p[j + 1]) j = next[j];
        if(s[i] == p[j + 1]) j++;
        if(j == m) return i - m;
    }
    return -1;
}


}