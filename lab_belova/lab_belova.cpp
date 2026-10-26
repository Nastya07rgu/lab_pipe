#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;

struct Pipe {
	string name;
	float length;
	int diametr;
	bool status;
    int id;
};

struct CS {
	string name;
	int number_work;
	int number_work_online;
	string class_cs;
    int id;
};

int ReadInt(const string& prompt, int minVal, int maxVal) {//безопасный ввод целого числа
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal && cin.peek() == '\n') {//проверяем, что после числа нет мусора
            cin.ignore(1000, '\n');//очищаем мусор
            return value;
        }
        cout << "Ошибка! Введите целое число от " << minVal
            << " до " << maxVal << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

float ReadPositiveFloat(const string& prompt) {//безопасный ввод положительного числа
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

string ReadNonEmptyString(const string& prompt) {//безопасный ввод строки
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);//читает всю строку целиком, включая пробелы
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

void Add_Pipe(vector<Pipe>& pipes, int& nextId) {
    Pipe p;
    p.id = nextId++;
    cout << "\n Добавление трубы " << endl;
    p.name = ReadNonEmptyString("Введите название: ");
    p.length = ReadPositiveFloat("Введите длину трубы (км): ");
    p.diametr = ReadInt("Введите диаметр трубы (мм): ", 1, 100000);
    p.status = ReadInt("В ремонте? (1-да, 0-нет): ", 0, 1) == 1;

    pipes.push_back(p); // добавляем в конец вектора
    cout << "Труба добавлена! ID: " << p.id << endl;
}
void Add_CS(vector<CS>& csList, int& nextId) {
    CS c;
    c.id = nextId++;
    cout << "\n Добавление КС " << endl;
    c.name = ReadNonEmptyString("Название: ");
    c.number_work = ReadInt("Всего цехов: ", 1, 100000);
    c.number_work_online = ReadInt("Работающих цехов: ", 0, c.number_work);
    c.class_cs = ReadNonEmptyString("Класс станции: ");
    
    csList.push_back(c);
    cout << "КС добавлена! ID: " << c.id << endl;
}
void Show_All(const vector<Pipe>& pipes, const vector<CS>& csList) {
    cout << "\n Все объекты " << endl;

    if (pipes.empty()) {
        cout << "\n[Трубы] Список пуст." << endl;
    }
    else {
        cout << "\n[Трубы] В списке: " << pipes.size() << endl;
        for (const Pipe& pipe : pipes) {
            cout << "  ID: " << pipe.id
                << " | Название: " << pipe.name
                << " | Длина: " << pipe.length << " км"
                << " | Диаметр: " << pipe.diametr << " мм"
                << " | В ремонте: " << (pipe.status ? "да" : "нет") << endl;
        }
    }

    if (csList.empty()) {
        cout << "\n[КС] Список пуст." << endl;
    }
    else {
        cout << "\n[КС] В списке: " << csList.size() << endl;
        for (const CS& cs : csList) {
            cout << "  ID: " << cs.id
                << " | Название: " << cs.name
                << " | Всего цехов: " << cs.number_work
                << " | В работе: " << cs.number_work_online
                << " | Класс: " << cs.class_cs << endl;
        }
    }
}
void Edit_Pipe(Pipe& pipe) {
    if (!pipe.isAdded) {
        cout << "Сначала добавьте трубу!" << endl;
        return;
    }
    cout << "\n Редактирование трубы " << endl;
    cout << "Текущий статус: " << (pipe.status ? "в ремонте" : "не в ремонте") << endl;
    pipe.status = ReadInt("Новый статус (1-в ремонте, 0-не в ремонте): ", 0, 1) == 1;
    cout << "Статус обновлён." << endl;
}

void Edit_CS(CS& cs) {
    if (!cs.isAdded) {
        cout << "Сначала добавьте КС!" << endl;
        return;
    }
    cout << "\n Редактирование КС " << endl;
    cout << "Цехов всего: " << cs.number_work << endl;
    cout << "Цехов в работе: " << cs.number_work_online << endl;
    cout << "1. Запустить цех" << endl;
    cout << "2. Остановить цех" << endl;
    int choice = ReadInt("Выберите действие: ", 1, 2);

    if (choice == 1) {
        if (cs.number_work_online < cs.number_work) {//проверяем есть ли что запускать
            cs.number_work_online++;
            cout << "Цех запущен. Работает: " << cs.number_work_online << endl;
        }
        else {
            cout << "Все цеха уже работают!" << endl;
        }
    }
    else {
        if (cs.number_work_online > 0) {//проверяем есть ли что останавливать
            cs.number_work_online--;
            cout << "Цех остановлен. Работает: " << cs.number_work_online << endl;
        }
        else {
            cout << "Все цеха уже остановлены!" << endl;
        }
    }
}
void Save_To_File(const Pipe& pipe, const CS& cs, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Не удалось открыть файл для записи!" << endl;
        return;
    }
    out << pipe.isAdded << endl;
    if (pipe.isAdded) {
        out << pipe.name << endl;
        out << pipe.length << endl;
        out << pipe.diametr << endl;
        out << pipe.status << endl;
    }
    out << cs.isAdded << endl;
    if (cs.isAdded) {
        out << cs.name << endl;
        out << cs.number_work << endl;
        out << cs.number_work_online << endl;
        out << cs.class_cs << endl;
    }
    out.close();
    cout << "Данные сохранены в " << filename << endl;
}

void Load_From_File(Pipe& pipe, CS& cs, const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл не найден!" << endl;
        return;
    }
    in >> pipe.isAdded;
    in.ignore(1000, '\n');
    if (pipe.isAdded) {
        getline(in, pipe.name);
        in >> pipe.length >> pipe.diametr >> pipe.status;
        in.ignore(1000, '\n');
    }
    in >> cs.isAdded;
    in.ignore(1000, '\n');
    if (cs.isAdded) {
        getline(in, cs.name);
        in >> cs.number_work >> cs.number_work_online;
        in.ignore(1000, '\n');
        getline(in, cs.class_cs);
    }
    in.close();
    cout << "Данные загружены из " << filename << endl;
}
int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Pipe> pipes;
    vector<CS> csList;
    int nextPipeId = 1;
    int nextCsId = 1;
    const string filename = "data.txt";

    while (true) {
        Show_menu();
        int choice = ReadInt("", 0, 7);

        switch (choice) {
            case 1: Add_Pipe(pipes, nextPipeId); break;
            case 2: Add_CS(csList, nextCsId); break;
            case 3: Show_All(pipes, csList); break;
            //case 4: Edit_Pipe(pipe); break;
            //case 5: Edit_CS(cs); break;
            //case 6: Save_To_File(pipe, cs, filename); break;
            //case 7: Load_From_File(pipe, cs, filename); break;
            case 0: cout << "Выход." << endl; return 0;
        
        }
    }
}

