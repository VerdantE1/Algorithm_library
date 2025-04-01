//
// Created by 25238 on 4/1/2025.
//

#pragma once
#include <vector>
#include <iostream>
#include <cassert>
#include <functional>


namespace frank_tools {


using StateValidator = std::function<bool(const std::vector<int>&)>;
using StateCompatChecker = std::function<bool(const std::vector<int>&, const std::vector<int>&)>;

// 整数式：直接操作 int 状态
using RawStateValidator = std::function<bool(int)>;
using RawStateCompatChecker = std::function<bool(int,int)>;


/**
 * 通用工具类：用于状态压缩 DP 中 base-N 状态的编码、解码与合法性判断
 * 可用于：格子染色、位图状态、排列组合、网格状态压缩等
 * 低位在前
 * 返回的都是int state,需要decode解码 若是vector<int> 必定是vector<STATE>
 */
    class StateEncoder {
    private:
        int m;      // 维度（多少位）
        int base;   // 每位可取 0~(base-1)
        using EncodeState = int;

    public:

        StateEncoder(int digits, int baseVal) : m(digits), base(baseVal) {
            assert(m > 0 && base > 1);
        }

        // 将 vector<int> 编码为整数状态（低位在前）
        EncodeState encode(const std::vector<int> &digits) const {
            assert(digits.size() == m);
            int state = 0;
            for (int i = m - 1; i >= 0; --i) {
                assert(digits[i] < base);
                state = state * base + digits[i];
            }
            return state;
        }
        // 将int state转化为vector<int>
        std::vector<int> decode(EncodeState state) const {
            std::vector<int> digits(m);
            for (int i = 0; i < m; ++i) {
                digits[i] = state % base;
                state /= base;
            }
            return digits;
        }


        bool isValid(EncodeState state, const StateValidator& validator) const {
            return validator(decode(state));
        }

        bool isCompatible(EncodeState s1, EncodeState s2, const StateCompatChecker& checker) const {
            return checker(decode(s1), decode(s2));
        }

        std::vector<EncodeState> getAllValidStates(const StateValidator& validator) const {
            int total = 1;
            for (int i = 0; i < m; ++i) total *= base;

            std::vector<int> result;
            for (int s = 0; s < total; ++s) {
                if (isValid(s, validator)) result.push_back(s);
            }
            return result;
        }

        int getDigitCount() const { return m; }
        int getBase() const { return base; }

    };

} // namespace tools
