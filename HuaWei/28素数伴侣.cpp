#include "stdafx.h"
#include "HuaWei.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cctype>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

vector<int> G[105];

bool flag[105];
int pre[105];

bool dfs(int k) 
{
	int x;
	for (int i = 0;i<G[k].size();i++) 
	{
		x = G[k][i];
		if (flag[x]) continue;
		flag[x] = true;
		if ((pre[x] == 0) || dfs(pre[x])) 
		{
			pre[x] = k;
			return true;
		}
	}
	return false;
}

const int PRIMESIZE = 80000;
bool isprime[PRIMESIZE];
int nums[105];

int test_28() 
{
	memset(isprime, 1, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	for (int i = 4;i < PRIMESIZE;i += 2)
	{
		isprime[i] = false;
	}
	for (int i = 3;i*i < PRIMESIZE;i += 2)
	{
		if (isprime[i])
		{
			for (int j = i*i;j < PRIMESIZE;j += 2 * i)
			{
				isprime[j] = false;
			}
		}
	}
	int n;
	while (cin>>n) 
	{
		for (int i = 1;i <= n;i++) 
		{
			cin >> nums[i];
		}
		for (int i = 1;i <= n;++i) 
		{
			for (int j = i + 1;j <= n;++j) 
			{
				if (isprime[nums[i] + nums[j]]) 
				{
					//大于2的素数一定=偶+奇，全部记录到偶数中
					//邻接表
					(nums[i] & 1) ? G[i].push_back(j) : G[j].push_back(i);
				}
			}
		}

		memset(pre, 0, sizeof(pre));
		int ans = 0;
		//深度优先遍历邻接表
		for (int i = 1;i <= n;i++) 
		{
			memset(flag, false, sizeof(flag));
			if (dfs(i)) ans++;
		}
		cout << ans << endl;

		for (int i = 1;i <= n;++i) 
		{
			G[i].clear();
		}
	}
	return 0;
}