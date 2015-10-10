/*
HDU 1044 Collect More Jewels
走迷宫，问在规定时间内从起点到终点最多可以收集到宝物的价值是多少。

先bfs找出所有宝物及起点和终点这些位置之间的最短距离，再起点dfs最大。
加个剪枝，如果已经拿到所有宝物了，就不再搜索。


AC G+ 31MS 560K
*/
#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int W, H, L, M;//区域是H行W列的，L是时间限制，M是宝石的数量
int val[60];//宝石的价值，1-M
char map[60][60];
bool used[60][60];//BFS时访问标记
bool vis[60];//dfs时访问标记
int step[60][60];
int ans;//结果
int sum;//所有的宝石的价值总和
int move11[4][2] = { { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } };
int dis[60][60];//记录初始位置、各宝石和出口两两间的距离
queue<int>q;

//从(x1,y1)点到其它点的距离，s(0-M+1)是该点编号，0表示初始位置
//M+1表示出口，1-M表示第i个宝物堆
void bfs(int x1, int y1, int s)
{
	while (!q.empty())q.pop();
	memset(used, false, sizeof(used));
	memset(step, 0, sizeof(step));
	int u = x1*W + y1;
	q.push(u);
	used[x1][y1] = true;
	step[x1][y1] = 0;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		int x = u / W;
		int y = u%W;
		for (int i = 0;i<4;i++)
		{
			int xx = x + move11[i][0];
			int yy = y + move11[i][1];
			if (xx<0 || xx >= H || yy<0 || yy >= W)continue;
			if (used[xx][yy] || map[xx][yy] == '*')continue;

			used[xx][yy] = true;
			step[xx][yy] = step[x][y] + 1;
			if (map[xx][yy] == '@')dis[s][0] = step[xx][yy];
			else if (map[xx][yy] == '<') dis[s][M + 1] = step[xx][yy];
			else if (map[xx][yy] >= 'A'&&map[xx][yy] <= 'J')
				dis[s][map[xx][yy] - 'A' + 1] = step[xx][yy];
			q.push(xx*W + yy);
		}
	}
}

//dfs,s表示当前点，value表示获得的价值，time表示花费的时间
void dfs(int s, int value, int time)
{
	if (time>L)return;//超出限制时间
	if (ans == sum) return;//已经得到了最大的价值，剪枝(没有这个会超时）
	if (s>M)
	{
		if (value>ans)ans = value;
		return;
	}
	for (int i = 0;i <= M + 1;i++)
	{
		if (dis[s][i] == 0 || vis[i])continue;
		vis[i] = true;
		dfs(i, value + val[i], time + dis[s][i]);
		vis[i] = false;
	}
}
int main()
{
	// freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--)
	{
		memset(dis, 0, sizeof(dis));
		iCase++;
		scanf("%d%d%d%d", &W, &H, &L, &M);
		sum = 0;
		ans = -1;
		for (int i = 1;i <= M;i++)
		{
			scanf("%d", &val[i]);
			sum += val[i];
		}
		val[0] = val[M + 1] = 0;//这个很重要啊，WR到死啊
		char temp;
		for (int i = 0;i<H;i++)
			for (size_t j = 0; j < W; j++)
			{
				cin >> temp;
				map[i][j] = temp;
				/*scanf("%c", &map[H][W]);*/
			}
		for (int i = 0;i<H;i++)
			for (int j = 0;j<W;j++)
			{
				if (map[i][j] == '@') bfs(i, j, 0);
				else if (map[i][j] == '<') bfs(i, j, M + 1);
				else if (map[i][j] >= 'A'&&map[i][j] <= 'J')
					bfs(i, j, map[i][j] - 'A' + 1);

			}
		memset(vis, false, sizeof(vis));
		vis[0] = true;
		dfs(0, 0, 0);

		printf("Case %d:\n", iCase);
		if (ans >= 0)printf("The best score is %d.\n", ans);
		else printf("Impossible\n");

		if (T>0)printf("\n");

	}
	return 0;
}