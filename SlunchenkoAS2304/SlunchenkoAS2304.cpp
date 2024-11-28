#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
    string Name;
    float length;
    int diameter;
    bool repair;
};

struct Station {
    string Name;
    int workshops;
    int workshopsinwork;
    int effectiveness;
};

int check_int(int max, int low) {
    int z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено отрицательное число или ноль! Попробуйте ещё раз: ";
        }
        else if (max != 0 && z > max) {
            cout << "Ошибка. Введено число больше допустимого значения! Попробуйте ещё раз: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

float floatcheck(int max, float low) {
    float z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не дробное число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено отрицательное число или ноль! Попробуйте ещё раз: ";
        }
        else if (max != 0 && z > max) {
            cout << "Ошибка. Введено число больше допустимого значения! Попробуйте ещё раз: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

int menu() {
    cout << "Меню" << endl
        << "1) Добавить трубу" << endl
        << "2) Добавить станцию" << endl
        << "3) Просмотреть объекты" << endl
        << "4) Редактировать трубу" << endl
        << "5) Редактировать станцию" << endl
        << "6) Сохранить данные" << endl
        << "7) Загрузить данные" << endl
        << "0) Выход" << endl
        << "Введите команду (0 до 7): ";
    return check_int(7, 0);
}

void new_pipe(Pipe& P) {
    cout << "Введите название трубы: ";
    getline(cin, P.Name);
    cout << "Введите длину трубы в километрах: ";
    P.length = floatcheck(0, 0.1);
    cout << "Введите диаметр трубы в миллиметрах: ";
    P.diameter = check_int(0, 1);
    cout << "Выберите статус трубы:\n0) Не в ремонте\n1) В ремонте\n";
    P.repair = check_int(1, 0);
    cout << "Труба создана: " << endl
        << "Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}

void new_station(Station& CS) {
    cout << "Введите название станции: ";
    getline(cin, CS.Name);
    cout << "Введите количество цехов: ";
    CS.workshops = check_int(0, 1);
    cout << "Введите количество цехов в работе: ";
    CS.workshopsinwork = check_int(CS.workshops, 0);
    cout << "Введите коэффициент эффективности станции (от 0 до 100): ";
    CS.effectiveness = check_int(100, 0);
    cout << "Станция создана: " << endl
        << "Название станции: " << CS.Name << "; Количество цехов: " << CS.workshops << "; Цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности: " << CS.effectiveness << endl;
}

void show_pipe(const Pipe& P) {
    cout << "Труба: " << endl
        << "Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}

void show_station(const Station& CS) {
    cout << "Станция: " << endl
        << "Название станции: " << CS.Name << "; Количество цехов: " << CS.workshops << "; Цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности: " << CS.effectiveness << endl;
}

void view_all(const Pipe& P, const Station& CS) {
    if (!P.Name.empty()) {
        show_pipe(P);
    }
    else {
        cout << "Труба ещё не добавлена!" << endl;
    }
    if (!CS.Name.empty()) {
        show_station(CS);
    }
    else {
        cout << "Станция ещё не добавлена!" << endl;
    }
}

void edit_pipe(Pipe& P) {
    if (!P.Name.empty()) {
        cout << "Выберите параметр для редактирования:\n"
            << "1) Название трубы\n"
            << "2) Длина трубы\n"
            << "3) Диаметр трубы\n"
            << "4) Статус 'на ремонте'\n"
            << "0) Вернуться в меню\n";
        int choice = check_int(4, 0);
        switch (choice) {
        case 1:
            cout << "Введите новое название трубы: ";
            getline(cin, P.Name);
            break;
        case 2:
            cout << "Введите новую длину трубы: ";
            P.length = floatcheck(0, 0.1);
            break;
        case 3:
            cout << "Введите новый диаметр трубы: ";
            P.diameter = check_int(0, 1);
            break;
        case 4:
            cout << "Выберите новый статус трубы:\n0) Не на ремонте\n1) На ремонте\n";
            P.repair = check_int(1, 0);
            break;
        }
    }
    else {
        cout << "Труба ещё не добавлена!" << endl;
    }
}

void edit_station(Station& CS) {
    if (!CS.Name.empty()) {
        cout << "Выберите параметр для редактирования:\n"
            << "1) Название станции\n"
            << "2) Количество цехов\n"
            << "3) Коэффициент эффективности\n"
            << "4) Количество цехов в работе\n"
            << "0) Вернуться в меню\n";
        int choice = check_int(4, 0);
        switch (choice) {
        case 1:
            cout << "Введите новое название станции: ";
            getline(cin, CS.Name);
            break;
        case 2:
            cout << "Введите новое количество цехов: ";
            CS.workshops = check_int(0, 1);
            CS.workshopsinwork = min(CS.workshopsinwork, CS.workshops);
            break;
        case 3:
            cout << "Введите новый коэффициент эффективности (от 0 до 100): ";
            CS.effectiveness = check_int(100, 0);
            break;
        case 4:
            cout << "Введите новое количество цехов в работе: ";
            CS.workshopsinwork = check_int(CS.workshops, 0);
            break;
        }
    }
    else {
        cout << "Станция ещё не добавлена!" << endl;
    }
}

void save(const Pipe& P, const Station& CS) {
    ofstream out("data.txt");
    if (out.is_open()) {
        if (!P.Name.empty()) {
            out << "Труба\n" << P.Name << '\n' << P.length << ' ' << P.diameter << ' ' << P.repair << '\n';
        }
        if (!CS.Name.empty()) {
            out << "Станция\n" << CS.Name << '\n' << CS.workshops << ' ' << CS.workshopsinwork << ' ' << CS.effectiveness << '\n';
        }
        cout << "Данные сохранены!" << endl;
    }
    else {
        cout << "Ошибка сохранения данных!" << endl;
    }
    out.close();
}

void load(Pipe& P, Station& CS) {
    ifstream in("data.txt");
    if (in.is_open()) {
        string type;
        while (getline(in, type)) {
            if (type == "Труба") {
                getline(in, P.Name);
                in >> P.length >> P.diameter >> P.repair;
                in.ignore();
            }
            else if (type == "Станция") {
                getline(in, CS.Name);
                in >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
                in.ignore();
            }
        }
        cout << "Данные загружены!" << endl;
    }
    else {
        cout << "Ошибка загрузки данных!" << endl;
    }
    in.close();
}

int main() {
    Pipe P;
    Station CS;
    while (true) {
        switch (menu()) {
        case 1: new_pipe(P); break;
        case 2: new_station(CS); break;
        case 3: view_all(P, CS); break;
        case 4: edit_pipe(P); break;
        case 5: edit_station(CS); break;
        case 6: save(P, CS); break;
        case 7: load(P, CS); break;
        case 0: return 0;
        }
    }
}
