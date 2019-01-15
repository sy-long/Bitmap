#include <iostream>
#include <vector>
#include<string>

using namespace std;

struct node
{
	bool data;
	node *next;
	node *front;
};
struct record_inf
{
	string name;
	int id;
};
const int N = 25;
const int Maxrecord = 10000;
int record_num = 0;
node Map[N][N];
record_inf inf[Maxrecord];

void set_map()
{
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			Map[i][j].data = 0;
			Map[i][j].next = NULL;
		}
}
void show_map()
{
	system("cls");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << Map[i][j].data << "  ";
		cout << "\n";
	}
	system("pause");

}
void show_record()
{
	system("cls");
	cout << "文件名" << "     " << "盘块号" << endl;
	for (int i = 0; i < record_num; i++)
		cout << inf[i].name << "              " << inf[i].id << endl;
	system("pause");
}
void record(string name, int id)
{
	inf[record_num].id = id;
	inf[record_num].name = name;
	record_num++;
}
void allocation()
{
	system("cls");
	cout << "请输入要分配的文件大小:";
	int size;
	cin >> size;
	int id;
	if (size == 0)
	{
		cout << "文件大小为0，未分配！";
		system("pause");
		return;
	}
	vector<node*> temp;
	int count = 0;
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			if (count == size)
				break;
			if (Map[i][j].data == 0)
			{
				if (count == 0)
				{
					id = i * N + j;
				}
				temp.push_back(&(Map[i][j]));
				count++;
			}
		}
	if (temp.size() < size)
	{
		cout << "空间不足，未分配！";
		system("pause");
		return;
	}
	temp[0]->front = NULL;
	temp[0]->next = temp[1];
	temp[0]->data = 1;
	for (int j = 1; j < size - 1; j++)
	{
		temp[j]->front = temp[j - 1];
		temp[j]->next = temp[j + 1];
		temp[j]->data = 1;
	}
	temp[size - 1]->front = temp[size - 2];
	temp[size - 1]->next = NULL;
	temp[size - 1]->data = 1;
	while (!temp.empty())
		temp.pop_back();
	cout << "请输入该文件的文件名:";
	string file_name;
	cin >> file_name;
	record(file_name, id);
	cout << "存储成功！";
	system("pause");
}
void recovery_file()
{
	system("cls");
	cout << "请输入要删除的文件的文件名:";
	string name_file;
	cin >> name_file;
	int id;
	int i;
	for (i = 0; i < record_num; i++)
		if (inf[i].name == name_file)
		{
			id = inf[i].id;
			break;
		}
	if (i >= record_num)
	{
		cout << "没有该文件,回收失败!";
		system("pause");
		return;
	}
	int x, y;
	x = id / N;
	y = id % N;
	node *temp = &Map[x][y];
	while (temp != NULL)
	{
		temp->data = 0;
		temp = temp->next;
	}
	cout << "回收成功!";
	system("pause");
}
void recovery_bit()
{
	system("cls");
	cout << "请输入要回收磁盘块的盘块号:";
	int id;
	cin >> id;
	if (id<0 || id>N*N)
	{
		cout << "没有该盘块号，回收失败!";
	}
	int x, y;
	x = id / N;
	y = id % N;
	Map[x][y].data = 0;
	Map[x][y].front->next = Map[x][y].next;
	cout << "回收成功!";
	system("pause");
}
void menu()
{
	system("cls");
	cout << "1.分配盘块" << endl;
	cout << "2.以文件回收" << endl;
	cout << "3.以磁盘块为单位回收" << endl;
	cout << "4.查看已分配的文件情况" << endl;
	cout << "5.查看位示图情况" << endl;
	cout << "6.退出";
	cout << "\n\n";
	cout << "请选择:";
	int chiose;
	cin >> chiose;
	switch (chiose)
	{
	case 1:allocation();
		break;
	case 2:recovery_file();
		break;
	case 3:recovery_bit();
		break;
	case 4:show_record();
		break;
	case 5:show_map();
		break;
	case 6:exit(0);
		break;
	default:
		break;
	}
}

int main()
{
	set_map();
	while (1)
	{
		menu();
	}
	return 0;
}