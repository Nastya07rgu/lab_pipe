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

class Logger {
    ofstream file;
public:
    Logger(const string& filename) {
        file.open(filename, ios::app); // ios::app — дописывать в конец файла
    }
    void log(const string& msg) {
        if (file.is_open()) file << msg << endl;
    }
    ~Logger() {
        if (file.is_open()) file.close();
    }
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
    cout << "4. Найти объект (редактировать/удалить)" << endl;
    cout << "5. Сохранить" << endl;
    cout << "6. Загрузить" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void Add_Pipe(vector<Pipe>& pipes, int& nextId, Logger& logger) {
    Pipe p;
    p.id = nextId++;
    cout << "\n Добавление трубы " << endl;
    p.name = ReadNonEmptyString("Введите название: ");
    p.length = ReadPositiveFloat("Введите длину трубы (км): ");
    p.diametr = ReadInt("Введите диаметр трубы (мм): ", 1, 100000);
    p.status = ReadInt("В ремонте? (1-да, 0-нет): ", 0, 1) == 1;

    pipes.push_back(p); // добавляем в конец вектора

    logger.log("ADD Pipe id=" + to_string(p.id) + " name=" + p.name); 

    cout << "Труба добавлена! ID: " << p.id << endl;
}
void Add_CS(vector<CS>& csList, int& nextId, Logger& logger) {
    CS c;
    c.id = nextId++;
    cout << "\n Добавление КС " << endl;
    c.name = ReadNonEmptyString("Название: ");
    c.number_work = ReadInt("Всего цехов: ", 1, 100000);
    c.number_work_online = ReadInt("Работающих цехов: ", 0, c.number_work);
    c.class_cs = ReadNonEmptyString("Класс станции: ");
    
    csList.push_back(c);
    logger.log("ADD CS id=" + to_string(c.id) + " name=" + c.name);
    cout << "КС добавлена! ID: " << c.id << endl;
}
void Show_All(const vector<Pipe>& pipes, const vector<CS>& csList) {
    cout << "\n Все объекты " << endl;

    if (pipes.empty()) {
        cout << "\nСписок труб пуст." << endl;
    }
    else {
        cout << "\nТрубы в списке: " << pipes.size() << endl;
        for (const Pipe& pipe : pipes) {
            cout << "  ID: " << pipe.id << endl;
            cout << "  Название: " << pipe.name << endl;
            cout << "  Длина: " << pipe.length << " км" << endl;
            cout << "  Диаметр: " << pipe.diametr << " мм" << endl;
            cout << "  В ремонте: " << (pipe.status ? "да" : "нет") << endl;
        }
    }

    if (csList.empty()) {
        cout << "\nСписок КС пуст." << endl;
    }
    else {
        cout << "\nКС в списке: " << csList.size() << endl;
        for (const CS& cs : csList) {
            cout << "  ID: " << cs.id << endl;
            cout << "  Название: " << cs.name << endl;
            cout << "  Всего цехов: " << cs.number_work << endl;
            cout << "  В работе: " << cs.number_work_online << endl;
            cout << "  Класс: " << cs.class_cs << endl;
        }
    }
}
void Edit_Pipe(vector<Pipe>& pipes, Logger& logger) {
    if (pipes.empty()) {
        cout << "Труб в списке нет!" << endl;
        return;
    }
    int id = ReadInt("Введите ID трубы для редактирования: ", 1, 1000000);

    for (Pipe& pipe : pipes) {          
        if (pipe.id == id) {
            cout << "Текущий статус: "
                << (pipe.status ? "в ремонте" : "не в ремонте") << endl;
            pipe.status = ReadInt("Новый статус (1-в ремонте, 0-не в ремонте): ", 0, 1) == 1;
            logger.log("EDIT Pipe id=" + to_string(pipe.id) + " new_status=" + to_string((int)pipe.status));
            cout << "Статус обновлён." << endl;
            return;
        }
    }
    cout << "Труба с ID " << id << " не найдена." << endl;
}

void Edit_CS(vector<CS>& csList, Logger& logger) {
    if (csList.empty()) {
        cout << "КС в списке нет!" << endl;
        return;
    }
    int id = ReadInt("Введите ID КС для редактирования: ", 1, 1000000);

    for (CS& cs : csList) {
        if (cs.id == id) {
            cout << "Цехов всего: " << cs.number_work << endl;
            cout << "Цехов в работе: " << cs.number_work_online << endl;
            cout << "1. Запустить цех" << endl;
            cout << "2. Остановить цех" << endl;
            int choice = ReadInt("Выберите действие: ", 1, 2);

            if (choice == 1) {
                if (cs.number_work_online < cs.number_work) {
                    cs.number_work_online++;
                    cout << "Цех запущен. Работает: " << cs.number_work_online << endl;
                }
                else {
                    cout << "Все цеха уже работают!" << endl;
                }
            }
            else {
                if (cs.number_work_online > 0) {
                    cs.number_work_online--;
                    cout << "Цех остановлен. Работает: " << cs.number_work_online << endl;
                }
                else {
                    cout << "Все цеха уже остановлены!" << endl;
                }
            }
            logger.log("EDIT CS id=" + to_string(cs.id) + " active=" + to_string(cs.number_work_online));
            return;
        }
    }
    cout << "КС с ID " << id << " не найдена." << endl;
}
void Delete_Pipe_By_Id(vector<Pipe>& pipes, Logger& logger) {
    if (pipes.empty()) { cout << "Труб в списке нет!" << endl; return; }

    int id = ReadInt("Введите ID трубы для удаления: ", 1, 1000000);

    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        if (it->id == id) {
            pipes.erase(it);
            logger.log("DELETE Pipe id=" + to_string(id));
            cout << "Труба с ID " << id << " удалена." << endl;
            return;
        }
    }
    cout << "Труба с ID " << id << " не найдена." << endl;
}

void Delete_CS_By_Id(vector<CS>& csList, Logger& logger) {
    if (csList.empty()) { cout << "КС в списке нет!" << endl; return; }

    int id = ReadInt("Введите ID КС для удаления: ", 1, 1000000);

    for (auto it = csList.begin(); it != csList.end(); ++it) {
        if (it->id == id) {
            csList.erase(it);
            logger.log("DELETE CS id=" + to_string(id));
            cout << "КС с ID " << id << " удалена." << endl;
            return;
        }
    }
    cout << "КС с ID " << id << " не найдена." << endl;
}
vector<int> Search_Pipes(const vector<Pipe>& pipes) {
    vector<int> found;
    cout << "\nПоиск труб:" << endl;
    cout << "1 - по названию" << endl;
    cout << "2 - по статусу (в ремонте)" << endl;
    int mode = ReadInt("Ваш выбор: ", 1, 2);

    if (mode == 1) {
        string fName = ReadNonEmptyString("Введите часть названия: ");
        for (const Pipe& p : pipes) {
            if (p.name.find(fName) != string::npos) { // ищем подстроку
                found.push_back(p.id);
            }
        }
    }
    else {
        int wantRepair = ReadInt("Искать: 1 - в ремонте, 0 - рабочие: ", 0, 1);
        for (const Pipe& p : pipes) {
            if (p.status == (wantRepair == 1)) {
                found.push_back(p.id);
            }
        }
    }
    return found;
}

vector<int> Search_CS(const vector<CS>& csList) {
    vector<int> found;
    cout << "\nПоиск КС:" << endl;
    cout << "1 - по названию" << endl;
    cout << "2 - по % незадействованных цехов" << endl;
    int mode = ReadInt("Ваш выбор: ", 1, 2);

    if (mode == 1) {
        string fName = ReadNonEmptyString("Введите часть названия: ");
        for (const CS& c : csList) {
            if (c.name.find(fName) != string::npos) {
                found.push_back(c.id);
            }
        }
    }
    else {
        float minP = ReadPositiveFloat("Минимальный % незадействованных: ");
        float maxP = ReadPositiveFloat("Максимальный % незадействованных: ");
        for (const CS& c : csList) {
            float percent = 0.0f;
            if (c.number_work > 0) {
                // формула: (всего - в работе) / всего * 100
                percent = 100.0f * (c.number_work - c.number_work_online) / c.number_work;
            }
            if (percent >= minP && percent <= maxP) {
                found.push_back(c.id);
            }
        }
    }
    return found;
}
void find_object(vector<Pipe>& pipes, vector<CS>& csList, Logger& logger) {
    if (pipes.empty() && csList.empty()) {
        cout << "\nНет объектов для поиска!" << endl;
        return;
    }

    cout << "\nЧто искать? 1 - трубы, 2 - КС: ";
    int type = ReadInt("", 1, 2);

    vector<int> ids;

    // Ищем объекты
    if (type == 1) {
        if (pipes.empty()) { cout << "Труб нет." << endl; return; }
        ids = Search_Pipes(pipes);
    }
    else {
        if (csList.empty()) { cout << "КС нет." << endl; return; }
        ids = Search_CS(csList);
    }

    if (ids.empty()) {
        cout << "Ничего не найдено." << endl;
        return;
    }

    // Выводим найденные
    cout << "\nНайдено (" << ids.size() << "):" << endl;
    for (int id : ids) {
        if (type == 1) {
            for (const Pipe& p : pipes) {
                if (p.id == id) {
                    cout << "ID: " << p.id << endl;
                    cout << "Название: " << p.name << endl;
                    cout << "Длина: " << p.length << " км" << endl;
                    cout << "Диаметр: " << p.diametr << " мм" << endl;
                    cout << "В ремонте: " << (p.status ? "да" : "нет") << endl;
                    break;
                }
            }
        }
        else {
            for (const CS& c : csList) {
                if (c.id == id) {
                    cout << "ID: " << c.id << endl;
                    cout << "Название: " << c.name << endl;
                    cout << "Всего цехов: " << c.number_work << endl;
                    cout << "Цехов в работе: " << c.number_work_online << endl;
                    cout << "Класс: " << c.class_cs << endl;
                    break;
                }
            }
        }
    }

    // Выбор "все" или "по одному"
    int pick = ReadInt("\n1 - выбрать ВСЕ найденные, 2 - выбрать по ID: ", 1, 2);

    vector<int> targets;
    if (pick == 1) {
        targets = ids; // берём всех найденных
    }
    else {
        cout << "Введите ID (0 - закончить):" << endl;
        while (true) {
            int id = ReadInt("ID: ", 0, 1000000);
            if (id == 0) break;
            // проверяем, что введённый ID есть в списке найденных
            bool ok = false;
            for (int x : ids) {
                if (x == id) { ok = true; break; }
            }
            if (ok) targets.push_back(id);
            else cout << "Такого ID нет в списке найденных." << endl;
        }
    }

    if (targets.empty()) {
        cout << "Ничего не выбрано." << endl;
        return;
    }

    // Действие: редактировать или удалить
    int action = ReadInt("\n1 - редактировать, 2 - удалить: ", 1, 2);

    if (action == 1) {
        // редактирование
        if (type == 1) {
            int newStatus = ReadInt("Новый статус труб (1-в ремонте, 0-работает): ", 0, 1);
            for (int id : targets) {
                for (Pipe& p : pipes) {
                    if (p.id == id) {
                        p.status = (newStatus == 1);
                        break;
                    }
                }
            }
        }
        else {
            int cmd = ReadInt("Действие с КС (1-запустить цех, 2-остановить цех): ", 1, 2);
            for (int id : targets) {
                for (CS& c : csList) {
                    if (c.id == id) {
                        if (cmd == 1 && c.number_work_online < c.number_work)
                            c.number_work_online++;
                        if (cmd == 2 && c.number_work_online > 0)
                            c.number_work_online--;
                        break;
                    }
                }
            }
        }
        cout << "Пакетное редактирование завершено." << endl;
        logger.log("BATCH EDIT type=" + to_string(type) + " count=" + to_string(targets.size()));
    }
    else {
        // удаление
        int count = 0;
        for (int id : targets) {
            if (type == 1) {
                for (auto it = pipes.begin(); it != pipes.end(); ++it) {
                    if (it->id == id) { pipes.erase(it); count++; break; }
                }
            }
            else {
                for (auto it = csList.begin(); it != csList.end(); ++it) {
                    if (it->id == id) { csList.erase(it); count++; break; }
                }
            }
        }
        cout << "Пакетное удаление завершено. Удалено: " << count << endl;
        logger.log("BATCH DELETE type=" + to_string(type) + " count=" + to_string(count));
    }
}


void Save_To_File(const vector<Pipe>& pipes, const vector<CS>& csList, Logger& logger) {
    cout << "Введите имя файла для сохранения (Enter — data.txt): ";
    string filename;
    getline(cin, filename);
    if (filename.empty()) filename = "data.txt";

    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Не удалось открыть файл для записи!" << endl;
        logger.log("SAVE FAIL file=" + filename);
        return;
    }

    
    out << pipes.size() << endl;
    for (const Pipe& p : pipes) {
        out << p.id << endl
            << p.name << endl
            << p.length << endl
            << p.diametr << endl
            << p.status << endl;
    }

   
    out << csList.size() << endl;
    for (const CS& c : csList) {
        out << c.id << endl
            << c.name << endl
            << c.number_work << endl
            << c.number_work_online << endl
            << c.class_cs << endl;
    }

    out.close();
    logger.log("SAVE file=" + filename + " pipes=" + to_string(pipes.size()) + " cs=" + to_string(csList.size()));
    cout << "Данные сохранены в " << filename << endl;
}

void Load_From_File(vector<Pipe>& pipes, vector<CS>& csList,
    int& nextPipeId, int& nextCsId, Logger& logger) {
    cout << "Введите имя файла для загрузки (Enter — data.txt): ";
    string filename;
    getline(cin, filename);
    if (filename.empty()) filename = "data.txt";

    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл не найден!" << endl;
        logger.log("LOAD FAIL file=" + filename);
        return;
    }

    pipes.clear();
    csList.clear();

   
    int count;
    in >> count;
    in.ignore(1000, '\n');
    int maxPipeId = 0;
    for (int i = 0; i < count; ++i) {
        Pipe p;
        in >> p.id;     in.ignore(1000, '\n');
        getline(in, p.name);
        in >> p.length >> p.diametr >> p.status;
        in.ignore(1000, '\n');
        pipes.push_back(p);
        if (p.id > maxPipeId) maxPipeId = p.id;
    }
    nextPipeId = maxPipeId + 1; // Чтобы новые ID не пересеклись со старыми

    
    in >> count;
    in.ignore(1000, '\n');
    int maxCsId = 0;
    for (int i = 0; i < count; ++i) {
        CS c;
        in >> c.id;     in.ignore(1000, '\n');
        getline(in, c.name);
        in >> c.number_work >> c.number_work_online;
        in.ignore(1000, '\n');
        getline(in, c.class_cs);
        csList.push_back(c);
        if (c.id > maxCsId) maxCsId = c.id;
    }
    nextCsId = maxCsId + 1;

    in.close();
    logger.log("LOAD file=" + filename + " pipes=" + to_string(pipes.size()) + " cs=" + to_string(csList.size()));
    cout << "Данные загружены из " << filename << endl;
}

int main() {
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Logger logger("log.txt");

    vector<Pipe> pipes;
    vector<CS> csList;
    int nextPipeId = 1;
    int nextCsId = 1;

    logger.log(" PROGRAM STARTED ");
    

    while (true) {
        Show_menu();
        int choice = ReadInt("", 0, 6);

        switch (choice) {
            case 1: Add_Pipe(pipes, nextPipeId, logger); break;
            case 2: Add_CS(csList, nextCsId, logger); break;
            case 3: Show_All(pipes, csList); break;
            case 4: find_object(pipes, csList, logger); break;
            case 5: Save_To_File(pipes, csList, logger); break; 
            case 6: Load_From_File(pipes, csList, nextPipeId, nextCsId, logger); break; 
            case 0:
                logger.log(" PROGRAM EXIT ");
                cout << "Выход." << endl; 
                return 0;
        
        }
    }
}

