//v[i]:i号物品的价值 w[i]:i号物品占用的空间 dn:拆分后物品个数 num:物品数量
int dn;
void divide(int k,int val,int weight)
{
    int x=1;
	while(k-x>=0)
	{
        p[++dn]=x*val;
        w[dn]=x*weight;
        k-=x;x=x*2;
    }
}
int pre()
{
    int k,val,weight;
	for(int i=1;i<=num;++i)
	{
        scanf("%d%d%d",&k,&val,&weight);
        divide(k,val,weight);
    }
}
//接下来是普通的01背包

