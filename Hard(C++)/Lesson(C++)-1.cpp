#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>


struct PhoneNumber;
using namespace std;

struct Person
{
    string surname;
    string name;
    optional<string> patronymic;
    friend ostream& operator << (ostream& os, const Person& person);
    friend bool operator <(const Person& p1, const Person& p2);
    friend bool operator ==(const Person& p1,  const Person& p2);
    
};
ostream& operator << (ostream& os, const Person& person)
{
    os <<right<<setw(11)<< endl << person.surname << right << setw(11) << person.name;
    if (person.patronymic)
    {
        os << right << setw(16) << *person.patronymic;
    }
    else
        os <<right << setw(16)<<" ";
    return os;
}
bool operator < (const Person& p1, const Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic) < tie(p2.surname, p2.name, p2.patronymic);
}
bool operator == (const Person& p1, const  Person& p2)
{
    return tie(p1.surname, p1.name, p1.patronymic) == tie(p2.surname, p2.name, p2.patronymic);
}


struct PhoneNumber
{
    int country_code{};
    int city_code{};
    string number;
    optional<int> extension_number;
    friend ostream& operator << (ostream& os, const PhoneNumber& phone_number);
    friend bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2);
};
ostream& operator << (ostream& os, const PhoneNumber& phone_number)
{
	os <<right << setw(5)<< "+" << phone_number.country_code << "(" << phone_number.city_code << ")" << phone_number.number;
    if (phone_number.extension_number)
    {
        os << right << setw(3) << *phone_number.extension_number;
    }
	return os;
}
bool operator<(const PhoneNumber& pn1, const PhoneNumber& pn2)
{
   return tie(pn1.country_code, pn1.city_code, pn1.number, pn1.extension_number) < tie(pn2.country_code, pn2.city_code, pn2.number, pn2.extension_number);
}


class PhoneBook
{
    vector<pair<Person, PhoneNumber>> phonebook;

public:
    PhoneBook(ifstream& fin)
    {
        string str, surn, nam, num;
        int temp_ccode, cicode;
        optional<string> patron;
        optional<int> addnum;

        const size_t MAX_ELLEMENT = 7;

        size_t data_id = 0;
        size_t pair_id = 0;
        while (!fin.eof())
        {
            for (size_t i = 0; i < MAX_ELLEMENT; i++)
            {
                getline(fin, str, ';');
                if (str.find(';'))
                {
                    if (!str.find('!'))
                    {
                        if (data_id == 2 || data_id == 6)
                        {
                            if (data_id < 3)
                                patron = nullopt;
                            else
                                addnum = nullopt;
                            data_id++;
                        }
                    }
                    else
                    {
                        switch (data_id)
                        {
                        case 0: surn = str; data_id++; break;
                        case 1: nam = str; data_id++; break;
                        case 2: patron = str; data_id++; break;
                        case 3: temp_ccode = stoi(str); data_id++; break;
                        case 4: cicode = stoi(str); data_id++; break;
                        case 5: num = str; data_id++; break;
                        case 6: addnum = stoi(str); break;
                        default: ;
                        }
                    }
                }
            }
            phonebook.resize(pair_id + 1);
            phonebook.push_back(make_pair(phonebook[pair_id].first = { surn, nam, patron }, phonebook[pair_id].second = { temp_ccode, cicode,num, addnum }));
            pair_id++;
            data_id = 0;
            fin.get();
        }
        phonebook.pop_back();
    }
    friend ostream& operator<<(ostream& os, const PhoneBook& book);
    void SortByName()
    {
        sort(phonebook.begin(), phonebook.end(), [](const pair<Person, PhoneNumber>& pair_a, const pair<Person, PhoneNumber>& pair_b) {return pair_a.first < pair_b.first; });
    }
    void SortByPhone()
    {
        sort(phonebook.begin(), phonebook.end(), [](const pair<Person, PhoneNumber>& pair_a, const pair<Person, PhoneNumber>& pair_b) {return pair_a.second < pair_b.second; });
    }

    void ChangePhoneNumber(const Person& person, const PhoneNumber& phone_number)
    {
       
        find_if(phonebook.begin(), phonebook.end(),[person, phone_number](pair<Person, PhoneNumber>& user)
        {
                if (user.first == person)
                    user.second = phone_number;
                else
                    return false;

        });

    }

    tuple<string,PhoneNumber> GetPhoneNumber(const string& surname)
    {
        
        tuple<string, PhoneNumber>res1, res2, res3;
        int result = 0;

        
        for_each(phonebook.begin(), phonebook.end(), [&res1, &res2, &res3, &result, surname](const pair<Person, PhoneNumber>& user)
            {
                if (user.first.surname == surname)
                {
                    result++;
                    result > 1 ? res3 = make_tuple("    found more than 1", user.second):res1 = make_tuple("", user.second);
                }
                else 
                {
                    res2 = make_tuple("    not found", user.second);
                }
        });
        if (result > 0 && result <2)
            return res1;
        else if (result > 1)
            return res3;
        else
            return res2;
    }
};

ostream& operator<<(ostream& os, const PhoneBook& book)
{
    for (const auto& [person, phone_number] : book.phonebook)
    {
        os << person << phone_number;
    }
    return os;
}

int main()
{
    ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
    PhoneBook book(file);
    cout << right<<book<<endl;

    
	
    cout << endl <<"------SortByPhone-------" << endl;
    book.SortByPhone();
    cout<< book;

    cout <<endl<<endl<< "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout <<endl<<endl<< "-----GetPhoneNumber-----" <<endl<<endl;
     //лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
      cout << surname << "\t";
      auto answer = book.GetPhoneNumber(surname);
      if (get<0>(answer).empty())
        cout << get<1>(answer);
      else
        cout << get<0>(answer);
      cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    print_phone_number("Solovev");
    

    cout << endl << endl<< "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;
	return 0;
}