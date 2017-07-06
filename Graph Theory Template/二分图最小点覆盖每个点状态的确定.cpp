#include <bits/stdc++.h>
#define rep(a,b,c) for(int (a)=(b);(a)<=(c);++(a))
#define drep(a,b,c) for(int (a)=(b);(a)>=(c);--(a))
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define two(x) (1<<(x))
#define clr(x,y) memset((x),(y),sizeof((x)))
#define dbg(x) cout << #x << "=" << x << endl;
#define lowbit(x) ((x)&(-x))
const int mod = 1e9 + 7;
int mul(int x,int y){return 1LL*x*y%mod;}
int qpow(int x , int y){int res=1;while(y){if(y&1) res=mul(res,x) ; y>>=1 ; x=mul(x,x);} return res;}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
using namespace std;
const int maxn = 1e3 + 15;
vector < int > LE[maxn] , RE[maxn] ;
int linkL[maxn],linkR[maxn],N,M,K,ansL[maxn],ansR[maxn],vis[maxn];

int DFS( int x ){
	for( auto v : LE[x] ){
		if( vis[v] ) continue;
		vis[v] = 1;
		if( linkR[v] == -1 || DFS( linkR[v] ) ){
			linkL[x] = v , linkR[v] = x;
			return 1;
		}
	}
	return 0;
}

int main( int argc , char * argv[] ){
	freopen("in.txt","r",stdin);
	N=read(),M=read(),K=read();
	rep(i,1,K){
		int u = read() , v = read();
		LE[u].pb( v ); RE[v].pb( u );
	}
	clr( linkL , -1 ) ; clr( linkR , -1 );
	// 进行二分图最大匹配
	rep(i,1,N){
		rep(j,1,M) vis[j]=0;
		DFS( i );
	}
	// 初始认为所有匹配的点都是 E , 对于未匹配点，加入队列中
	queue < int > Q;
	rep(i,1,N) if(~linkL[i]) ansL[i] = 1; else Q.push( i );
	rep(i,1,M) if(~linkR[i]) ansR[i] = 1; else Q.push( i + N );
	// 对于一定在最小点覆盖的点满足的条件即 ： 这个匹配点连接的所有边中存在非匹配点 , 即，如果存在的话，就必须选这个点
	// 开始跑
	// 注意队列中的点都是未匹配点
	while(!Q.empty()){
		int x = Q.front() ; Q.pop();
		// 是左边的点
		if( x <= N ){
			for( auto v : LE[x] ){
				// 右边的点是一个匹配点同时没有check过
				if( ~linkR[v] && ansR[v] != 2 ){
					ansR[v] = 2; // 这个点必选
					ansL[linkR[v]] = 0; // 那么他所对应的左边的匹配点一定不选
					Q.push( linkR[v] ); // 左边那个点不选了，加入到队列中
				}
			}
		}else{
			for( auto v : RE[x - N] ){
				// 左边的点是一个匹配点同时没有check过
				if( ~linkL[v] && ansL[v] != 2 ){
					ansL[v] = 2; // 这个点必选
					ansR[linkL[v]] = 0; // 那么他所对应的右边的匹配点一定不选
					Q.push( linkL[v] + N ); // 左边那个点不选了，加入到队列中
				}
			}
		}
	}
	rep(i,1,N) if(ansL[i] == 0) putchar('N') ; else if( ansL[i] == 1 ) putchar('E') ; else putchar('A');
	puts("");
	rep(i,1,M) if(ansR[i] == 0) putchar('N') ; else if( ansR[i] == 1 ) putchar('E') ; else putchar('A');
	puts("");
	return 0;
}