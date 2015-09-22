//Prob: 1030 Delta-wave
//三角形金字塔结构
//

//Problem Description
//A triangle field is numbered with successive integers in the way shown on the picture below.
//
//
//
//
//The traveller needs to go from the cell with number M to the cell with number N.The traveller is able to enter the cell through cell edges only, he can not travel from cell to cell through vertices.The number of edges the traveller passes makes the length of the traveller's route. 
//
//Write the program to determine the length of the shortest route connecting cells with numbers N and M.
//
//
//Input
//Input contains two integer numbers M and N in the range from 1 to 1000000000 separated with space(s).
//
//
//Output
//Output should contain the length of the shortest route.
//
//
//Sample Input
//6 12
//
//
//Sample Output
//3
//
//
//Source
//Ural Collegiate Programming Contest 1998
//
//
//Recommend
//lcy | We have carefully selected several similar problems for you:  1035 1071 1032 1027 1548

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
using namespace std;

int layer_location(int test)
{
	return int(ceil(sqrt(test)));
}
int left_location(int test)
{
	int last_layer = layer_location(test) - 1;
	return int((test - (last_layer * last_layer + 1)) / 2);
}
int right_location(int test)
{
	int cur_layer = layer_location(test);
	return int((cur_layer * cur_layer - test) / 2);
}

int main()
{
	vector<std::function<int(int)>> task;
	task.push_back(layer_location);
	task.push_back(left_location);
	task.push_back(right_location);

	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) 
	{
		int result = 0;
		for (size_t i = 0; i < 3; i++)
		{
			result += abs(task.at(i)(n) - task.at(i)(m));

		}
		cout << result << endl;
	}
	return 0;
}

