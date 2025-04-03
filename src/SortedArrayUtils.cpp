//
// Created by 25238 on 4/3/2025.
//
#include <cmath>
#include "array/SortedArrayUtils.h"
#include "array/SortedArrayPairUtils.h"


double SortedArrayPairUtils::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int n1= nums1.size();
    int n2= nums2.size();
    if(n1>n2) return findMedianSortedArrays(nums2,nums1); //找小的数组更合适

    int k = (n1 + n2 + 1)/2; //无论合并后的数组是奇偶，k一定是左边最大；[数量，非下标]

    int left=0,right = n1; //左闭右开
    while(left < right){
        //构造分界线
        int m = left + (right-left)/2; //猜测在nums1中取m个元素放到左边
        int n = k-m; //则nums2中取n个元素放到左边

        //由于m,n是数量，以1开始。所以nums1[m]是最小右元素，nums2[n]是最小右边元素
        if(nums1[m] < nums2[n-1]){
            left = m+1;
        }
        else{
            right = m;
        }
    }
    int m1 = left;
    int m2 = k - m1;

    double maxLeft = max(
            m1 == 0 ? -INFINITY : nums1[m1 - 1],
            m2 == 0 ? -INFINITY : nums2[m2 - 1]
    );

    if ((n1 + n2) % 2 == 1) return maxLeft;

    double minRight = min(
            m1 == n1 ? INFINITY : nums1[m1],
            m2 == n2 ? INFINITY : nums2[m2]
    );

    return (maxLeft + minRight) / 2.0;
}
