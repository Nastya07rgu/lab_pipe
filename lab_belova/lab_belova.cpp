
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Pipe {
	string name;
	float lenght;
	int diametr;
	bool status;
	bool isAdded = false;
};

struct CS {
	string name;
	int number_work;
	int number_work_online;
	string class_cs;
	bool isAdded = false;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	return 0;

}
