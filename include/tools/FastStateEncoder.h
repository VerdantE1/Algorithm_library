//
// Created by 25238 on 4/1/2025.
//

#pragma once
#include <vector>
#include <functional>
#include <cassert>

namespace frank_tools {

    using EncodedState = int;
    using RawValidator = std::function<bool(EncodedState)>;
    using RawCompatChecker = std::function<bool(EncodedState, EncodedState)>;

    class FastStateEncoder {
    private:
        int m, base;
        int totalStates;

    public:
        FastStateEncoder(int m_, int base_) : m(m_), base(base_) {
            totalStates = 1;
            for (int i = 0; i < m; ++i) totalStates *= base;
        }

        // 直接枚举所有合法状态（不解码）
        std::vector<EncodedState> getAllValidStates(const RawValidator& validator) const {
            std::vector<EncodedState> result;
            for (int s = 0; s < totalStates; ++s) {
                if (validator(s)) result.push_back(s);
            }
            return result;
        }

        bool isValid(EncodedState state, const RawValidator& validator) const {
            return validator(state);
        }

        bool isCompatible(EncodedState s1, EncodedState s2, const RawCompatChecker& checker) const {
            return checker(s1, s2);
        }

        // 解码（仅在调试或使用 vector 时使用）
        std::vector<int> decode(int state) const {
            std::vector<int> digits(m);
            for (int i = 0; i < m; ++i) {
                digits[i] = state % base;
                state /= base;
            }
            return digits;
        }

        int getDigitCount() const { return m; }
        int getBase() const { return base; }
        int getTotalStates() const { return totalStates; }
    };

} // namespace tools





using namespace frank_tools;
// Validator
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