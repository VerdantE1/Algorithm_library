//
// Created by 25238 on 3/31/2025.
//
#include <iostream>
#include <algorithm>
#include "library.h"

using namespace std;
using namespace frank_tools;
using namespace frank;

const int MOD =1e9+7;



int main(){
    int m ,n; cin >> m >>n;
    StateEncoder encoder(m,3); //定义一个编码器，m位，3进制

    auto States = encoder.getAllValidStates(validators::adjacentDifferent); //得到所有不相邻的符合状态
    int sz = States.size();

    //i行兼容j的状态
    vector<vector<int>> compat(sz);
    vector<vector<int>> dp(n, vector<int>(sz, 0));

    // 初始化第一列
    for (int i = 0; i < sz; i++) {
        dp[0][i] = 1;
    }
    const int MOD = 1e9 + 7;

    for(int col =1;col<n;col++){
        for(int i =0;i<sz;i++){
            int i_state = States[i];
            for(int j =0;j<sz;j++){
                int j_states = States[j];
                if(encoder.isCompatible(i_state,j_states,compat::noSamePosition)){
                    dp[col][i] += dp[col-1][j];
                    dp[col][i] %= MOD;
                }
            }
        }
    }
    int result = 0;
    for (int i = 0; i < sz; i++) {
        result = (result + dp[n - 1][i]) % MOD;
    }

    cout << result <<endl;


    return 0;
}