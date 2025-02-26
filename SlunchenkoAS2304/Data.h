#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;


#define INPUT_LINE(in, str) getline(in>> ws, str); \
						 cerr << str <<  endl
#define PRINT_PARAM(out, x) out<< #x << "=" << x <<  endl
template <typename T>
T GetCorrectData(T min, T max)
{
	T x;
	while (( cin >> x).fail() ||  cin.peek() != '\n' || x < min || x > max)
	{
		 cin.clear();
		 cin.ignore(100000, '\n');
		 cout << "Мы вас не поняли. Напишите число от " << min << " до " << max << ":" << endl;
	}
	cerr << x << endl;

	return x;
}
template <typename T>
T& SelectElement(unordered_map<int, T>& notes, int key)
{
	auto it = notes.find(key);
	if (it != notes.end())
	{
		return it->second;
	}
	else
	{
		cout << "Моя твоя не понимать. Напишите правильно :0 ( до " << notes.size() << "): " << endl;
	}
}

template <typename T>
T GetCorrectDiameter(T min, T max)
{
	T diameter;
	cin >> diameter;
	while (((diameter != 500) && (diameter != 700) && (diameter != 1000) && (diameter != 1400)) || diameter < min || diameter > max || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "Пожалуйста, напишите верный диаметр трубы (500, 700, 1000, 1400): "<< endl;
		cin >> diameter;
	}
	cerr << diameter << endl;
	return diameter;
}


template <typename K>
unordered_map<int, K> removeKeyIfExists(unordered_map<int, K>& notes, int key) {
	while (true) {
		auto it = notes.find(key);
		if (it != notes.end()) {
			notes.erase(it);
			cout << "Готово. Удалили!" << endl;
			return notes;
		}
		else {
			cout << "Мы не нашли то, что вы хотели удалить. Возможно вы сами когда-то там удалили...Что хотите удалить?" << endl;
			key = GetCorrectData(1, findMaxId(notes));
		}
	}
}
string inputString(istream& in = cin);
template<typename K, typename V>
K findMaxId(const  unordered_map<K, V>& map) {
	if (map.empty()) {
		throw  runtime_error("Пусто...");
	}

	K maxId =  numeric_limits<K>::min();

	for (const auto& pair : map) {
		if (pair.first > maxId) {
			maxId = pair.first;
		}
	}
	return maxId;
}

template <typename T>
T inputNumber(istream& in = cin)
{
	T x;
	while ((in >> x).fail()	
		|| in.peek() != '\n')	
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "НЕ ЧИСЛО! " << endl;
	}
	cerr << x << endl;
	return x;
}


class redirect_output_wrapper
{
	 ios& stream;
	 streambuf* const old_buf;
public:
	redirect_output_wrapper( ios& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect( ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};