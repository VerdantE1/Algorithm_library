//
// Created by 25238 on 3/31/2025.
//

#ifndef ALGORITHMS_STRING_H
#define ALGORITHMS_STRING_H


#include <tuple>
#include <string>
#include <vector>
using namespace std;
namespace frank{
    /**
    * @功能 查找最长回文子串，生成回文判断DP表
    * @参数 s 输入字符串
    * @返回值 tuple包含：
    *          - int: 最长回文子串长度
    *          - string: 最长回文子串内容
    *          - vector<vector<bool>>: 回文判断DP表（s[i..j]是否为回文）
    * @用法 auto [len, substr, dp] = longestPalinSubstr("babad"); // 返回 (3, "bab", DP表)
    * @时间复杂度 O(n^2)
    * @空间复杂度 O(n^2)
 */
    tuple<int, std:: string,vector<std:: vector<bool>>> longestPalinSubstr(const string &s);

    /**
    * @功能 查找字符串数组中的最长公共前缀
    * @参数 strs 字符串数组（至少包含一个字符串）
    * @返回值 最长公共前缀字符串
    * @用法 string prefix = longestCommonPrefix({"flower","flow","flight"}); // 返回 "fl"
    * @时间复杂度 O(S) 其中S是所有字符串字符总数
    * @空间复杂度 O(1) (除返回字符串外)
    */
    string longestCommonPrefix(const vector<string>& strs);

    /**
     * @功能 计算两个字符串的编辑距离（Levenshtein距离）
     * @参数 word1 原始字符串
     * @参数 word2 目标字符串
     * @返回值 将word1转换为word2所需的最少操作次数（插入/删除/替换）
     * @用法 int dist = minDistance("kitten", "sitting"); // 返回3
     * @时间复杂度 O(m*n) (m和n分别为两个字符串长度)
     * @空间复杂度 O(min(m,n))
     */
    int minDistance(string word1, string word2);


}
#endif //ALGORITHMS_STRING_H
