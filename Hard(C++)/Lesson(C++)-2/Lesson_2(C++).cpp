#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>



using namespace std;


//Задание-1
//Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, на которые указывают эти указатели.

template < typename T >
void my_swap(T*& a, T*& b) //шаблонная функция, аналогична swap
{
	T* temp = a;
	a = b;
	b = temp;
}

//Задание-2
//Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.

template <typename T>
void SortPointers(vector<T*>& t)
{
	
	sort(t.begin(), t.end(),[](int* a, int* b)
	{
			return *a < *b;
	});
}
//задание-3(таймер)
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::string m_name;
	std::chrono::time_point<clock_t> m_beg;
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}

public:
	Timer() : m_beg(clock_t::now()) { }
	Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

	void start(std::string name) {
		m_name = name;
		m_beg = clock_t::now();
	}
	void print() const {
		std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
	}
};

int main()
{
	//Реализация Задания-1
	cout << "Task-1" << endl;

	int* ptrInt1 = new int(2);
	*ptrInt1 = 5;
	int* ptrInt2 = new int(3);
	*ptrInt2 = 8;
	cout <<"*ptrInt1= " << *ptrInt1<<endl;
	cout <<"*ptrInt2= " << *ptrInt2<<endl;
	cout << "Swap ptr"<<endl;
	my_swap(ptrInt1, ptrInt2);
	cout << "*ptrInt1= " << *ptrInt1 << endl;
	cout << "*ptrInt2= " << *ptrInt2 << endl;
	delete ptrInt1,ptrInt2;

	
	//Реализация Задания-2
	cout <<endl<< "Task-2" << endl;
	vector<int> vecInt{ 2,4,6,8,2,4,1 };
	vector<int*> PtrvecInt(7);
	for(size_t i = 0; i < 7; i++)
	{
		PtrvecInt[i] = &vecInt[i];
	}								 
	cout << "PtrVec: "<<endl;
	for (auto i : PtrvecInt)
	{
		cout << *i << " ";
	}
	cout <<endl;
	SortPointers(PtrvecInt);
	cout << "PtrVec(Sort): " << endl;
	for (auto i : PtrvecInt)
	{
		cout << *i << " ";
	}
	cout << endl;

	//Реализация Задание-3

	
	//Count_if и find
	cout << endl << "Task-3" << endl;
	Timer timer("Count_if, find");
	string vowels = "AEIOUYaeiouy";
	ifstream f("War and Peace.txt");
	size_t count = count_if
	(
		
		istreambuf_iterator<char>(f),
		 istreambuf_iterator<char>(),
		[=](char x)
		{
			return   vowels.find(x) != string::npos;
		}

	);
	f.close();
	cout << "Vowel-1: " << count << endl;
	timer.print();
	

	//While, if
	Timer timer1("while if");
	char vowel[] = "AEIOUYaeiouy";
	char ch;
	int vcount = 0;
	ifstream in("War and Peace.txt", ios::in | ios::binary);
	while (in.get(ch))
	{
		if (strchr(vowel, ch))
		{
			vcount++;
		}
	}
	in.close();
	cout << "Vowel-2: " << vcount << endl;
	timer1.print();

	
//успел не все методы
	
	return 0;
}
