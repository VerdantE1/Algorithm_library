//
// Created by Buzzlight on 2025/3/25.
//

#include <vector>
#include "algorithms/search.h"
namespace frank{
    //二分搜索算法：返回目标值的索引，如果未找到返回 -1
    int binarySearch(const std::vector<int>&nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right){
            int mid = left + (right - left) / 2;
            if(nums[mid] == target){
                return mid;
            }else if(nums[mid] < target){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        return -1;
    }
}