//Prob 1035: Robot Motion
//Problem Description
//
//
//A robot has been programmed to follow the instructions in its path.Instructions for the next direction the robot is to move are laid down in a grid.The possible instructions are
//
//N north(up the page)
//S south(down the page)
//E east(to the right on the page)
//W west(to the left on the page)
//
//For example, suppose the robot starts on the north(top) side of Grid 1 and starts south(down).The path the robot follows is shown.The robot goes through 10 instructions in the grid before leaving the grid.
//
//Compare what happens in Grid 2: the robot goes through 3 instructions only once, and then starts a loop through 8 instructions, and never exits.
//
//You are to write a program that determines how long it takes a robot to get out of the grid or how the robot loops around.
//
//
//Input
//There will be one or more grids for robots to navigate.The data for each is in the following form.On the first line are three integers separated by blanks : the number of rows in the grid, the number of columns in the grid, and the number of the column in which the robot enters from the north.The possible entry columns are numbered starting with one at the left.Then come the rows of the direction instructions.Each grid will have at least one and at most 10 rows and columns of instructions.The lines of instructions contain only the characters N, S, E, or W with no blanks.The end of input is indicated by a row containing 0 0 0.
//
//
//Output
//For each grid in the input there is one line of output.Either the robot follows a certain number of instructions and exits the grid on any one the four sides or else the robot follows the instructions on a certain number of locations once, and then the instructions on some number of locations repeatedly.The sample input below corresponds to the two grids above and illustrates the two forms of output.The word "step" is always immediately followed by "(s)" whether or not the number before it is 1.
//
//
//Sample Input
//3 6 5
//NEESWE
//WWWESS
//SNWWWW
//4 5 1
//SESWE
//EESNW
//NWEEN
//EWSEN
//0 0
//
//
//Sample Output
//10 step(s) to exit
//3 step(s) before a loop of 8 step(s)
//
//
//Source
//Mid - Central USA 1999
//
//
//Recommend
//We have carefully selected several similar problems for you:  2553 1258 1045 2660 1312

#include <iostream>
#include <cstring>
using namespace std;
#define MAXNUM 11

int main()
{
	unsigned row, col;
	cin >> row >> col;
	while (row != 0 && col != 0)
	{
		bool visited[MAXNUM][MAXNUM];
		memset(visited, 0, sizeof(bool)*MAXNUM*MAXNUM);
		char path[MAXNUM][MAXNUM];
		memset(path, 0, sizeof(char)*MAXNUM*MAXNUM);
		unsigned count_path_array[MAXNUM][MAXNUM];
		memset(count_path_array, 0, sizeof(unsigned)*MAXNUM*MAXNUM);
		unsigned init_col;
		cin >> init_col;
		//坐标转为索引
		unsigned cur_row = 0, cur_col = init_col - 1;
		char path_temp;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				cin >> path_temp;
				path[i][j] = path_temp;
			}
		}
		int count_total = 0;
		bool loop = false;
		while ((cur_row >= 0) && (cur_row < row) && (cur_col >= 0) && (cur_col < col))
		{
			//cout << "cur_row:" << cur_row << " cur_col:" << cur_col << endl;
			if (visited[cur_row][cur_col])
			{
				cout << count_path_array[cur_row][cur_col] << " step(s) before a loop of "
					<< count_total - count_path_array[cur_row][cur_col] << " step(s)" << endl;
				loop = true;
				break;
			}
			visited[cur_row][cur_col] = true;
			count_path_array[cur_row][cur_col] = count_total;
			//第一个格子已经经历过一格
			count_total++;
			switch (path[cur_row][cur_col])
			{
			case 'N':
				cur_row--;
				break;
			case 'S':
				cur_row++;
				break;
			case 'E':
				cur_col++;
				break;
			case 'W':
				cur_col--;
				break;
			default:
				break;
			}
		}
		if (!loop)
		{
			cout << count_total << " step(s) to exit" << endl;
		}
		cin >> row >> col;
	}
	
	return 0;
}