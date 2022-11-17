//num:物品数量 container:背包空间
void Resolve_KnapSack()
{
    for (int i=1;i<=num;++i) //遍历物品，规划最优选择
    {
        for (int j=1;j<=container;j++)
        {
            if (j>=w[i])
            {
                dp[i][j]=max(dp[i-1][j], dp[i-1][j-w[i]]+p[i]);
            }
            else
            {
                dp[i][j]=dp[i-1][j];
            }
        }
    }
}

