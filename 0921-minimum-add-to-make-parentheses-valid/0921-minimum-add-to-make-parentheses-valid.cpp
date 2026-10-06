class Solution {
public:
    int minAddToMakeValid(string s) {
        int balance = 0;
        int ans = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            }
            else {
                if (balance > 0) {
                    balance--;
                }
                else {
                    // Need to insert '('
                    ans++;
                }
            }
        }

        // Need to insert ')' for remaining '('
        ans += balance;

        return ans;
    }
};