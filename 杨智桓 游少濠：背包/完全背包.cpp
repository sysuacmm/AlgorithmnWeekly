//num:物品数量 container:背包空间
void Resolve_KnapSack()
{
    for(int j=1;j<=container;++j)
	{
		dp[j]=dp[j-1];
        for(int i=1;i<=num;++i) //遍历物品，规划最优选择
        {
            if(j>=w[i])
            {
                dp[j]=max(dp[j],dp[j-w[i]]+p[i]);
            }
        }
    }
}
