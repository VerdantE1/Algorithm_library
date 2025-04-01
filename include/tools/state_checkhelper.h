//
// Created by 25238 on 4/1/2025.
//

#pragma once
#include "state_compression.h"


using namespace frank_tools;


namespace validators {
    // 一个状态里的相邻位数不同
    inline StateValidator adjacentDifferent = [](const std::vector<int> &digits) {
        for (int i = 1; i < digits.size(); ++i) {
            if (digits[i] == digits[i - 1]) return false;
        }
        return true;
    };
}




namespace compat {
    //两个状态的任意一个数字不能相同
    inline StateCompatChecker noSamePosition = [](const std::vector<int>& a, const std::vector<int>& b) {
        for (int i = 0; i < a.size(); ++i)
            if (a[i] == b[i]) return false;
        return true;
    };
}