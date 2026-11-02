
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int median = nums[nums.size() / 2];
        long long moves = 0;

        for (int num : nums) {
            moves += abs((long long)num - median);
        }

        return (int)moves;
    }
};