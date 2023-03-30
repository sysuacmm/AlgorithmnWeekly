#include <cstdio>
#include <queue>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
const int Inf=2147483647;
struct Pair {
	int id,dist;
	friend bool operator < (Pair a,Pair b) {return a.dist>b.dist;}//按边权排序 
};
struct Graph {
	int u,v,w,nx;
}g[2*M];
int cnt,list[N],dis[N];
bool vis[N];
int n,m,ans;

void Add(int u,int v,int w) {g[++cnt]=(Graph){u,v,w,list[u]};list[u]=cnt;}

bool Prim() {
	priority_queue<Pair> q;
	while (!q.empty()) q.pop();
	q.push((Pair){1,0});
	for (int i=2;i<=n;i++) dis[i]=Inf;
	while (!q.empty()) {
		int u=q.top().id;
		q.pop();
		if (vis[u]) continue;//堆顶端点如果在 U 中则略过不要更新 
		vis[u]=1;//将 u 加入 V' 
		ans+=dis[u];//统计最小生成树的边权和 
		for (int i=list[u];i;i=g[i].nx)
			if (dis[g[i].v]>g[i].w) {//更新 U 外的点到 U 内的点的最小边 
				dis[g[i].v]=g[i].w;
				q.push((Pair){g[i].v,dis[g[i].v]});//将更新数据加入堆中 
			}
	}
	for (int i=1;i<=n;i++)
		if (!vis[i]) return 0;//如果结束算法后有点不在最小生成树中，说明该图不连通 
	return 1;
}

int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,u,v,w;i<=m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		Add(u,v,w),Add(v,u,w);
	}
	if (Prim())	printf("%d",ans);
	else printf("disconnected");
}
