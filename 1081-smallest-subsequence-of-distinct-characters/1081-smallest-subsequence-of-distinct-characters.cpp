class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26);

        for (int i = 0; i < s.size(); i++)
            last[s[i] - 'a'] = i;

        vector<bool> inStack(26, false);
        string st;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (inStack[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   last[st.back() - 'a'] > i) {
                inStack[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            inStack[c - 'a'] = true;
        }

        return st;
    }
};