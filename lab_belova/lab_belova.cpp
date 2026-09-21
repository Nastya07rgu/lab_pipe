
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

void Add_Pipe(Pipe& pipe) {
    cout << "\n=== Добавление трубы ===" << endl;
    pipe.name = ReadNonEmptyString("Введите километровую отметку (название): ");
    pipe.length = ReadPositiveFloat("Введите длину трубы (км): ");
    pipe.diametr = ReadInt("Введите диаметр трубы (мм): ", 1, 100000);
    pipe.status = ReadInt("В ремонте? (1-да, 0-нет): ", 0, 1) == 1;
    pipe.isAdded = true;
    cout << "Труба добавлена!" << endl;
}
void Add_CS(CS& cs) {
    cout << "\n=== Добавление КС ===" << endl;
    cs.name = ReadNonEmptyString("Название: ");
    cs.number_work = ReadInt("Всего цехов: ", 1, 100000);
    cs.number_work_online = ReadInt("Работающих цехов: ", 0, cs.number_work);
    cs.class_cs = ReadNonEmptyString("Класс станции: ");
    cs.isAdded = true;
    cout << "КС добавлена!" << endl;
}
void Edit_Pipe(Pipe& pipe) {
    if (!pipe.isAdded) {
        cout << "Сначала добавьте трубу!" << endl;
        return;
    }
    cout << "\n=== Редактирование трубы ===" << endl;
    cout << "Текущий статус: " << (pipe.status ? "в ремонте" : "не в ремонте") << endl;
    pipe.status = ReadInt("Новый статус (1-в ремонте, 0-не в ремонте): ", 0, 1) == 1;
    cout << "Статус обновлён." << endl;
}
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Pipe pipe;
    CS   cs;

    while (true) {
        Show_menu();
        int choice = ReadInt("", 0, 7);
        switch (choice) {
        case 1: Add_Pipe(pipe); break;
        case 2: Add_CS(cs); break;
        case 3: Show_All(pipe, cs); break;
        case 4: Edit_Pipe(pipe); break;
        case 0: cout << "Выход." << endl; return 0;
        default: cout << "Пункт в разработке." << endl;
        }
    }
}

