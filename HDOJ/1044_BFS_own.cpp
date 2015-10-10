#include <queue>
#include <vector>
#include <iostream>
//#include "TTimer.h"
using namespace std;

#define MAXN 50

char path[MAXN][MAXN];
bool visited[MAXN][MAXN];

bool visited2[28];
unsigned matrix[28][28];
int postion_xy[28][2];

int g_col, g_row, g_depth;

struct Node
{
	int x, y;
	int depth;
	Node() {};
	Node(int p_x, int p_y, int d)
	{
		x = p_x;
		y = p_y;
		depth = d;
	}
};

struct Node2
{
	int x, treasure, depth;
	Node2(int p_x, int jewel, int d)
	{
		x = p_x;
		treasure = jewel;
		depth = d;
	}
};
int directions[4][2]{ { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

//@brief: calculate the shortest path matrix[num][*]
//@param x_begin: the col of begin position
//@param y_begin: the row of begin position
//@param num: the calculate index.
//>[*]:-1 marks a wall, into which you can not move;
//>[.]:0 marks an empty space, into which you can move;
//>[@]:-3 marks the initial position of the adventurer;
//>[<]:-2 marks the exit stairs;
//>[A]:unsigned value - [J] marks the jewels.
void BFS(int x_begin, int y_begin, int num, int num_trea)
{
	Node begin_node(x_begin, y_begin, 0);
	queue<Node> que;
	que.push(begin_node);
	visited[y_begin][x_begin] = true;
	int result = g_depth;
	Node last_one;

	while (!que.empty())
	{
		int x, y;
		last_one = que.front();
		que.pop();
		visited[last_one.y][last_one.x] = true;
		for (size_t i = 0; i < 4; i++)
		{
			x = last_one.x + directions[i][0];
			y = last_one.y + directions[i][1];
			//超过矩阵范围
			if (x < 0 || x >= g_col || y < 0 || y >= g_row || visited[y][x] == true || path[y][x] == '*')
			{
				continue;
			}
			//又回到该点
			if (((num == 0) && path[y][x] == '@') || ((num == num_trea + 1) && path[y][x] == '<') || ((num > 0) && (num <= num_trea) && path[y][x] == 'A' - 1 + num))
			{
				continue;
			}
			//到达终点
			if (path[y][x] >= 'A' && path[y][x] <= 'Z')
			{
				matrix[num][path[y][x] - 'A' + 1] = last_one.depth + 1;// < matrix[num][path[y][x] - 'A' + 1] ? last_one.depth + 1 : matrix[num][path[y][x] - 'A' + 1];
			}
			else if (path[y][x] == '@')
			{
				matrix[num][0] = last_one.depth + 1;// < matrix[num][path[y][x] - 'A' + 1] ? last_one.depth + 1 : matrix[num][0];
			}
			else if (path[y][x] == '<')
			{
				matrix[num][num_trea + 1] = last_one.depth + 1;// < matrix[num][path[y][x] - 'A' + 1] ? last_one.depth + 1 : matrix[num_trea + 1][1];
			}
			Node newone(x, y, last_one.depth + 1);
			que.push(newone);
			visited[y][x] = true;

		}
	}
	//return result;
}

//@brief: calculate the shortest path 
//@param x_begin: the col of begin position
//@param y_begin: the row of begin position
//@param x_end: the col of end position
//@param y_end: the row of end position
//@param bound: the bound value of the matrix
//@param treasures: each treasure of 'A' .. 'Z'
//@param sum_treasure: total treasure
//@return: the length of the shortest path
//>[*]:-1 marks a wall, into which you can not move;
//>[.]:0 marks an empty space, into which you can move;
//>[@]:-3 marks the initial position of the adventurer;
//>[<]:-2 marks the exit stairs;
//>[A]:unsigned value - [J] marks the jewels.
int BFS2(int x_begin, int x_end, int bound, vector<int> treasures, int sum_treause)
{
	Node2 begin_node(x_begin, -1, 0);
	queue<Node2> que;
	que.push(begin_node);
	visited2[x_begin] = true;
	int result = -1;

	while (!que.empty())
	{
		int x;
		Node2 last_one = que.front();
		que.pop();
		visited2[last_one.x] = false;
		for (size_t i = 1; i <= bound; i++)//去掉0,0是起点
		{
			x = i;
			//已经访问
			if (last_one.x == x || visited2[x] == true)
			{
				continue;
			}

			//>[<] marks the exit stairs;
			if (x == x_end)
			{
				result = last_one.treasure > result ? last_one.treasure : result;
				continue;
			}

			if (matrix[last_one.x][x] + last_one.depth < g_depth)
			{
				Node2 newone(x, last_one.treasure + treasures.at(x - 2), last_one.depth + matrix[last_one.x][x]);
				que.push(newone);
				visited2[x] = true;
			}

		}
	}
	if (result >= 0)
		return result + 1;
	else
		return result;
}
int ans;







void dfs(int s, int value, int time, int sum_treasure, int jew_num, vector<int> treasures)
//(int x_begin, int x_end, int bound, vector<int> treasures, int sum_treause)
{
	if (time > g_depth)
		return;//超出限制时间
	if (ans == sum_treasure) 
		return;//已经得到了最大的价值，剪枝(没有这个会超时）
	if (s>jew_num)
	{
		if (value > ans)
			ans = value;
		return;
	}
	for (int i = 0;i <= jew_num + 1;i++)
	{
		if (matrix[s][i] > g_depth || visited2[i])
			continue;
		visited2[i] = true;
		dfs(i, value + treasures[i], time + matrix[s][i], sum_treasure, jew_num, treasures);
		visited2[i] = false;
	}
}
int main()
{

	int numcase;
	cin >> numcase;

	for (size_t i = 0; i < numcase; i++)
	{
		int max_index = 1;
		int M;
		int x1, x2, y1, y2;
		cin >> g_col >> g_row >> g_depth >> M;
		char temp;
		vector<int> treasures;
		int temp_treasure;
		int sum_treause = 0;
		//////
		treasures.push_back(0);
		
		for (size_t j = 0; j < M; j++)
		{
			cin >> temp_treasure;
			sum_treause += temp_treasure;
			treasures.push_back(temp_treasure);
		}
		treasures.push_back(0);
		//matrix赋值
		for (size_t row = 0; row < g_row; row++)
		{
			for (size_t col = 0; col < g_col; col++)
			{
				cin >> temp;
				path[row][col] = temp;
				if (temp == '*')
				{

				}
				else if (temp == '@')
				{
					/*    path[row][col] = -3;*/
					x1 = col;
					y1 = row;
					postion_xy[0][0] = x1;
					postion_xy[0][1] = y1;
				}
				else if (temp == '<')
				{
					/*    path[row][col] = -2;*/
					x2 = col;
					y2 = row;
					postion_xy[M + 1][0] = x2;
					postion_xy[M + 1][1] = y2;
				}
				else if (temp == '.')
				{
					/*    path[row][col] = 0;*/
				}
				else
				{
					unsigned index = temp - 'A';
					/*        path[row][col] = treasures.at(index);*/
					postion_xy[index + 1][0] = col;
					postion_xy[index + 1][1] = row;
					max_index = max_index > index + 2 ? max_index : index + 2;
				}
			}
		}
		//END matrix赋值
		//TTimer test1;
		//test1.start();

		memset(matrix, 111111111111, sizeof(matrix));
		for (size_t j = 0; j <= max_index; ++j)
		{
			//for (size_t k = 0; k < j; k++)
			//{
			memset(visited, 0, sizeof(visited));
			BFS(postion_xy[j][0], postion_xy[j][1], j, M);
			//}
		}

		//test1.stop();
		//test1.start();

		memset(visited2, 0, sizeof(visited2));

		ans = -1;
		//int result = BFS2(0, 1, max_index, treasures, sum_treause);
		visited2[0] = true;
		dfs(0, 0, 0, sum_treause, M, treasures);
		int result = ans;
		//test1.stop();
		cout << "Case " << i + 1 << ":" << endl;
		if (result < 0)
		{
			cout << "Impossible" << endl ;
		}
		else
		{
			cout << "The best score is " << result << "." << endl ;
		}
		if (i < numcase - 1)
			cout << endl;
	}
	return 0;
}