#include <iostream>
#include <fstream>
#include <string>
#include <limits> 

using namespace std;

const int MAX_PIPES = 100;  
const int MAX_STATIONS = 100;  

struct Pipe {
    string name;
    double length;
    double diameter;
    bool in_repair;

    void input() {
        cout << "Введите километровую отметку (название трубы): ";
        cin >> ws;
        getline(cin, name);

        cout << "Введите длину трубы (км): ";
        while (!(cin >> length) || length <= 0) {
            cout << "Ошибка! Введите корректное значение длины: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Введите диаметр трубы (м): ";
        while (!(cin >> diameter) || diameter <= 0) {
            cout << "Ошибка! Введите корректное значение диаметра: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Труба в ремонте (1 - да, 0 - нет): ";
        while (!(cin >> in_repair)) {
            cout << "Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void output() const {
        cout << "Труба: " << name << endl;
        cout << "Длина: " << length << " км" << endl;
        cout << "Диаметр: " << diameter << " м" << endl;
        cout << "В ремонте: " << (in_repair ? "Да" : "Нет") << endl;
    }

    void editRepair() {
        cout << "Труба в ремонте (1 - да, 0 - нет): ";
        while (!(cin >> in_repair)) {
            cout << "Ошибка! Введите 0 или 1: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

struct CompressorStation {
    string name;
    int total_workshops;
    int active_workshops;
    double efficiency;

    void input() {
        cout << "Введите название КС: ";
        cin >> ws;
        getline(cin, name);

        cout << "Введите общее количество цехов: ";
        while (!(cin >> total_workshops) || total_workshops < 0) {
            cout << "Ошибка! Введите корректное количество цехов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        do {
            cout << "Введите количество цехов в работе: ";
            while (!(cin >> active_workshops) || active_workshops < 0) {
                cout << "Ошибка! Введите корректное количество цехов в работе: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (active_workshops > total_workshops);

        cout << "Введите эффективность КС: ";
        while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
            cout << "Ошибка! Введите корректное значение эффективности (0-100): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void output() const {
        cout << "КС: " << name << endl;
        cout << "Общее количество цехов: " << total_workshops << endl;
        cout << "Цехов в работе: " << active_workshops << endl;
        cout << "Эффективность: " << efficiency << endl;
    }

    void editWorkshops() {
        int change;
        do {
            cout << "Введите новое количество цехов в работе (от 0 до " << total_workshops << "): ";
            while (!(cin >> change)) {
                cout << "Ошибка! Введите корректное количество цехов в работе: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (change > total_workshops || change < 0);
        active_workshops = change;
    }
};

void saveToFile(const Pipe pipes[], const CompressorStation stations[], int pipeCount, int stationCount, const string& filename) {
    ofstream fout(filename);
    if (fout.is_open()) {
        fout << pipeCount << endl;
        for (int i = 0; i < pipeCount; ++i) {
            fout << pipes[i].name << endl;
            fout << pipes[i].length << endl;
            fout << pipes[i].diameter << endl;
            fout << pipes[i].in_repair << endl;
        }
        fout << stationCount << endl;
        for (int i = 0; i < stationCount; ++i) {
            fout << stations[i].name << endl;
            fout << stations[i].total_workshops << endl;
            fout << stations[i].active_workshops << endl;
            fout << stations[i].efficiency << endl;
        }
        fout.close();
        cout << "Данные успешно сохранены в файл." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи." << endl;
    }
}

void loadFromFile(Pipe pipes[], CompressorStation stations[], int& pipeCount, int& stationCount, const string& filename) {
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> pipeCount;
        for (int i = 0; i < pipeCount; ++i) {
            fin >> ws;
            getline(fin, pipes[i].name);
            fin >> pipes[i].length;
            fin >> pipes[i].diameter;
            fin >> pipes[i].in_repair;
        }
        fin >> stationCount;
        for (int i = 0; i < stationCount; ++i) {
            fin >> ws;
            getline(fin, stations[i].name);
            fin >> stations[i].total_workshops;
            fin >> stations[i].active_workshops;
            fin >> stations[i].efficiency;
        }
        fin.close();
        cout << "Данные успешно загружены из файла." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для чтения." << endl;
    }
}

int main() {
    Pipe pipes[MAX_PIPES];
    CompressorStation stations[MAX_STATIONS];
    int pipeCount = 0, stationCount = 0;
    string filename = "data.txt";

    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать КС\n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        while (!(cin >> choice)) {
            cout << "Ошибка! Введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: {
            if (pipeCount < MAX_PIPES) {
                pipes[pipeCount].input();
                pipeCount++;
            }
            else {
                cout << "Достигнут предел количества труб.\n";
            }
            break;
        }
        case 2: {
            if (stationCount < MAX_STATIONS) {
                stations[stationCount].input();
                stationCount++;
            }
            else {
                cout << "Достигнут предел количества КС.\n";
            }
            break;
        }
        case 3: {
            cout << "Трубы:\n";
            for (int i = 0; i < pipeCount; ++i)
                pipes[i].output();
            cout << "\nКомпрессорные станции:\n";
            for (int i = 0; i < stationCount; ++i)
                stations[i].output();
            break;
        }
        case 4: {
            if (pipeCount > 0) {
                for (int i = 0; i < pipeCount; ++i) {
                    cout << i + 1 << ". ";
                    pipes[i].output();
                }
                cout << "Выберите трубу для редактирования: ";
                int index;
                while (!(cin >> index) || index <= 0 || index > pipeCount) {
                    cout << "Ошибка! Введите корректный индекс: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                pipes[index - 1].editRepair();
            }
            else {
                cout << "Нет доступных труб для редактирования.\n";
            }
            break;
        }
        case 5: {
            if (stationCount > 0) {
                for (int i = 0; i < stationCount; ++i) {
                    cout << i + 1 << ". ";
                    stations[i].output();
                }
                cout << "Выберите КС для редактирования: ";
                int index;
                while (!(cin >> index) || index <= 0 || index > stationCount) {
                    cout << "Ошибка! Введите корректный индекс: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                stations[index - 1].editWorkshops();
            }
            else {
                cout << "Нет доступных КС для редактирования.\n";
            }
            break;
        }
        case 6:
            saveToFile(pipes, stations, pipeCount, stationCount, filename);
            break;
        case 7:
            loadFromFile(pipes, stations, pipeCount, stationCount, filename);
            break;
        case 0:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
