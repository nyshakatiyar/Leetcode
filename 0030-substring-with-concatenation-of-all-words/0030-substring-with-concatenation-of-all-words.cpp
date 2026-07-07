class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty() || s.empty()) return result;

        int wordLen = words[0].size();
        int wordCount = words.size();
        int substringLen = wordLen * wordCount;
        int n = s.size();

        unordered_map<string, int> wordFreq;
        for (string &w : words) wordFreq[w]++;

        // Try starting from each offset inside word length
        for (int i = 0; i < wordLen; i++) {
            int left = i, count = 0;
            unordered_map<string, int> window;

            for (int j = i; j + wordLen <= n; j += wordLen) {
                string word = s.substr(j, wordLen);

                if (wordFreq.count(word)) {
                    window[word]++;
                    count++;

                    // If word appears more than allowed, shrink from left
                    while (window[word] > wordFreq[word]) {
                        string leftWord = s.substr(left, wordLen);
                        window[leftWord]--;
                        left += wordLen;
                        count--;
                    }

                    // If we matched all words
                    if (count == wordCount) {
                        result.push_back(left);
                        // shrink one word to continue
                        string leftWord = s.substr(left, wordLen);
                        window[leftWord]--;
                        left += wordLen;
                        count--;
                    }
                } else {
                    // reset window
                    window.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }
        return result;
    }
};
