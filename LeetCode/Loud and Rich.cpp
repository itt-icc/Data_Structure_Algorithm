class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n=quiet.size();
        /*建立图*/
        vector<vector<int>> graph(n);
        
        /*指向比自己更有钱的*/
        for(auto &edge:richer){
            graph[ edge[1] ].emplace_back(edge[0]);
        }
        
        /*初始化下标列表为-1*/
        vector<int> ans(n,-1);
        
        for(int i=0;i<n;++i){
            dfs(graph,quiet,i,ans);
        }
        return ans;
        
    }
    
    void dfs(vector<vector<int>>& graph, vector<int>& quiet,int idx,vector<int>& ans){
        if(ans[idx]!=-1)//如果已经有值，就返回
            return;
        ans[idx]=idx;//先初始化为自己
        for(int nextidx:graph[idx]){
            dfs(graph,quiet,nextidx,ans);//深度优先遍历自己的邻居
            if(quiet[ans[nextidx]]<quiet[ans[idx]]){//邻居的比自己的小，更新自己
                ans[idx]=ans[nextidx];
            }
        }
    }
};

/*Toplogical*/
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n=quiet.size();
        vector<vector<int>> graph(n);
        vector<int> inDag(n,0);
        
        for(auto & edge:richer){
            graph[edge[0]].emplace_back(edge[1]);
            inDag[edge[1]]++;
        }
        
        vector<int> ans(n);
        queue<int> q;
        for(int i=0;i<n;++i){
            ans[i]=i;
            if(inDag[i]==0){
                q.emplace(i);
            }
        }
        
        while(!q.empty()){
            int idx=q.front();
            q.pop();
            
            for(auto& nextidx:graph[idx]){
                if(quiet[ans[idx]]<quiet[ans[nextidx]]){
                    ans[nextidx]=ans[idx];
                }
                inDag[nextidx]--;
                if(inDag[nextidx]==0){
                    q.emplace(nextidx);
                }
            }
            
        }
        
        return ans;
        
    }
};
