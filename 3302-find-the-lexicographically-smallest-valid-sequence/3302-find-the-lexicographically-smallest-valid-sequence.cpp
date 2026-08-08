class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        vector<int> right(m, -1);

        int j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; i--) {
            if (word1[i] == word2[j]) {
                right[j] = i;
                j--;
            }
        }

        vector<int> ans;
        int i = 0;
        bool used = false;

        for (int p = 0; p < m; p++) {
            while (i < n) {
                bool ok = false;

                if (word1[i] == word2[p]) {
                    ok = true;
                } else if (!used) {
                    if (p == m - 1 || (right[p + 1] != -1 && right[p + 1] > i))
                        ok = true;
                }

                if (ok) {
                    if (word1[i] != word2[p]) used = true;
                    ans.push_back(i);
                    i++;
                    break;
                }

                i++;
            }

            if ((int)ans.size() != p + 1)
                return {};
        }

        return ans;
    }
};