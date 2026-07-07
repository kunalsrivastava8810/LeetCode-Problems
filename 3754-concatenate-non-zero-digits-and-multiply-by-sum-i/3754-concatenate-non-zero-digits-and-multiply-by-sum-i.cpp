class Solution {
public:
    long long sumAndMultiply(int n) {
        int p = 1;
        int x = 0;
        int sum = 0;

        while (n > 0) {
            int d = n % 10;
            if (d != 0) {
                x += p * d;
                p *= 10;
                sum += d;
            }
            n /= 10;
        }

        return 1LL * x * sum;
    }
};