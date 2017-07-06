#include <iostream>
#include <cstdio>

using namespace std;

struct RMQ{
	const static int RMQ_size = 1500;
	int n;
	int ArrayMax[RMQ_size][21];
	int ArrayMin[RMQ_size][21];

	/*

	    mm[0]=-1;
	    for(int i=1;i<=n;i++){
	        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
	    }
	    int k = mm[len];
	    return max( dp[l][k] , dp[r-(1<<k)+1][k] )
	*/

	void build_rmq(){
		for(int j = 1 ; (1<<j) <= n ; ++ j)
			for(int i = 0 ; i + (1<<j) - 1 < n ; ++ i){
				ArrayMax[i][j]=max(ArrayMax[i][j-1],ArrayMax[i+(1<<(j-1))][j-1]);
				ArrayMin[i][j]=min(ArrayMin[i][j-1],ArrayMin[i+(1<<(j-1))][j-1]);
			}
	}

	int QueryMax(int L,int R){
		int k = 0;
		while( (1<<(k+1)) <= R-L+1) k ++ ;
		return max(ArrayMax[L][k],ArrayMax[R-(1<<k)+1][k]);
	}

	int QueryMin(int L,int R){
		int k = 0;
		while( (1<<(k+1)) <= R-L+1) k ++ ;
		return min(ArrayMin[L][k],ArrayMin[R-(1<<k)+1][k]);
	}


	void init(int * a,int n){
		this->n = n ;
		for(int i = 0 ; i < n ; ++ i) ArrayMax[i][0] = ArrayMin[i][0] = a[i];
		build_rmq();
	}
    
}solver;

int main(int argc,char *argv[]){
	
	return 0;
}