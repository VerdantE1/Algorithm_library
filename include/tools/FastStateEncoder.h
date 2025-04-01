//
// Created by 25238 on 4/1/2025.
//

#pragma once
#include <vector>
#include <functional>
#include <cassert>

#pragma once
#include <vector>
#include <functional>
#include <cassert>

namespace frank_tools {

    /// @brief 压缩后的状态表示（整数形式）
    using EncodedState = int;

    /// @brief 状态合法性检查器（单状态）
    using RawValidator = std::function<bool(EncodedState)>;

    /// @brief 状态兼容性检查器（双状态）
    using RawCompatChecker = std::function<bool(EncodedState, EncodedState)>;

    /**
     * @class FastStateEncoder
     * @brief 高效状态压缩与枚举工具类
     *
     * 用于将 m 维 base 进制的状态压缩为整数，并支持：
     * - 枚举所有合法状态（通过外部 validator 控制）
     * - 判断两个状态是否兼容（通过传入 checker 控制）
     * - 反解码状态为 vector<int>（可选，用于调试）
     *
     * 常用于动态规划、状态压缩、图染色等问题。
     *
     * 示例用法：
     * @code
     * FastStateEncoder encoder(m, base);
     * auto validator = makeAdjacentDifferentValidator(m, base);
     * auto checker = makeNoSamePositionChecker(m, base);
     *
     * auto states = encoder.getAllValidStates(validator);
     * for (int s1 : states)
     *     for (int s2 : states)
     *         if (encoder.isCompatible(s1, s2, checker)) {
     *             // s1 和 s2 可以相邻使用
     *         }
     * @endcode
     */
    class FastStateEncoder {
    private:
        int m, base;
        int totalStates;

    public:
        /**
         * @brief 构造函数
         * @param m_ 状态的维度（例如行数）
         * @param base_ 每位的进制（例如 3 表示三种颜色）
         */
        FastStateEncoder(int m_, int base_) : m(m_), base(base_) {
            totalStates = 1;
            for (int i = 0; i < m; ++i) totalStates *= base;
        }

        /**
         * @brief 枚举所有满足 validator 条件的状态
         * @param validator 状态合法性检查器（如相邻不同颜色）
         * @return 所有合法状态的集合（整数编码形式）
         */
        std::vector<EncodedState> getAllValidStates(const RawValidator& validator) const {
            std::vector<EncodedState> result;
            for (int s = 0; s < totalStates; ++s) {
                if (validator(s)) result.push_back(s);
            }
            return result;
        }

        /**
         * @brief 判断一个状态是否合法
         * @param state 被检查的状态
         * @param validator 判定逻辑
         */
        bool isValid(EncodedState state, const RawValidator& validator) const {
            return validator(state);
        }

        /**
         * @brief 判断两个状态是否兼容（适用于相邻行）
         * @param s1 状态1
         * @param s2 状态2
         * @param checker 判定逻辑
         */
        bool isCompatible(EncodedState s1, EncodedState s2, const RawCompatChecker& checker) const {
            return checker(s1, s2);
        }

        /**
         * @brief 将整数状态解码为 base 进制的向量（从低位到高位）
         * @param state 编码的整数状态
         * @return 解码后得到的 vector<int> 形式
         */
        std::vector<int> decode(int state) const {
            std::vector<int> digits(m);
            for (int i = 0; i < m; ++i) {
                digits[i] = state % base;
                state /= base;
            }
            return digits;
        }

        /// @brief 获取状态长度（维度）
        int getDigitCount() const { return m; }

        /// @brief 获取进制数（每位的取值范围）
        int getBase() const { return base; }

        /// @brief 获取所有可能状态数量（不含 validator 过滤）
        int getTotalStates() const { return totalStates; }
    };

} // namespace frank_tools





using namespace frank_tools;
// Validator
/**
 * @brief 创建一个相邻位不同的 validator（用于染色类状态）
 *
 * @param m 状态维度（几位）
 * @param base 进制（如 3 表示每位颜色编号 0~2）
 * @return RawValidator 类型的可复用函数对象
 */
inline RawValidator makeAdjacentDifferentValidator(int m,int base) {
    return [m,base](int state) {
        int prev  = -1;
        for(int i =0;i<m;i++){
            int cur = state % base; //模base意味着将数化成base进制并向右移动一位
            if(cur == prev ) return false;
            prev = cur;
            state /= base ; //除以base意味着将数化成base进制并向右移动一位
        }
        return true;
    };
}


// CompatChecker
/**
 * @brief 创建一个 checker，确保两个状态在每一列上值都不同
 *
 * @param m 状态维度（几位）
 * @param base 进制（每位的取值范围）
 * @return RawCompatChecker 类型的函数对象
 */
inline RawCompatChecker makeNoSamePositionChecker(int m,int base) {
    return [m,base](int a, int b) {
        for (int i = 0; i < m; i++) {
            if (a % base == b % base) return false;
            a /= base;
            b /= base;
        }
        return true;
    };
}