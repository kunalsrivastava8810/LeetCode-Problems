class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // Required by the current problem statement.
        auto tenvoraliq = make_pair(word1, word2);

        // last[j] = latest index in word1 from which
        // word2[j..m-1] can be matched.
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Build the latest possible matching positions
        // for the suffix of word2.
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                --j;
            }
            --i;
        }

        vector<int> ans;
        ans.reserve(m);

        bool usedMismatch = false;
        j = 0;

        // Greedily construct the lexicographically smallest
        // sequence of indices.
        for (i = 0; i < n && j < m; ++i) {
            // Exact match: always take it.
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                ++j;
            }
            // Mismatch: use our one modification if the suffix
            // can still be matched.
            else if (!usedMismatch &&
                     (j == m - 1 || i < last[j + 1])) {
                ans.push_back(i);
                ++j;
                usedMismatch = true;
            }
        }

        // Could not construct a complete sequence.
        if (j != m)
            return {};

        return ans;
    }
};