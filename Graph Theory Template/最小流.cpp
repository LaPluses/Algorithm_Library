#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 110000
#define S (M-1)
#define T (M-2)
#define SS (M-3)
#define TT (M-4)
#define INF 0x3f3f3f3f
using namespace std;
int n,m,ans;
int degree[M];
namespace Min_Flow{
    struct abcd{
        int to,f,next;
    }table[1001001];
    int head[M],tot=1;
    int dpt[M];
    void Add(int x,int y,int z)
    {
        table[++tot].to=y;
        table[tot].f=z;
        table[tot].next=head[x];
        head[x]=tot;
    }
    void Link(int x,int y,int z)
    {
        Add(x,y,z);
        Add(y,x,0);
    }
    void Restore()
    {
        int i;
        for(i=head[S];i;i=table[i].next)
            table[i].f=table[i^1].f=0;
        for(i=head[T];i;i=table[i].next)
            table[i].f=table[i^1].f=0;
        for(i=head[TT];i;i=table[i].next)
            if(table[i].to==SS)
            {
                ans+=table[i^1].f;
                table[i].f=table[i^1].f=0;
                break;
            }
        Link(S,TT,INF);
        Link(SS,T,INF);
    }
    bool BFS()
    {
        static int q[M];
        int i,r=0,h=0;
        memset(dpt,-1,sizeof dpt);
        dpt[S]=1;q[++r]=S;
        while(r!=h)
        {
            int x=q[++h];
            for(i=head[x];i;i=table[i].next)
                if(table[i].f&&!~dpt[table[i].to])
                {
                    dpt[table[i].to]=dpt[x]+1;
                    q[++r]=table[i].to;
                    if(table[i].to==T)
                        return true;
                }
        }
        return false;
    }
    int Dinic(int x,int flow)
    {
        int i,left=flow;
        if(x==T) return flow;
        for(i=head[x];i&&left;i=table[i].next)
            if(table[i].f&&dpt[table[i].to]==dpt[x]+1)
            {
                int temp=Dinic(table[i].to,min(left,table[i].f));
                left-=temp;
                table[i].f-=temp;
                table[i^1].f+=temp;
            }
        if(left) dpt[x]=-1;
        return flow-left;
    }
}


// 添加一条限制流量必须为C的边
void Special_Link( int u , int v , int c ){
	degree[u] -= c ;
	degree[v] += c;
	Link( u , v , INF );
}

// 添加一条无限制的边
void Normal_Link( int u , int v ){
	Link( u , v , INF );
}


// solve
void Solve(){
	ans = 0;
	for(i=1;i<=n;i++)
    {
        if(degree[i]>0)
            Link(S,i,degree[i]);
        if(degree[i]<0)
            Link(i,T,-degree[i]);
        Link(SS,i,INF);
        Link(i,TT,INF);
    }
    Link(TT,SS,INF);
    while( BFS() )
        Dinic(S,INF);
    Restore();
    while( BFS() )
        ans-=Dinic(S,INF);
    printf("%d\n" , ans);
}