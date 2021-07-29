#include <iostream>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

//Функция для задания-1

void addArithmeticMean(list <double>& ls)
{
    list< double >::const_iterator  it = ls.begin(); //константный итератор списка
    double sum_elem_ls = 0; //сумма всех элементов списка
    int    size_ls{}; //размер списка
    while (it != ls.end())
    {
        sum_elem_ls = sum_elem_ls + *it;
        ++size_ls;
        ++it;
    }
    if (size_ls != 0) // если размер списка не равен 0, то добавляем число равное среднему арифметическому в конец списка
    {
        ls.push_back(sum_elem_ls / size_ls);
    }
}

//Задание-2

class Matrix {
    int m = 2;
    int n = 2;
    int** a;
public:
    Matrix()
    {
        a = new int* [n];
        for (int i = 0; i < n; i++)
            a[i] = new int[m]; // Создаем элементы
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                a[i][j] = rand() % 10 + 1;
        }
    }
    ~Matrix()
    {};
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        
    }
    int findDet()
    {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0]; //вычесляем определитель матрицы 2х2
    }

};

//Задание-3
class Range
{
private:
    class Impl
    {
    public:
        using value_type = int;
        using const_reference = const int&;

        Impl(const size_t v, const vector<int>& values) : m_idx(v), m_values(values) {}

        const_reference operator*() const { return m_values[m_idx]; }
        Impl& operator++()
        {
            m_idx++;
            return *this;
        }
        bool operator!=(const Impl& rhs) { return m_idx != rhs.m_idx; }

    private:
        
        size_t m_idx;
        const vector<int>& m_values;
    };

public:
    Range(const vector<int>& values) : m_values(values) {}

    typedef Impl iterator;
    iterator begin() const { return Impl(0, m_values); }
    iterator end() const { return Impl(m_values.size(), m_values); }

private:
    
    const vector<int>& m_values;
};

int main()
{
	//Реализация задания-1
    cout << endl << "Task-1" << endl;
    list<double> listDouble{ 2,3,6,5,4,3 };
    cout << "listDouble: ";
	for (auto i:listDouble)
	{
        cout << i << " ";
	}
    cout << endl;
    addArithmeticMean(listDouble);
    cout << "function(addArithmeticMean) listDouble: ";
    for (auto i : listDouble)
    {
        cout << i << " ";
    }
    cout << endl;

	//Реализация задания-2
    cout << endl << "Task-2" << endl;
    Matrix matrixInt;
    matrixInt.print();
    int result = matrixInt.findDet();
    cout << "Determinant = " << result << endl;


    
    //Задание-3
    cout << endl << "Task-3" << endl;
    vector<int> vec{ 2,3,54,4,3 };
  
    for (const int& v : Range(vec))
    {
        cout << v <<" ";
    }
   
    
}

