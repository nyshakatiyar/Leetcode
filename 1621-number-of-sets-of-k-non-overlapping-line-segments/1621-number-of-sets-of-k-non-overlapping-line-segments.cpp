class Solution {
public:
    static const long long MOD = 1000000007;

    long long modPow(long long a, long long b) {
        long long result = 1;

        while (b > 0) {
            if (b & 1)
                result = result * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return result;
    }

    int numberOfSets(int n, int k) {

        int N = n + k - 1;
        int R = 2 * k;

        // factorials
        vector<long long> fact(N + 1);
        vector<long long> invFact(N + 1);

        fact[0] = 1;

        for (int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i % MOD;

        // inverse factorials
        invFact[N] = modPow(fact[N], MOD - 2);

        for (int i = N - 1; i >= 0; i--)
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;

        // C(N, R)
        long long ans = fact[N];

        ans = ans * invFact[R] % MOD;
        ans = ans * invFact[N - R] % MOD;

        return ans;
    }
};