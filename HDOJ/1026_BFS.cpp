//Prob 1026 Ignatius and the Princess I
//reference: http://www.csdn123.com/html/mycsdn20140110/ef/eff538bb46dfeb69fd9076e3ddbe2246.html
//keypoint: DFS vs BFS
//Problem Description
//The Princess has been abducted by the BEelzebub feng5166, our hero Ignatius has to rescue our pretty Princess.Now he gets into feng5166's castle. The castle is a large labyrinth. To make the problem simply, we assume the labyrinth is a N*M two-dimensional array which left-top corner is (0,0) and right-bottom corner is (N-1,M-1). Ignatius enters at (0,0), and the door to feng5166's room is at(N - 1, M - 1), that is our target.There are some monsters in the castle, if Ignatius meet them, he has to kill them.Here is some rules :
//
//1.Ignatius can only move in four directions(up, down, left, right), one step per second.A step is defined as follow : if current position is(x, y), after a step, Ignatius can only stand on(x - 1, y), (x + 1, y), (x, y - 1) or (x, y + 1).
//2.The array is marked with some characters and numbers.We define them like this :
//	. : The place where Ignatius can walk on.
//	X : The place is a trap, Ignatius should not walk on it.
//	n : Here is a monster with n HP(1 <= n <= 9), if Ignatius walk on it, it takes him n seconds to kill the monster.
//
//	Your task is to give out the path which costs minimum seconds for Ignatius to reach target position.You may assume that the start position and the target position will never be a trap, and there will never be a monster at the start position.
//
//
//	Input
//	The input contains several test cases.Each test case starts with a line contains two numbers N and M(2 <= N <= 100, 2 <= M <= 100) which indicate the size of the labyrinth.Then a N*M two - dimensional array follows, which describe the whole labyrinth.The input is terminated by the end of file.More details in the Sample Input.
//
//
//	Output
//	For each test case, you should output "God please help our poor hero." if Ignatius can't reach the target position, or you should output "It takes n seconds to reach the target position, let me show you the way."(n is the minimum seconds), and tell our hero the whole path. Output a line contains "FINISH" after each test case. If there are more than one path, any one is OK in this problem. More details in the Sample Output.
//
//
//	Sample Input
//	5 6
//	.XX.1.
//	..X.2.
//	2...X.
//	...XX.
//	XXXXX.
//	5 6
//	.XX.1.
//	..X.2.
//	2...X.
//	...XX.
//	XXXXX1
//	5 6
//	.XX...
//	..XX1.
//	2...X.
//	...XX.
//	XXXXX.
//
//
//	Sample Output
//	It takes 13 seconds to reach the target position, let me show you the way.
//	1s:(0, 0)->(1, 0)
//	2s : (1, 0)->(1, 1)
//	3s : (1, 1)->(2, 1)
//	4s : (2, 1)->(2, 2)
//	5s : (2, 2)->(2, 3)
//	6s : (2, 3)->(1, 3)
//	7s : (1, 3)->(1, 4)
//	8s : FIGHT AT(1, 4)
//	9s : FIGHT AT(1, 4)
//	10s : (1, 4)->(1, 5)
//	11s : (1, 5)->(2, 5)
//	12s : (2, 5)->(3, 5)
//	13s : (3, 5)->(4, 5)
//	FINISH
//	It takes 14 seconds to reach the target position, let me show you the way.
//	1s : (0, 0)->(1, 0)
//	2s : (1, 0)->(1, 1)
//	3s : (1, 1)->(2, 1)
//	4s : (2, 1)->(2, 2)
//	5s : (2, 2)->(2, 3)
//	6s : (2, 3)->(1, 3)
//	7s : (1, 3)->(1, 4)
//	8s : FIGHT AT(1, 4)
//	9s : FIGHT AT(1, 4)
//	10s : (1, 4)->(1, 5)
//	11s : (1, 5)->(2, 5)
//	12s : (2, 5)->(3, 5)
//	13s : (3, 5)->(4, 5)
//	14s : FIGHT AT(4, 5)
//	FINISH
//	God please help our poor hero.
//	FINISH
//
//
//	Author
//	Ignatius.L
//
//
//	Recommend
//	We have carefully selected several similar problems for you:  1072 1175 1180 1253 1242



#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

class Labyrinth
{
private:
	unsigned int MAXDIS = 100000;//numeric_limits<unsigned int>::max();//100*100*10
	unsigned int MAXALL;
	int row_number = 0, col_number = 0;
	vector<vector<unsigned int> > array_distance;
	vector<vector<int> > array_char;
	vector<vector<short> > path_direction;
	vector<vector<bool> > visited;
	vector<pair<int, int>> direciton;//(make_pair(1, 0), { 0, 1 }, { -1, 0 }, { 0, -1 });
	struct Node
	{
		int row_number;
		int col_number;
	};

public:
	Labyrinth(int row, int col)
	{
		direciton.push_back(make_pair<int, int>(1, 0));
		direciton.push_back(make_pair<int, int>(0, 1));
		direciton.push_back(make_pair<int, int>(-1, 0));
		direciton.push_back(make_pair<int, int>(0, -1));

		row_number = row;
		col_number = col;
		//array_distance.resize((row_number + 1, col_number + 1));
		//array_distance.resize(row_number + 1, vector<int>(col_number + 1));
		//path_direction.resize(row_number + 1, vector<int>(col_number + 1));
		vector<unsigned int> temp_unsigned(col_number + 1);
		vector<short> temp_short(col_number + 1);
		vector<int> temp_int(col_number + 1);
		vector<bool> temp_bool(col_number + 1);
		for (size_t i = 0; i < row + 1; i++)
		{
			array_char.push_back(temp_int);
			array_distance.push_back(temp_unsigned);
			path_direction.push_back(temp_short);
			visited.push_back(temp_bool);
		}

		for (size_t row = 0; row <= row_number; row++)
		{
			for (size_t col = 0; col <= col_number; col++)
			{
				array_distance.at(row).at(col) = MAXDIS;
				visited.at(row).at(col) = false;
			}
		}
	}
	void set_path()
	{
		char current_node;
		for (size_t row = 1; row <= row_number; row++)
		{
			for (size_t col = 1; col <= col_number; col++)
			{
				cin >> current_node;
				if (current_node == 'X')
					array_char.at(row).at(col) = -1;
				else if (current_node == '.')
					array_char.at(row).at(col) = 0;
				else
					array_char.at(row).at(col) = current_node - '0';
			}
		}
		MAXALL = (row_number * col_number - 2) * 10 + 1;
	}
	void BFSTraverse()
	{
		queue<Node> Q;

		//for (int row = 1; row <= row_number; row++)
		//{
		//	for (int col = 1; col <= col_number; col++)
		//	{
				int col = 1, row = 1;
				if (!visited[row][col])
				{
					visited[row][col] = true;
					Node temp{ row, col };
					Q.push(temp);
					while (!Q.empty())
					{
						Node pop_element = Q.front();
						row = pop_element.row_number;
						col = pop_element.col_number;
						Q.pop();
						visited[row][col] = false;/////
												  //4 directions
						for (size_t i = 0; i < 4; i++)
						{
							unsigned row_new = row + get<0>(direciton.at(i)), col_new = col + get<1>(direciton.at(i));
							if (col_new == 0 || row_new == 0 || col_new == (col_number + 1) || row_new == (row_number + 1))
								continue;
							if (array_char[row_new][col_new] < 0)
								continue;
							Node temp2{ row_new, col_new };
							unsigned int old_value = array_char[row_new][col_new];
							unsigned int refresh_dis = 1 + array_distance[row][col] + old_value;
							unsigned int value_past = array_distance[row_new][col_new];
							// 新位置的最小距离 = min（原新位置距离， 1步+旧位置距离+旧位置战斗值）
							if (refresh_dis < value_past)
							{
								if (!visited[row_new][col_new])
								{
									visited[row_new][col_new] = true;
									Q.push(temp2);
								}
								array_distance[row_new][col_new] = refresh_dis;
								path_direction[row_new][col_new] = i + 1;

							}
						}
					}
				}
		//	}
		//}
	}
	void calculate()
	{
		array_distance.at(1).at(1) = 0;
		BFSTraverse();
		if (array_distance.at(row_number).at(col_number) == MAXDIS)
		{
			cout << "God please help our poor hero." << endl << "FINISH" << endl;
		}
		else
		{
			vector<vector<short> > path_direction_first;

			vector<short> temp_short(col_number + 1);
			for (size_t i = 0; i < row_number + 1; i++)
			{
				path_direction_first.push_back(temp_short);
			}
			int col = col_number, row = row_number;
			int total_pathnumber = array_char.at(row).at(col);
			while (1)
			{
				switch (path_direction.at(row).at(col))//vector<pair<int, int>> direciton{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
				{
				case 1:
					path_direction_first.at(--row).at(col) = 1;
					break;//Right
				case 2:
					path_direction_first.at(row).at(--col) = 2;
					break;//Down
				case 3:
					path_direction_first.at(++row).at(col) = 3;
					break;//Left
				case 4:
					path_direction_first.at(row).at(++col) = 4;
					break;//Up
				default:
					break;
				}
				total_pathnumber++;
				total_pathnumber += array_char.at(row).at(col);
				if (col == 1 && row == 1)
				{
					break;
				}
			}
			cout << "It takes " << total_pathnumber << " seconds to reach the target position, let me show you the way." << endl;
			for (size_t i = 0; i < total_pathnumber; i++)
			{
				cout << i + 1 << "s:(" << row - 1 << "," << col - 1 << ")->(";
				switch (path_direction_first.at(row).at(col))//vector<pair<int, int>> direciton{ {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
				{
				case 1:
					row++;break;//Right
				case 2:
					col++;break;//Down
				case 3:
					row--;break;//Left
				case 4:
					col--;break;//Up
				default:
					break;
				}
				cout << row - 1 << "," << col - 1 << ")" << endl;
				unsigned fight_num = array_char.at(row).at(col);
				while (fight_num > 0)
				{
					cout << (++i + 1) << "s:FIGHT AT (" << row - 1 << "," << col - 1 << ")" << endl;
					fight_num--;
				}
			}
			cout << "FINISH" << endl;
		}
	}
};

int main()
{
	int row, col;
	while (scanf("%d%d", &row, &col) != EOF)
	{
		Labyrinth test(row, col);
		test.set_path();
		test.calculate();
	}

	return 0;
}
