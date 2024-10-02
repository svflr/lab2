#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Структура для хранения информации о трубе
struct Pipe {
    string name;        // километровая отметка
    double length;      // длина трубы
    double diameter;    // диаметр трубы
    bool in_repair;     // признак "в ремонте"

    // Функция для считывания данных трубы с консоли
    void input() {
        cout << "Введите километровую отметку (название трубы): ";
        cin >> ws; // для очистки буфера ввода перед вводом строки
        getline(cin, name);
        cout << "Введите длину трубы (км): ";
        cin >> length;
        cout << "Введите диаметр трубы (м): ";
        cin >> diameter;
        cout << "Труба в ремонте (1 - да, 0 - нет): ";
        cin >> in_repair;
    }

    // Функция для вывода данных трубы на консоль
    void output() const {
        cout << "Труба: " << name << endl;
        cout << "Длина: " << length << " км" << endl;
        cout << "Диаметр: " << diameter << " м" << endl;
        cout << "В ремонте: " << (in_repair ? "Да" : "Нет") << endl;
    }

    // Редактирование признака "в ремонте"
    void editRepair() {
        cout << "Труба в ремонте (1 - да, 0 - нет): ";
        cin >> in_repair;
    }
};

// Структура для хранения информации о компрессорной станции (КС)
struct CompressorStation {
    string name;             // название
    int total_workshops;      // общее количество цехов
    int active_workshops;     // количество цехов в работе
    double efficiency;        // эффективность

    // Функция для считывания данных КС с консоли
    void input() {
        cout << "Введите название КС: ";
        cin >> ws; // для очистки буфера ввода
        getline(cin, name);
        cout << "Введите общее количество цехов: ";
        cin >> total_workshops;
        do {
            cout << "Введите количество цехов в работе: ";
            cin >> active_workshops;
        } while (active_workshops > total_workshops || active_workshops < 0);
        cout << "Введите эффективность КС: ";
        cin >> efficiency;
    }

    // Функция для вывода данных КС на консоль
    void output() const {
        cout << "КС: " << name << endl;
        cout << "Общее количество цехов: " << total_workshops << endl;
        cout << "Цехов в работе: " << active_workshops << endl;
        cout << "Эффективность: " << efficiency << endl;
    }

    // Запуск или останов цехов
    void editWorkshops() {
        int change;
        do {
            cout << "Введите новое количество цехов в работе (от 0 до " << total_workshops << "): ";
            cin >> change;
        } while (change > total_workshops || change < 0);
        active_workshops = change;
    }
};

// Функции для сохранения и загрузки данных
void saveToFile(const vector<Pipe>& pipes, const vector<CompressorStation>& stations, const string& filename) {
    ofstream fout(filename);
    if (fout.is_open()) {
        fout << pipes.size() << endl;
        for (const auto& pipe : pipes) {
            fout << pipe.name << endl;
            fout << pipe.length << endl;
            fout << pipe.diameter << endl;
            fout << pipe.in_repair << endl;
        }
        fout << stations.size() << endl;
        for (const auto& station : stations) {
            fout << station.name << endl;
            fout << station.total_workshops << endl;
            fout << station.active_workshops << endl;
            fout << station.efficiency << endl;
        }
        fout.close();
        cout << "Данные успешно сохранены в файл." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи." << endl;
    }
}

void loadFromFile(vector<Pipe>& pipes, vector<CompressorStation>& stations, const string& filename) {
    ifstream fin(filename);
    if (fin.is_open()) {
        size_t pipeCount, stationCount;
        fin >> pipeCount;
        pipes.clear();
        for (size_t i = 0; i < pipeCount; ++i) {
            Pipe pipe;
            fin >> ws;
            getline(fin, pipe.name);
            fin >> pipe.length;
            fin >> pipe.diameter;
            fin >> pipe.in_repair;
            pipes.push_back(pipe);
        }
        fin >> stationCount;
        stations.clear();
        for (size_t i = 0; i < stationCount; ++i) {
            CompressorStation station;
            fin >> ws;
            getline(fin, station.name);
            fin >> station.total_workshops;
            fin >> station.active_workshops;
            fin >> station.efficiency;
            stations.push_back(station);
        }
        fin.close();
        cout << "Данные успешно загружены из файла." << endl;
    }
    else {
        cout << "Ошибка при открытии файла для чтения." << endl;
    }
}

int main() {
    vector<Pipe> pipes;
    vector<CompressorStation> stations;
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
        cin >> choice;

        switch (choice) {
        case 1: {
            Pipe pipe;
            pipe.input();
            pipes.push_back(pipe);
            break;
        }
        case 2: {
            CompressorStation station;
            station.input();
            stations.push_back(station);
            break;
        }
        case 3: {
            cout << "Трубы:\n";
            for (const auto& pipe : pipes)
                pipe.output();
            cout << "\nКомпрессорные станции:\n";
            for (const auto& station : stations)
                station.output();
            break;
        }
        case 4: {
            if (!pipes.empty()) {
                for (size_t i = 0; i < pipes.size(); ++i) {
                    cout << i + 1 << ". ";
                    pipes[i].output();
                }
                cout << "Выберите трубу для редактирования: ";
                size_t index;
                cin >> index;
                if (index > 0 && index <= pipes.size())
                    pipes[index - 1].editRepair();
            }
            else {
                cout << "Нет доступных труб для редактирования.\n";
            }
            break;
        }
        case 5: {
            if (!stations.empty()) {
                for (size_t i = 0; i < stations.size(); ++i) {
                    cout << i + 1 << ". ";
                    stations[i].output();
                }
                cout << "Выберите КС для редактирования: ";
                size_t index;
                cin >> index;
                if (index > 0 && index <= stations.size())
                    stations[index - 1].editWorkshops();
            }
            else {
                cout << "Нет доступных КС для редактирования.\n";
            }
            break;
        }
        case 6:
            saveToFile(pipes, stations, filename);
            break;
        case 7:
            loadFromFile(pipes, stations, filename);
            break;
        case 0:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
