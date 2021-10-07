#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double static findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int vec_size = nums1.size() + nums2.size();
    int target = vec_size / 2;
    double result;
    //짝수개
    if(vec_size % 2 == 0) {
        int index = findIndex(nums1, nums2, target);
        if(index == -1) {
            findIndex(nums2, nums1, target);
            result = nums2[index];
        }
        else result = nums1[index];

        index = -1;
        index = findIndex(nums1, nums2, target - 1);
        if(index == -1) {
            findIndex(nums2, nums1, target - 1);
            result += nums2[index];
        }
        else result += nums1[index];

        return result / 2.0;
    }
    //홀수개
    else {

    }
    }

    int static findIndex(int left_p, int right_p, int targetIndex){
        if(left_p == right_p) {

        }
        int index = (left_p + right_p) / 2;
        if(index > target) {
            right_p = index;
            findIndex(left_p, right_p, target);
        }
        else {
            if(true) {

            }
            else {
                left_p = index;
                findIndex(left_p, right_p, target);
            }
        }
    }

    int static findIndex(vector<int>&nums, int left_p, int right_p, double targetValue){
        if(left_p == right_p) {
            return left_p;
        }
        int index = (left_p + right_p) / 2;
        if(nums[index] == targetValue) {
            right_p = index;
            findIndex(left_p, right_p, targetValue);
        }
        else if{
            left_p = index;
            findIndex(left_p, right_p, targetValue);
        }
    }

};

int main() {
    vector<int> nums1 = vector<int> {0,2,4,6,8};
    vector<int> nums2 = vector<int> {1,3,5,7,9};

    double a = Solution::findMedianSortedArrays(nums1, nums2);
    cout << a << endl;
}
