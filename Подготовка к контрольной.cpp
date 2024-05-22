// Харитонович Маргарита, ФСК, Прикладная информатика, 1 курс, 21-я группа
// Контрольная работа ПИ1
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
using namespace std;

class Test {
public:
	string country;
	string team;
	int total_score;
	int num_solved;
	vector<int> points;
public:
	virtual int total_sum() = 0;
	virtual int total_solved() = 0;
	virtual void Output() = 0;
	friend istringstream& operator >> (istringstream& in, Test& test) {

		in >> test.country;
		getline(in, test.team, ':');
		int a;
		while (in >> a)
		{
			test.points.push_back(a);
		}
		test.total_sum();
		test.total_solved();
		return in;
	}
};

class CompSrtuctPointers
{
public:
	bool operator()(const Test* obj1, const Test* obj2)
	{
		return obj1->total_score < obj2->total_score;
	}
};

class HeirTest: public Test {
public:
	ifstream in, prizy;
	ofstream res, diplomy;
public:
	int total_sum() override {
		total_score = accumulate(points.begin(), points.end(), 0);
		return total_score;
	}
	int total_solved() override {
		num_solved = points.size();
		return num_solved;
	}
	void Output() override {
		res.open("Result.txt", ios::app);
		if (!res.is_open())
		{
			cout << "Ошибка" << endl;
		}
		res << "Страна: " << country << endl;
		res << "Команда: " << team << endl;
		res << "Общий балл: " << total_score << endl;
		res << "Количество решённых задач: " << num_solved << endl<<endl;

		cout << "Страна: " << country << endl;
		cout << "Команда: " << team << endl;
		cout << "Общий балл: " << total_score << endl;
		cout << "Количество решённых задач: " << num_solved << endl << endl;
		res.close();
	}
	~HeirTest() {
		in.close();
		prizy.close();
		res.close();
		diplomy.close();
	}
};

class Prises : public HeirTest {
public:
	vector<Test*> commands;
public:
	Prises() {
		in.open("Olimp.txt");
		string s;
		if (!in.is_open())
		{
			cout << "Ошибка" << endl;
		}
		while (getline(in, s)) {
			istringstream iss(s);
			HeirTest* a = new HeirTest();
			iss >> *a;
			commands.push_back(a);
		}
	}
	void Sort() {
		sort(commands.begin(), commands.end(), CompSrtuctPointers());
	}
	void Print() {
		cout << "Команды:" << endl << endl;
		for (Test* obj : commands)
			obj->Output();
	}
	void Search_winners() {
		Sort();
		prizy.open("Prizy.txt");
		diplomy.open("Diplomy.txt");
		if (!prizy.is_open())
		{
			cout << "Ошибка" << endl;
		}
		if (!diplomy.is_open())
		{
			cout << "Ошибка" << endl;
		}
		string s;
		auto it = commands.end();
		cout << "Дипломы: " << endl<<endl;
		while (getline(prizy, s))
		{
			istringstream iss(s);
			it--;
			iss >> s;
			diplomy << "Номер диплома: " << s << endl;
			cout << "Номер диплома: " << s << endl;;
			getline(iss, s);
			diplomy << "Название приза: " << s << endl;
			diplomy << "Страна: " << (*it)->country << endl;
			diplomy << "Команда: " << (*it)->team << endl;
			diplomy << "Общий балл: " << (*it)->total_score << endl << endl;

			cout << "Название приза: " << s << endl;
			cout << "Страна: " << (*it)->country << endl;
			cout << "Команда: " << (*it)->team << endl;
			cout << "Общий балл: " << (*it)->total_score << endl << endl;
		}
		prizy.close();
		diplomy.close();
	}
	~Prises() {
		for (Test* obj : commands) {
			delete obj;
		}
	}
	};

int main() {
	setlocale(LC_ALL, "rus");
	Prises commands;
	commands.Sort();
	commands.Print();
	commands.Search_winners();
	system("pause");
	return 0;
}