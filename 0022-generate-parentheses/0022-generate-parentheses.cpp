#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }

private:
    void backtrack(vector<string>& result, string current, int open, int close, int maxPairs) {
        if (current.size() == maxPairs * 2) {
            result.push_back(current);
            return;
        }
        if (open < maxPairs) {
            backtrack(result, current + "(", open + 1, close, maxPairs);
        }
        if (close < open) {
            backtrack(result, current + ")", open, close + 1, maxPairs);
        }
    }
};
