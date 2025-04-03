//
// Created by Buzzlight on 2025/3/25.
//

#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H
using namespace  std;
#include <vector>
#include <functional>


//1.为vector<int>服务
//2.

namespace frank{
    //模板 1：查找某个元素的下标（找第一个等于 target 的位置） 需要正序数值
    int binarySearch(const std::vector<int>&nums, int target){
        int left =0 ,right =nums.size() -1;
        while(left <= right){
            int mid = left + (right-left) /2;
            if(nums[mid] == target) return mid;
            else if (nums[mid] < target)  left = mid+1;
            else right = mid-1;
        }
        return left;
    }

    //模板 2：寻找第一个满足条件的位置（左边界/最小值）
    int binaryLeft(const std::vector<int>& nums, const function<bool(int)>& check){
        int left =0,right=nums.size();
        while(left < right){
            int mid = left + (right-left) /2;
            if(check(nums[mid])) {
                right = mid;  //找左边界，向左缩小范围
            }
            else left= mid+1;
        }
        //此时left == right
        //由于每次check成功后都将right = mid,所以当结束后left就是答案
        if(left < nums.size() && check(nums[left]))   return left;
        else return -1;
    }

    //模板 3：寻找最后一个满足条件的位置（右边界/最大值）
    int binaryRight(const std::vector<int>& nums, const function<bool(int)>& check) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (check(nums[mid])) {
                left = mid+1;// 满足条件，尝试找更靠右的
            } else {
                right = mid; // 不满足，缩小范围
            }
        }
        //此时left == right,是第一个不满足check的元素位置
        //由于每次check成功后都将 left = mid+1,所以left-1是答案；
        if(left == 0) return -1;
        else return left -1 ;
    }

    //模板 4：二分切割问题（如两个有序数组找中位数）
}

#endif //ALGORITHMS_SEARCH_H
