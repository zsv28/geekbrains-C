#include <algorithm>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <numeric>


using namespace std;

template <typename C>
void printCont(const C& c)
{
	for (auto const& e : c)
	{
		cout << e << " ";
	}
	cout << endl;
}

template< typename T >
typename std::vector<T>::iterator
insert_sorted(std::vector<T>& vec, T const& item)
{
	int medianIndex = vec.size() / 2;
	if (item < vec.at(medianIndex) / 2)
	{
		return vec.insert(
			std::upper_bound(vec.begin(), vec.end() - medianIndex + 1, item),
			item);
	}
	else {
		return vec.insert(
			std::upper_bound(vec.begin() + medianIndex - 1, vec.end(), item),
			item);
	}
}

int main()
{
	cout << "Task-1" << endl;
	vector<int> vInt{ 2,5,1,4,9,7 };
	printCont(vInt);
	cout << "Sort vector" << endl;
	sort(vInt.begin(), vInt.end());//сортировка массива
	printCont(vInt);
	cout<<"insert_sorted"<<endl;
	insert_sorted(vInt, 3);//функция добавляет элемент в уже отсортированный массив
	printCont(vInt);
	cout << endl;
	

	cout << "Task-2" << endl;
	vector<double> analog; //массив аналогово сигнала
	for (int x = 0; x < 100; ++x) // запомление массива с изменение по синусоиде
	{
		auto y = 5 * sin((x * M_PI / 2));
		analog.push_back(y);
	}
	vector<int> digital; //массив цифрового сигнала
	transform(analog.cbegin(), analog.cend(), back_inserter(digital), [](double value) -> int { return trunc(value); }); //данные массива analog с отбросом дробных частей
	cout << "analog" << endl;
	printCont(analog);
	cout <<endl<< "digital" << endl;
	printCont(digital);

	vector<double> temp_array; //временный массив для подсчета
	temp_array.resize(analog.size()); // берем размер равный массиву analog
	generate(temp_array.begin(), temp_array.end(), [&analog, &digital, n = -1]() mutable { ++n; return pow(analog[n] - digital[n], 2); }); //подсчет двух массивов
	cout << endl << endl;
	cout << "temp_array"<<endl;
	printCont(temp_array);
	cout << endl;
	auto result = accumulate(temp_array.begin(), temp_array.end(), 0.); // результат ошибки
	cout << "result = "<<result;
}