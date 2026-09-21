
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

void Show_menu() {
    cout << "\n1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void Show_All(const Pipe& pipe, const CS& cs) {
    cout << "\n=== Все объекты ===" << endl;

    if (pipe.isAdded) {
        cout << "\n--- Труба ---" << endl;
        cout << "Километровая отметка: " << pipe.name << endl;
        cout << "Длина: " << pipe.length << " км" << endl;
        cout << "Диаметр: " << pipe.diametr << " мм" << endl;
        cout << "В ремонте: " << (pipe.status ? "да" : "нет") << endl;
    }
    else {
        cout << "Труба не добавлена." << endl;
    }

    if (cs.isAdded) {
        cout << "\n--- Компрессорная станция ---" << endl;
        cout << "Название: " << cs.name << endl;
        cout << "Всего цехов: " << cs.number_work << endl;
        cout << "Цехов в работе: " << cs.number_work_online << endl;
        cout << "Класс: " << cs.class_cs << endl;
    }
    else {
        cout << "КС не добавлена." << endl;
    }
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	return 0;

}
