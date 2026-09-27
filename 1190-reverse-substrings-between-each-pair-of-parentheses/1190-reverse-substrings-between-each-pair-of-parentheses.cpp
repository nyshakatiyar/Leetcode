class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;

        st.push("");

        for (char c : s) {

            if (c == '(') {
                // Start a new level
                st.push("");
            }
            else if (c == ')') {
                // Get current substring
                string curr = st.top();
                st.pop();

                // Reverse it
                reverse(curr.begin(), curr.end());

                // Add it to the previous level
                st.top() += curr;
            }
            else {
                // Normal character
                st.top() += c;
            }
        }

        return st.top();
    }
};