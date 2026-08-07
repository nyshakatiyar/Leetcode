#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int e2=0,e3=0,e5=0,e7=0;
    vector<vector<int>> dp;
    // digit -> (a,b,c,d) exponents contributed for primes 2,3,5,7
    array<array<int,4>,10> dprop{};

    bool feasible(long long length, int n2,int n3,long long n5,long long n7){
        long long mand = n5+n7;
        if(mand > length) return false;
        if(n2>e2) n2=e2; // safety clamp, shouldn't exceed
        if(n3>e3) n3=e3;
        return (long long)dp[n2][n3] <= (length - mand);
    }

    string greedyFill(long long length, int n2,int n3,long long n5,long long n7){
        string res;
        res.reserve((size_t)length);
        int c2=n2,c3=n3; long long c5=n5,c7=n7;
        for(long long pos=0; pos<length; pos++){
            long long rem = length - pos - 1;
            for(int d=1; d<=9; d++){
                int a=dprop[d][0], b=dprop[d][1], c=dprop[d][2], dd=dprop[d][3];
                int nn2 = max(c2-a,0), nn3 = max(c3-b,0);
                long long nn5 = max((long long)c5-c,0LL), nn7 = max((long long)c7-dd,0LL);
                if(feasible(rem, nn2,nn3,nn5,nn7)){
                    res.push_back('0'+d);
                    c2=nn2; c3=nn3; c5=nn5; c7=nn7;
                    break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        dprop[1]={0,0,0,0};
        dprop[2]={1,0,0,0};
        dprop[3]={0,1,0,0};
        dprop[4]={2,0,0,0};
        dprop[5]={0,0,1,0};
        dprop[6]={1,1,0,0};
        dprop[7]={0,0,0,1};
        dprop[8]={3,0,0,0};
        dprop[9]={0,2,0,0};

        long long tt=t;
        for(int p : {2,3,5,7}){
            int *cnt;
            if(p==2) cnt=&e2; else if(p==3) cnt=&e3; else if(p==5) cnt=&e5; else cnt=&e7;
            while(tt % p == 0){ tt/=p; (*cnt)++; }
        }
        if(tt != 1) return "-1";

        // combo digits (2,3,4,6,8,9) as (a,b) pairs for primes 2,3
        vector<pair<int,int>> combo = {{1,0},{0,1},{2,0},{1,1},{3,0},{0,2}};

        dp.assign(e2+1, vector<int>(e3+1, 0));
        for(int s=1; s<=e2+e3; s++){
            int iLo = max(0, s-e3), iHi = min(e2, s);
            for(int i=iLo; i<=iHi; i++){
                int j = s-i;
                int best = INT_MAX;
                for(auto &pr : combo){
                    int a=pr.first,b=pr.second;
                    int ni = max(i-a,0), nj = max(j-b,0);
                    if(ni==i && nj==j) continue;
                    int cand = dp[ni][nj] + 1;
                    if(cand < best) best = cand;
                }
                dp[i][j] = (best==INT_MAX)?0:best;
            }
        }

        long long minLen = (long long)e5 + e7 + dp[e2][e3];
        long long L = (long long)num.size();
        vector<int> digits(L);
        for(long long i=0;i<L;i++) digits[i]=num[i]-'0';

        long long p = L;
        for(long long idx=0; idx<L; idx++){
            if(num[idx]=='0'){ p = idx; break; }
        }

        if(p == L){ // zero-free
            long long te2=0,te3=0,te5=0,te7=0;
            for(int dch : digits){
                te2+=dprop[dch][0]; te3+=dprop[dch][1];
                te5+=dprop[dch][2]; te7+=dprop[dch][3];
            }
            if(te2>=e2 && te3>=e3 && te5>=e5 && te7>=e7) return num;
        }

        if(minLen > L){
            return greedyFill(minLen, e2,e3,e5,e7);
        }

        long long upper = (p < L) ? p : (L-1);
        vector<long long> preE2(upper+2,0), preE3(upper+2,0), preE5(upper+2,0), preE7(upper+2,0);
        for(long long idx=0; idx<=upper; idx++){
            int a=dprop[digits[idx]][0], b=dprop[digits[idx]][1];
            int c=dprop[digits[idx]][2], dd=dprop[digits[idx]][3];
            preE2[idx+1]=preE2[idx]+a;
            preE3[idx+1]=preE3[idx]+b;
            preE5[idx+1]=preE5[idx]+c;
            preE7[idx+1]=preE7[idx]+dd;
        }

        string ans = "";
        bool found = false;
        for(long long i=upper; i>=0 && !found; i--){
            long long pe2=preE2[i], pe3=preE3[i], pe5=preE5[i], pe7=preE7[i];
            for(int d=digits[i]+1; d<=9; d++){
                int a=dprop[d][0], b=dprop[d][1], c=dprop[d][2], dd=dprop[d][3];
                int n2 = (int)max((long long)e2-(pe2+a), 0LL);
                int n3 = (int)max((long long)e3-(pe3+b), 0LL);
                long long n5 = max((long long)e5-(pe5+c), 0LL);
                long long n7 = max((long long)e7-(pe7+dd), 0LL);
                long long rem = L - i - 1;
                if(feasible(rem, n2,n3,n5,n7)){
                    ans = num.substr(0,i) + char('0'+d) + greedyFill(rem, n2,n3,n5,n7);
                    found = true;
                    break;
                }
            }
        }

        if(found) return ans;
        return greedyFill(L+1, e2,e3,e5,e7);
    }
};