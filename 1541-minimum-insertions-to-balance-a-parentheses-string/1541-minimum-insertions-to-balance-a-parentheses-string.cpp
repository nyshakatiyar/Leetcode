class Solution {
public:
    int minInsertions(string s) {
        int ans = 0;
        int open = 0;

        for (int i = 0; i < s.length(); i++) {

            if (s[i] == '(') {
                open++;
            }
            else {
                // We need two ')' for every '('
                if (i + 1 < s.length() && s[i + 1] == ')') {
                    // Found a pair: "()"
                    i++;
                }
                else {
                    // Only one ')' exists, so insert another ')'
                    ans++;
                }

                // This ')' pair needs a preceding '('
                if (open > 0) {
                    open--;
                }
                else {
                    // Insert '('
                    ans++;
                }
            }
        }

        // Every remaining '(' needs two ')'
        ans += 2 * open;

        return ans;
    }
};