//Prob: 1043 N!


#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

#define SQRTN 3
#define N 9  
#define NMAX 362885 //9! = 362880

int direction[4][2]{ 1, 0, 0, 1, -1, 0, 0, -1 };
char char_direction[4]{ 'l', 'u', 'r', 'd' };
bool visited[NMAX];
string g_path[NMAX];
const int fac[] = { 1,1,2,6,24,120,720,5040,40320 };//康托序列   
struct Point
{
	char eightPoint[N];
	unsigned position;
	string path;
};

inline unsigned cantor(char* p)//range from 0 to (N-1)!
{
	unsigned result = 0;
	for (size_t i = 1; i < N; i++)
	{
		unsigned num = 0;
		for (size_t j = 0; j <= i; j++)
		{
			if (p[i] < p[j])// Eg. 21
			{
				num++;
			}
		}
		result += fac[i] * num;
	}
	return result;
}

void BFSTraverse()
{
	Point init;
	for (size_t i = 0; i < N; i++)
	{
		init.eightPoint[i] = i + 1;
	}
	init.position = N - 1;
	init.path = "";
	memset(visited, 0, NMAX * sizeof(bool));
	visited[0] = true;

	queue<Point> que;
	que.push(init);
	int row, col;
	while (!que.empty())
	{
		Point lastpoint = que.front();
		que.pop();
		for (size_t i1 = 0; i1 < 4; i1++)
		{
			//计算新坐标
			col = lastpoint.position % SQRTN + direction[i1][0];
			row = lastpoint.position / SQRTN + direction[i1][1];
			if (col >= SQRTN || row >= SQRTN || col < 0 || row < 0)
			{
				continue;
			}
			unsigned g_position = row * SQRTN + col;

			//生成新的点的char信息
			Point newpoint(lastpoint);
			newpoint.eightPoint[newpoint.position] = newpoint.eightPoint[g_position];
			newpoint.eightPoint[g_position] = 9;
			

			//已经符合条件，继续
			unsigned g_nuumber = cantor(newpoint.eightPoint);
			if (visited[g_nuumber] == true)
			{
				continue;
			}
			newpoint.position = g_position;
			newpoint.path += char_direction[i1];
			g_path[g_nuumber] = newpoint.path;
			visited[g_nuumber] = true;
			//cout << "true:" << visited[40320] << endl;
			//cout << "hehe:" << g_nuumber << endl;
			que.push(newpoint);



		}
	}
}
int main() {
	

	BFSTraverse();
	//for (size_t i = 0; i < 24; i++)
	//{
	//	cout << i << ":" << visited[i] << ":" << g_path[i] << endl;
	//}
	//char a[9]{ 1, 2, 3, 4};
	//cout << endl << cantor(a);
	//cout << 1 << endl;
	char temp;
	while (cin >> temp)
	{
		char a[9];
		if (temp == 'x')
		{
			a[0] = 9;
		}
		else
			a[0] = temp - '0';

		for (size_t i = 1; i < 9; i++)
		{
			cin >> temp;
			if (temp == 'x')
			{
				a[i] = 9;
			}
			else
				a[i] = temp - '0';
			
		}
		//for (size_t i = 0; i < 9; i++)
		//{
		//	cout <<char(a[i] + '0') << " ";
		//}
		//cout << endl;
		//cout << cantor(a) << endl;
		unsigned num_cantor = cantor(a);
		if (visited[num_cantor])
		{
			reverse(g_path[num_cantor].begin(), g_path[num_cantor].end());
			cout << g_path[num_cantor] << endl;
		}
		else
		{
			cout << "unsolvable" << endl;
		}
	}
	return 0;
}
//2  3  4  1  5  x  7  6  8
//1  2  3  4  5  6  7  x  8