long long rec(vector<vector<int>> &idx,vector<vector<long long>> &dp,vector<int>&B,int start, int end){
    long long ans = dp[start][end]; 
    // cout << ans<<"  "<<start << "  "<< end<< endl;
    if(end<=start+1){
        return 0;
    }
    else if(ans!=0){
        return ans;
    }
    ans = LLONG_MAX;
    for(int i=start+1;i<end;i++){
        long long t = B[end]-B[start] + rec(idx,dp,B,start,i) + rec(idx,dp,B,i,end);
        if(t<ans){
            ans = t;
            idx[start][end] = i;
        }   
    }
    dp[start][end] = ans;
    return ans;
}
void formans(vector<vector<int> >&idx,vector<int> &ans,int start,int end,vector<int> &B){
    if(start>=end-1){
        return;
    }
    ans.push_back(B[idx[start][end]]);
    formans(idx,ans,start,idx[start][end],B);
    formans(idx,ans,idx[start][end],end,B);
}
vector<int> Solution::rodCut(int A, vector<int> &B) {
    vector <int> S = B;
    S.push_back(A);
    S.insert(S.begin(),0);
    int n = S.size();
    vector<long long>X(n,0);
    vector<vector<long long>> dp(n,X);
    vector<int> Y(n,0);
    vector<vector<int>> idx(n,Y);
    long long t = rec(idx,dp,S,0,n-1);
    vector<int> ans;
    formans(idx,ans,0,n-1,S);
    return ans;
}