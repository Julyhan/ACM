#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

//@param: hash����������ֵ�����ĸ���
const int MAX_N = 362880 + 100;

//@param map: 9λ����
int map[9];

//@param: �Ƿ���ʹ�
bool close[MAX_N];

//@param: cantorֵ���ķ���
char dir[MAX_N];

char direction[] = "udlr";

//@param: ȫ��·������
int f[MAX_N];

//@param:��ʾ��״̬���ɳڴ���
int open[MAX_N];

//@param: �ӳ�̬���Ϸ�̬��cantorֵ������һ��λ�õ�cantorֵ
int pa[MAX_N];

const int FACT[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };

const int MOVE[4][2] = { { 0, -1 },{ 0, 1 },{ -1, 0 },{ 1, 0 } };

//@param Node(id��a big interger, g����ʼ�ڵ㵽n�ڵ��ʵ�ʴ���,h: ��n��Ŀ��ڵ����·���Ĺ��ƴ���,
//	flags:��ʾ��״̬���ɳڴ���)
//��ʽ��ʾΪ�� f(n) = g(n) + h(n),
//���� f(n) �Ǵӳ�ʼ�㾭�ɽڵ�n��Ŀ���Ĺ��ۺ�����
//g(n) ����״̬�ռ��дӳ�ʼ�ڵ㵽n�ڵ��ʵ�ʴ��ۣ�
//h(n) �Ǵ�n��Ŀ��ڵ����·���Ĺ��ƴ��ۡ�
struct Node
{
	int id;
	int f, g, h;
	int flags;   
	Node() {}
	Node(int a_id, int a_g, int a_h, int a_flags)
	{
		id = a_id, g = a_g, h = a_h, flags = a_flags;
		f = g + h;
	}
	friend bool operator<(const Node &lhs, const Node &rhs);
};
bool operator<(const Node &lhs, const Node &rhs) { return lhs.f > rhs.f; }
priority_queue<Node> find_min;

int StateToCanto()
{
	int state_num = 1;
	for (int i = 0; i < 9; ++i)
	{
		int temp = map[i] - 1;

		for (int j = 0; j < i; ++j)
			temp -= (map[j] < map[i]);
		state_num += temp * FACT[8 - i];
	}
	return state_num;
}


//@brief: convert int* to an interger between 123456789 and 987654321.
int StateToId()
{
	int ans = 0;

	for (int i = 0; i < 9; ++i)
		ans = ans * 10 + map[i];
	return ans;
}

//@brief: convert an interger between 123456789 and 987654321 to int*.
void IdToState(int num)
{
	int i = 8;
	while (num)
	{
		map[i--] = num % 10;
		num /= 10;
	}
}

//@brief: calculate the A* distance of eight value matrix
//@return: A* distance
int Heuristic()
{
	int sum = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			int k = i * 3 + j;
			if (map[k] == 9) continue;
			sum += abs(i - (map[k] - 1) / 3) + abs(j - (map[k] - 1) % 3);
		}
	return sum;
}

//@brief: �����飬��֦
//@return: true: mod2==1�������ܷ�����false:mod2==0��һ������
inline bool inversionNumberCheck()
{
	int cnt = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (map[i] == 9) continue;
		for (int k = i - 1; k >= 0; --k)
		{
			if (map[k] == 9) continue;
			if (map[k] > map[i])
				cnt++;
		}
	}
	return cnt & 1;
}

//@brief:  get the position of 'x'
//@x: the col position
//@y: the row position
void FindX(int &x, int &y)
{
	for (int i = 0; i < 9; ++i)
	{
		if (map[i] == 9)
		{
			y = i / 3;
			x = i % 3;
			return;
		}
	}
}

int A_star()
{
	int state_canto, state_id;

	state_canto = StateToCanto();
	state_id = StateToId();
	open[state_canto] += 1;
	Node start(state_id, 0, Heuristic(), open[state_canto]);
	f[state_canto] = start.f;
	find_min.push(start);
	pa[state_canto] = -1;
	dir[state_canto] = '0';

	if (state_id == 123456789)
		return state_canto;

	while (!find_min.empty())
	{
		Node parent = find_min.top();
		Node child;
		int p_x, p_y, c_x, c_y, parent_canto;
		find_min.pop();

		IdToState(parent.id);
		parent_canto = StateToCanto();
		if (parent.flags != open[parent_canto]) // һ��״̬���ܱ��ɳڶ�Σ����parent�Ƿ�Ϊ��״̬���һ���ɳڵ�״̬
			continue;
		close[StateToCanto()] = 1; // To do

		FindX(p_x, p_y);
		for (int i = 0; i < 4; ++i)
		{
			int temp_swap, child_state_conto;

			c_x = p_x;
			c_y = p_y;
			c_x += MOVE[i][0];
			c_y += MOVE[i][1];

			if (c_x < 0 || c_x >= 3 || c_y < 0 || c_y >= 3)
				continue;
			temp_swap = map[p_x + p_y * 3];
			map[p_x + p_y * 3] = map[c_x + c_y * 3];
			map[c_x + c_y * 3] = temp_swap;
			child_state_conto = StateToCanto();

			if (close[child_state_conto] == 1)
			{
				temp_swap = map[p_x + p_y * 3];
				map[p_x + p_y * 3] = map[c_x + c_y * 3];
				map[c_x + c_y * 3] = temp_swap;

				continue;
			}

			child.id = StateToId();
			if (child.id == 123456789)
			{
				pa[child_state_conto] = parent_canto;
				dir[child_state_conto] = direction[i];
				return child_state_conto;
			}

			child.h = Heuristic();
			child.g = parent.g + 1;
			child.f = child.g + child.h;
			child.flags = open[child_state_conto] + 1;
			pa[child_state_conto] = parent_canto;
			dir[child_state_conto] = direction[i];
			if (open[child_state_conto] == 0 /*���ʴ���Ϊ0*/ || f[child_state_conto] > child.f /*�ɵ�ȫ��·�����ȴ����¼������*/)
			{
				f[child_state_conto] = child.f;
				open[child_state_conto] = child.flags;
				find_min.push(child);
			}
			temp_swap = map[p_x + p_y * 3];
			map[p_x + p_y * 3] = map[c_x + c_y * 3];
			map[c_x + c_y * 3] = temp_swap;
		}
	}
	return -1;
}

void Find(int i)
{
	if (pa[i] == -1)
		return;
	else
	{
		Find(pa[i]);
		printf("%c", dir[i]);
	}
}

void PrintPath()
{
	int end_canto;

	for (int i = 0; i < 9; ++i)
		map[i] = i + 1;
	end_canto = StateToCanto();

	Find(end_canto);
	printf("\n");
}

int main()
{
	int ans = 0;

	while (scanf("%s", &map[0]) != EOF)
	{
		map[0] = (map[0] == 'x' ? 9 : (map[0] -= '0'));
		for (int i = 1; i < 9; ++i)
		{
			scanf("%s", &map[i]);
			map[i] = (map[i] == 'x' ? 9 : (map[i] -= '0'));
		}

		if (inversionNumberCheck())
		{
			printf("unsolvable\n");
			continue;
		}
		memset(open, 0, sizeof(open));
		memset(close, 0, sizeof(close));
		memset(pa, 0, sizeof(pa));
		memset(f, 0, sizeof(f));
		memset(dir, 0, sizeof(dir));
		ans = A_star();
		if (ans == -1)
			printf("unsolvable\n");
		else
			PrintPath();

		while (find_min.empty())
			find_min.pop();
	}
	return 0;
}