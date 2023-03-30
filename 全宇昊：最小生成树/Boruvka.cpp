#include <cstdio>
#include <cstring>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
struct Graph {
	int u,v,w,nx;
}g[M];
int cnt,list[N],f[N],link[N];//link[i]表示根节点为 i 的并查集（连通块）向外连的最短边 
bool used[M];
int n,m,wans;

int Get_F(int x) {return f[x]==x?x:f[x]=Get_F(f[x]);}

bool Boruvka() {
	bool flag;
	int coa=0;//统计连通块合并次数 
	for (int i=1;i<=n;i++) f[i]=i;//并查集初始化 
	do {
		flag=0;
		for (int i=1;i<=n;i++) link[i]=0;//每次需要重新记录连通块向外连的最短的边 
		for (int i=1,fu,fv;i<=m;i++)
			if (!used[i]&&(fu=Get_F(g[i].u))!=(fv=Get_F(g[i].v))) {//已经在 MST 中的边和连通块内部中的边是不能取的 
				if (!link[fu]||g[link[fu]].w>g[i].w||g[link[fu]].w==g[i].w&&link[fu]>i)//双关键字确定最短边 
					link[fu]=i;
				if (!link[fv]||g[link[fv]].w>g[i].w||g[link[fv]].w==g[i].w&&link[fv]>i)
					link[fv]=i;
			}
		for (int i=1;i<=n;i++)
			if (link[i]&&!used[link[i]]) {//合并连通块，同时标记边 
				flag=1;
				used[link[i]]=1;
				wans+=g[link[i]].w;
				coa++;
				f[Get_F(g[link[i]].u)]=Get_F(g[link[i]].v);
			}
	}
	while (flag);//如果没有再进行合并操作，说明所有图中连通块都已经强连通 
	return coa==n-1;//如果连通块合并次数恰好为 n-1，说明图连通 
}

void Add(int u,int v,int w) {g[++cnt]=(Graph){u,v,w,list[u]};list[u]=cnt;}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,u,v,w;i<=m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		Add(u,v,w);
	}
	Boruvka();
	printf("%d",wans);
}
