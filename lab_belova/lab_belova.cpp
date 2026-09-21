
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Pipe {
	string name;
	float length;
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

int ReadInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal && cin.peek() == '\n') {//Проверяем, что после числа нет мусора
            cin.ignore(1000, '\n');
            return value;
        }
        cout << "Ошибка! Введите целое число от " << minVal
            << " до " << maxVal << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

float ReadPositiveFloat(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0 && cin.peek() == '\n') {
            cin.ignore(1000, '\n');
            return value;
        }
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

string ReadNonEmptyString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) return value;
        cout << "Ошибка! Строка не может быть пустой." << endl;
    }
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	return 0;

}
