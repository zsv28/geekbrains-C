#include <chrono>
#include <iostream>
#include <future>
#include <map>
#include <mutex>
#include <random>
#include <sstream>
#include <thread>



using namespace std;


mutex mtx;

//Задание-1
//Создайте потокобезопасную оболочку для объекта cout.Назовите ее pcout.
//Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль.
//Продемонстрируйте работу pcout.

class pCout
{
public:
    
    template<class T>
    pCout& operator<<(const T& obj)
    {
        mtx.lock();
        cout << obj;
        mtx.unlock();
        return *this;
        
    }
	
};
pCout pcout; //экземпляр класса

//перегрузка для endl
pCout& operator<< (pCout& s, ostream& (*f)(ostream&)) {
    f(cout);
    return s;
}

//Задание-2
//Реализовать функцию, возвращающую i - ое простое число(например, миллионное простое число равно 15485863).
//Вычисления реализовать во вторичном потоке.В консоли отображать прогресс вычисления.

bool isPrime(int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
        else
            continue;
    }
    return true;
}

int testPrimeIndex(int i)
{
    if (i == 1)
    {
        return 2; 
    }
    int num = 3;
    int i_curr = 2; 

    if (isPrime(num))
    {

        while (i_curr != i)  // выполняем до тех пор, пока i_curr не станет равно введенному i
        {
            num += 2;
            if (isPrime(num)) {
                ++i_curr;  // i_curr увеличиваем только если число является простым!
                pcout << "Progress " << double(i_curr) / i * 100. << "%" << endl;
            }
        }
    }
    return num;
}

//Задание-3
//Промоделировать следующую ситуацию.Есть два человека(2 потока) : хозяин и вор.
//Хозяин приносит домой вещи.При этом у каждой вещи есть своя ценность.
//Вор забирает вещи, каждый раз забирает вещь с наибольшей ценностью.



//Касаемо вора и хозяина.Да, почти похоже на игру ) Вообщем, там необходимо создать класс Home, внутри которого надо реализовать два потокобезопастных метода(с использованием mutex'a).
//Первый метод добавляет предметы в этот дом, второй метод - забирает вещь с наибольшей ценностью.
//
//
//И далее, два потока(мастер и вор) должны получить экземпляр этого класса Home и каждый вызывать в нем то, что нужно по логике.Мастер соответственно первый метод, вор - второй)



class Home
{
private:
  
    multimap<int, string> item
    {
        { 10000,"TV"},
        {  5000, "Phone"},
        { 30000, "Notebook"},
    	{ 2500, "Watch"},
    	{40000, "Gold chain"},
    	{15000, "Gold ring"}
    };
    
    multimap<int, string> local_items;
    
public:

    void master_add()
    {
        mtx.lock();
        std::random_device rd;
        std::mt19937 generator{ rd() };
        // и определяем диапазон этих случайных чисел (это будут индексы контейнера item)
        uniform_int_distribution<> distr(0, item.size() - 1);
        // здесь 5 число того, сколько раз мастер приносит предметы, можно подставить свое
        // определяем индекс вещи, которую принесет мастер
        auto index = distr(generator);
        // берем итератор на эту вещь по индексу
        auto current_it = item.begin();
        advance(current_it, index);
        auto current_item = *current_it;
        // и удаляем ее из общих объектов (можно и не удалять, например, тогда мастер может
        // принести более одной такой вещи)
        item.erase(current_it);
        // далее добавляем эту вещь к контейнеру вещей непосредственно связанных с домом
        local_items.insert(current_item);
        cout << "Master add: ";
       cout << current_item.second << " " << current_item.first << "$" << endl;
        mtx.unlock();
    }

   void thief_pick()
    {
       
        mtx.lock();
        multimap<int, string>::reverse_iterator it = local_items.rbegin();
        cout << "Thief stole: ";
        cout <<it->second<<endl;
        local_items.erase(prev(local_items.end()));
       mtx.unlock();
    }
   
};

int main()
{
	//Задание-1
    cout << "Task-1" << endl;
	
    const int x = 10, b = 5;
	//потоки вывода
    thread t1([&]() {pcout <<"x = " << x << endl; });
    thread t2([&]() {pcout <<"b = " << b << endl; });
    t1.join();
    t2.join();

    //Задание-2
    cout <<endl <<"Task-2" << endl;
    auto future(async(launch::async, testPrimeIndex, 2));
    auto res{ future.get() };
    pcout << endl << "Result = " << res<<endl;


    //Задание-3

    cout << endl << "Task-3" << endl;
    Home home;
    thread master([&]()
        {
            for (int i = 0; i < 5; ++i) {
                home.master_add();
                this_thread::sleep_for(chrono::milliseconds(1000));
            }
        }
    );
    thread thrief([&]()
    {
    	for(int i=0;i<5;i++)
    	{
            home.thief_pick();
            this_thread::sleep_for(chrono::milliseconds(2000));
    	}
	    
    });
    master.join();
    thrief.join();
  
	return 0;
   
};
