class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> arr(n);
        for(int i=0;i<n;i++) arr[i] = {nums[i], i};
        sort(arr.begin(), arr.end());
        
        vector<int> valSorted(n), origIdx(n), pos(n);
        for(int i=0;i<n;i++){
            valSorted[i]=arr[i].first;
            origIdx[i]=arr[i].second;
            pos[origIdx[i]] = i;
        }
        
        // hi[i] = farthest sorted position directly reachable from i
        vector<int> hi(n);
        int j=0;
        for(int i=0;i<n;i++){
            if(j<i) j=i;
            while(j+1<n && valSorted[j+1]-valSorted[i]<=maxDiff) j++;
            hi[i]=j;
        }
        
        // connected components based on consecutive gaps
        vector<int> comp(n);
        comp[0]=0;
        for(int i=1;i<n;i++){
            comp[i] = comp[i-1] + ((valSorted[i]-valSorted[i-1] <= maxDiff) ? 0 : 1);
        }
        
        int LOG = 1;
        while((1<<LOG) < n) LOG++;
        LOG++; // safety margin
        
        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = hi;
        for(int k=1;k<LOG;k++){
            for(int i=0;i<n;i++){
                up[k][i] = up[k-1][ up[k-1][i] ];
            }
        }
        
        vector<int> ans;
        ans.reserve(queries.size());
        for(auto& qy : queries){
            int u=qy[0], v=qy[1];
            if(u==v){ ans.push_back(0); continue; }
            int p=pos[u], q=pos[v];
            if(p>q) swap(p,q);
            if(comp[p]!=comp[q]){ ans.push_back(-1); continue; }
            if(hi[p]>=q){ ans.push_back(1); continue; }
            
            int cur=p, steps=0;
            for(int k=LOG-1;k>=0;k--){
                if(up[k][cur] < q){
                    cur = up[k][cur];
                    steps += (1<<k);
                }
            }
            steps += 1; // final jump crosses q
            ans.push_back(steps);
        }
        return ans;
    }
};