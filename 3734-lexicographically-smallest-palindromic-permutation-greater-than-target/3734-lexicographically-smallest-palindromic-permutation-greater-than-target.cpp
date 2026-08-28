class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        // A palindrome can have at most one odd frequency.
        int odd = 0;
        int mid = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = i;
            }
        }

        if (odd > 1)
            return "";

        // Number of characters available for the left half.
        vector<int> halfCnt(26);
        for (int i = 0; i < 26; i++) {
            halfCnt[i] = cnt[i] / 2;
        }

        int halfLen = n / 2;
        string left;

        // Construct palindrome from a given left half.
        auto makePalindrome = [&](const string& L) {
            string res = L;

            if (n % 2)
                res += char('a' + mid);

            for (int i = (int)L.size() - 1; i >= 0; i--) {
                res += L[i];
            }

            return res;
        };

        /*
         * Check whether, after fixing `left`,
         * there exists some completion that is > target.
         *
         * The lexicographically largest completion is obtained
         * by putting the remaining characters in descending order.
         */
        auto possible = [&]() {
            string largest = left;

            // Largest possible remaining left half
            for (int c = 25; c >= 0; c--) {
                largest.append(halfCnt[c], char('a' + c));
            }

            string candidate = makePalindrome(largest);

            return candidate > target;
        };

        // Build the left half greedily.
        for (int pos = 0; pos < halfLen; pos++) {

            bool found = false;

            for (int c = 0; c < 26; c++) {
                if (halfCnt[c] == 0)
                    continue;

                // Try this character.
                left.push_back(char('a' + c));
                halfCnt[c]--;

                // Is there any valid completion?
                if (possible()) {
                    found = true;
                    break;
                }

                // Undo.
                halfCnt[c]++;
                left.pop_back();
            }

            if (!found)
                return "";
        }

        string ans = makePalindrome(left);

        return ans > target ? ans : "";
    }
};