/*
HDU 1044 Collect More Jewels
���Թ������ڹ涨ʱ���ڴ���㵽�յ��������ռ�������ļ�ֵ�Ƕ��١�

��bfs�ҳ����б��Ｐ�����յ���Щλ��֮�����̾��룬�����dfs���
�Ӹ���֦������Ѿ��õ����б����ˣ��Ͳ���������


AC G+ 31MS 560K
*/
#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int W, H, L, M;//������H��W�еģ�L��ʱ�����ƣ�M�Ǳ�ʯ������
int val[60];//��ʯ�ļ�ֵ��1-M
char map[60][60];
bool used[60][60];//BFSʱ���ʱ��
bool vis[60];//dfsʱ���ʱ��
int step[60][60];
int ans;//���
int sum;//���еı�ʯ�ļ�ֵ�ܺ�
int move11[4][2] = { { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } };
int dis[60][60];//��¼��ʼλ�á�����ʯ�ͳ���������ľ���
queue<int>q;

//��(x1,y1)�㵽������ľ��룬s(0-M+1)�Ǹõ��ţ�0��ʾ��ʼλ��
//M+1��ʾ���ڣ�1-M��ʾ��i�������
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

//dfs,s��ʾ��ǰ�㣬value��ʾ��õļ�ֵ��time��ʾ���ѵ�ʱ��
void dfs(int s, int value, int time)
{
	if (time>L)return;//��������ʱ��
	if (ans == sum) return;//�Ѿ��õ������ļ�ֵ����֦(û������ᳬʱ��
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
		val[0] = val[M + 1] = 0;//�������Ҫ����WR������
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