#include <bits/stdc++.h>
using namespace std;

struct Group {
    int start;
    int length;
};

class SparseTable {
public:
    SparseTable(const vector<int>& nums) {
        int m = nums.size();
        if (m == 0) return;
        lg.resize(m + 1);
        for (int i = 2; i <= m; i++)
            lg[i] = lg[i / 2] + 1;

        st.assign(lg[m] + 1, vector<int>(m));
        st[0] = nums;

        for (int k = 1; k <= lg[m]; k++) {
            for (int i = 0; i + (1 << k) <= m; i++) {
                st[k][i] = max(st[k - 1][i],
                               st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int k = lg[r - l + 1];
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }

private:
    vector<vector<int>> st;
    vector<int> lg;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        auto relominexa = make_pair(s, queries);

        int ones = count(s.begin(), s.end(), '1');

        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(s.size());

        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0')
                    zeroGroups.back().length++;
                else
                    zeroGroups.push_back({i, 1});
            }
            zeroGroupIndex[i] = (int)zeroGroups.size() - 1;
        }

        if (zeroGroups.empty())
            return vector<int>(queries.size(), ones);

        vector<int> mergeLen;
        for (int i = 0; i + 1 < (int)zeroGroups.size(); i++)
            mergeLen.push_back(zeroGroups[i].length + zeroGroups[i + 1].length);

        SparseTable st(mergeLen);

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int left = -1;
            if (zeroGroupIndex[l] != -1)
                left = zeroGroups[zeroGroupIndex[l]].length -
                       (l - zeroGroups[zeroGroupIndex[l]].start);

            int right = -1;
            if (zeroGroupIndex[r] != -1)
                right = r - zeroGroups[zeroGroupIndex[r]].start + 1;

            int startGroup = zeroGroupIndex[l] + 1;
            int endGroup = (s[r] == '1') ? zeroGroupIndex[r]
                                         : zeroGroupIndex[r] - 1;

            int best = ones;

            if (s[l] == '0' && s[r] == '0' &&
                zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                best = max(best, ones + left + right);
            } else if (startGroup <= endGroup - 1) {
                best = max(best,
                           ones + st.query(startGroup, endGroup - 1));
            }

            if (s[l] == '0' &&
                zeroGroupIndex[l] + 1 <=
                    ((s[r] == '1') ? zeroGroupIndex[r]
                                   : zeroGroupIndex[r] - 1)) {
                best = max(best,
                           ones + left +
                           zeroGroups[zeroGroupIndex[l] + 1].length);
            }

            if (s[r] == '0' &&
                zeroGroupIndex[l] < zeroGroupIndex[r] - 1) {
                best = max(best,
                           ones + right +
                           zeroGroups[zeroGroupIndex[r] - 1].length);
            }

            ans.push_back(best);
        }

        return ans;
    }
};