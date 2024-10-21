#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class SolutionSeven{
private:
    unordered_map<int,vector<int>> adj; //alimentas el unordered_map desde la f(x) main
    int dp[1<<15];

    int solve(int mask, int n, int k){ //prrimer nodo, total de cursos, paralelos
        if(mask==(1<<n)-1) return 0;
        if(dp[mask]!=-1) return dp[mask];
        vector<int> indegree(n,0); //para cada nodo
        for(int i=0; i<n; i++){
            if(!(mask & (1<<i))){
                for(auto& child: adj[i]){
                    indegree[child]++;
                }
            }
        }

        int coursesToTake=0;
        for(int i=0; i<n; i++){
            if(indegree[i]==0 && (mask & (1<<i))==0){
                coursesToTake |= (1<<i);
            }
        }

        int coursesCnt=__builtin_popcount(coursesToTake); //cantidad de unos
        int ans=INT_MAX;

        if(coursesCnt>k){ //mayores a la cantidade cursos iguales
            for(int i=coursesToTake; i>=0; i--){
                int combination=(i & coursesToTake); 
                int cnt=__builtin_popcount(combination);
                if(cnt!=k) continue;
                ans=min(ans, 1+solve(mask|combination,n,k));
            }
            return dp[mask]=ans;
        }
        return dp[mask]=1+solve(mask|coursesToTake,n,k);
    }
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        for(auto& x: relations){
            adj[x[0]-1].push_back(x[1]-1);
        }
        memset(dp,-1,sizeof(dp));//array, llenado, calculo del tamaño bytes
        return solve(0,n,k);
    }
};

int main(){
    return 0;
}