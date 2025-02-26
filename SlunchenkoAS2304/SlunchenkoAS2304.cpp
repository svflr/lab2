#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

struct Pipe {
    int id;
    string name;
    float length;
    int diameter;
    bool repair;
};

struct Station {
    int id;
    string name;
    int workshops;
    int workshopsInWork;
    int effectiveness;
};

vector<Pipe> pipes;
vector<Station> stations;
int pipeID = 1, stationID = 1;

void logAction(const string& action) {
    ofstream logFile("log.txt", ios::app);
    time_t now = time(0);
    logFile << ctime(&now) << action << endl;
}

int getIntInput(int min, int max = 0) {
    int value;
    while (!(cin >> value) || value < min || (max != 0 && value > max)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка. Попробуйте ещё раз: ";
    }
    cin.ignore();
    return value;
}

float getFloatInput(float min) {
    float value;
    while (!(cin >> value) || value < min) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка. Попробуйте ещё раз: ";
    }
    cin.ignore();
    return value;
}

void addPipe() {
    Pipe p;
    p.id = pipeID++;
    cout << "Название трубы: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Длина (км): ";
    p.length = getFloatInput(0.1);
    cout << "Диаметр (мм): ";
    p.diameter = getIntInput(1);
    cout << "В ремонте? (1 - да, 0 - нет): ";
    p.repair = getIntInput(0, 1);
    pipes.push_back(p);
    logAction("Добавлена труба ID: " + to_string(p.id));
}

void addStation() {
    Station s;
    s.id = stationID++;
    cout << "Название станции: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Количество цехов: ";
    s.workshops = getIntInput(1);
    cout << "Цехов в работе: ";
    s.workshopsInWork = getIntInput(0, s.workshops);
    cout << "Эффективность (0-100): ";
    s.effectiveness = getIntInput(0, 100);
    stations.push_back(s);
    logAction("Добавлена станция ID: " + to_string(s.id));
}

void viewPipes() {
    for (const auto& p : pipes)
        cout << "Труба [ID: " << p.id << "] " << p.name << " | Длина: " << p.length << " | Диаметр: " << p.diameter << " | В ремонте: " << (p.repair ? "Да" : "Нет") << endl;
}

void viewStations() {
    for (const auto& s : stations)
        cout << "Станция [ID: " << s.id << "] " << s.name << " | Цехов: " << s.workshops << " | В работе: " << s.workshopsInWork << " | Эффективность: " << s.effectiveness << endl;
}

void deletePipe() {
    cout << "Введите ID трубы для удаления: ";
    int id = getIntInput(1);
    pipes.erase(remove_if(pipes.begin(), pipes.end(), [id](const Pipe& p) { return p.id == id; }), pipes.end());
}

void deleteStation() {
    cout << "Введите ID станции для удаления: ";
    int id = getIntInput(1);
    stations.erase(remove_if(stations.begin(), stations.end(), [id](const Station& s) { return s.id == id; }), stations.end());
}

void searchPipes() {
    cout << "Фильтр труб: 1 - по названию, 2 - по ремонту: ";
    int choice = getIntInput(1, 2);
    if (choice == 1) {
        string name;
        cout << "Введите название трубы: ";
        cin.ignore();
        getline(cin, name);
        for (const auto& p : pipes)
            if (p.name.find(name) != string::npos)
                cout << "Труба [ID: " << p.id << "] " << p.name << endl;
    }
    else {
        cout << "В ремонте? (1 - да, 0 - нет): ";
        bool status = getIntInput(0, 1);
        for (const auto& p : pipes)
            if (p.repair == status)
                cout << "Труба [ID: " << p.id << "] " << p.name << endl;
    }
}

void searchStations() {
    cout << "Фильтр станций: 1 - по названию, 2 - по проценту незадействованных цехов: ";
    int choice = getIntInput(1, 2);

    if (choice == 1) {
        string name;
        cout << "Введите название станции: ";
        cin.ignore();
        getline(cin, name);
        bool found = false;
        for (const auto& s : stations) {
            if (s.name.find(name) != string::npos) {
                double freePercentage = (100.0 * (s.workshops - s.workshopsInWork) / s.workshops);
                cout << "Станция [ID: " << s.id << "] " << s.name << " | Цехов: " << s.workshops
                    << " | В работе: " << s.workshopsInWork
                    << " | Незадействовано: " << freePercentage << "%\n";
                found = true;
            }
        }
        if (!found) cout << "Станции с таким названием не найдены.\n";
    }
    else {
        cout << "Сортировать станции по незадействованным цехам? (1 - по убыванию, 2 - по возрастанию): ";
        int sortOrder = getIntInput(1, 2);

        sort(stations.begin(), stations.end(), [sortOrder](const Station& a, const Station& b) {
            double freeA = (100.0 * (a.workshops - a.workshopsInWork) / a.workshops);
            double freeB = (100.0 * (b.workshops - b.workshopsInWork) / b.workshops);
            return sortOrder == 1 ? freeA > freeB : freeA < freeB;
            });

        cout << "Список станций после сортировки:\n";
        for (const auto& s : stations) {
            double freePercentage = (100.0 * (s.workshops - s.workshopsInWork) / s.workshops);
            cout << "Станция [ID: " << s.id << "] " << s.name << " | Цехов: " << s.workshops
                << " | В работе: " << s.workshopsInWork
                << " | Незадействовано: " << freePercentage << "%\n";
        }
    }
}




void batchEditPipes() {
    cout << "Изменить статус ремонта всех труб? (1 - да, 0 - выбрать): ";
    int choice = getIntInput(0, 1);
    cout << "Введите новый статус ремонта (1 - в ремонте, 0 - не в ремонте): ";
    bool newStatus = getIntInput(0, 1);
    if (choice == 1) {
        for (auto& p : pipes) p.repair = newStatus;
    }
    else {
        cout << "Введите ID труб через пробел (0 - завершить): ";
        string input;
        cin.ignore();
        getline(cin, input);
        istringstream iss(input);
        int id;
        while (iss >> id && id != 0) {
            for (auto& p : pipes)
                if (p.id == id) p.repair = newStatus;
        }
    }
}

int main() {
    while (true) {
        cout << "1) Добавить трубу\n2) Добавить станцию\n3) Просмотреть трубы\n4) Просмотреть станции\n5) Поиск труб\n6) Поиск станций\n7) Удалить трубу\n8) Удалить станцию\n9) Пакетное редактирование труб\n0) Выход\nВыберите действие: ";
        switch (getIntInput(0, 9)) {
        case 1: addPipe(); break;
        case 2: addStation(); break;
        case 3: viewPipes(); break;
        case 4: viewStations(); break;
        case 5: searchPipes(); break;
        case 6: searchStations(); break;
        case 7: deletePipe(); break;
        case 8: deleteStation(); break;
        case 9: batchEditPipes(); break;
        case 0: return 0;
        }
    }
}
