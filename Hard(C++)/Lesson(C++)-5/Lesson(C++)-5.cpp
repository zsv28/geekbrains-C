#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_set>

using namespace  std;

//1.Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов,
//и выводящую в консоль список уникальных слов(если слово повторяется больше 1 раза, то вывести его надо один раз).
//Продемонстрировать работу функции, передав итераторы различных типов.

template <typename IteratorType>
void foo_iter(IteratorType begin, IteratorType end)
{
	using type = typename iterator_traits<IteratorType>::value_type; //тип данных на который указывает итератор
	set<type> s{ begin, end }; // переносим наш контейнер в формат set-контейнера
	copy(s.begin(), s.end(), ostream_iterator<type>(cout, " "));//выводим результат
}

//2.Используя ассоциативный контейнер, напишите программу,
//которая будет считывать данные введенные пользователем из стандартного потока ввода и разбивать их на предложения.
//Далее программа должна вывести пользователю все предложения, отсортировав их по длине.




int main()
{
	//Задание-1
	cout << "Task-1" << endl;
	vector<string> words = { "hello","hi","hey","hi" };
	foo_iter(words.begin(), words.end());
	cout << endl;
	list<string> words2 = { "one","two", "one","three" };
	foo_iter(words2.begin(), words2.end());

	//Задание-2
	cout << endl << "Task-2" << endl;
	cout << "Enter  three sentences separated by '.'" << endl;
	string a,b,c; //переменные для ввода
	//ввод пользователем предложений
	getline(cin, a, '.');
	getline(cin, b, '.');
	getline(cin, c, '.');
	multimap<int, string> str;
	//запись предложений в контейнер
	str.emplace(a.size(), a);
	str.emplace(b.size(), b);
	str.emplace(c.size(), c);
	for(auto i:str)
	{
		cout <<i.second<< endl; // Вывод предложений
	}
	
	return 0;
}
