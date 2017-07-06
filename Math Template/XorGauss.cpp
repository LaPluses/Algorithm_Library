#include <bits/stdc++.h>

using namespace std;

int solve(matrix mat , int n , int m){
	int cur = 0;
	for(int i = 0 ; i < m && cur < n ; ++ i){
		int r = -1;
		for(int j = cur ; j < n ; ++ j) if(mat[j][i]) {r = j ; break;}
		if(r==-1) continue;
		if(r!=cur) for(int j = 0 ; j <= m ; ++ j) swap(mat[cur][j],mat[r][j]);
		for(int j = 0 ; j < n ; ++ j)
			if(mat[j][i] && j != cur)
				for(int v = i ; v <= m ; ++ v)
					mat[j][v] ^= mat[cur][v];
		cur++;
	}
	return m - cur;
}

int main(int argc,char *argv[]){


	return 0;
}