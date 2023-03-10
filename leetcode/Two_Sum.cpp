#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int,int>> nums_pair;
        for(int i = 0; i < nums.size(); i++) nums_pair.push_back(make_pair(nums[i], i));
        sort(nums_pair.begin(), nums_pair.end());
        
        for(int i = 0; i < nums_pair.size(); i++) {
            for(int j = nums_pair.size() - 1; j >= i; j--) {
                int addTwo = nums_pair[i].first + nums_pair[j].first;
                if (addTwo == target) {
                    return vector<int>{nums_pair[i].second, nums_pair[j].second};
                }
                if (addTwo < target) {
                    break;
                }
                else continue;  
            }
        }
        return vector<int>{0} ; // no answer
    }
};
