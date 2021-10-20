#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <tuple>
#include <utility>
#include <optional>
#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>
using namespace std;

class Person
{
public:
    string m_surname, m_name, m_patronymic;
    Person(string surname = "", string name = "", string patronymic = "")
        : m_surname(surname), m_name(name), m_patronymic(patronymic)
    {
        IsPatronymic();
    }
    ~Person() {}
    optional<string> IsPatronymic()
    {
        if (m_patronymic == "-")
            m_patronymic = "";
        return m_patronymic;
    }
    friend ostream& operator<< (ostream& out, const Person& person);
    friend bool operator>(const Person& P1, const Person& P2);
    friend bool operator<(const Person& P1, const Person& P2);
    bool operator==(const Person& other)
    {
        return this->m_surname == other.m_surname && this->m_name == other.m_name
            && this->m_patronymic == other.m_patronymic;
    }

};


bool operator>(const Person& P1, const Person& P2)
{
    if (P1.m_surname > P2.m_surname)
        return P1.m_surname > P2.m_surname;
    else if (P1.m_surname == P2.m_surname)
    {
        if (P1.m_name > P2.m_name)
            return P1.m_name > P2.m_name;
        else if (P1.m_name == P2.m_name)
            return P1.m_patronymic > P2.m_patronymic;
    }
}

bool operator<(const Person& P1, const Person& P2)
{
    if (P1.m_surname == P2.m_surname)
    {
        if (P1.m_name == P2.m_name)
        {
            return P1.m_patronymic < P2.m_patronymic;
        }
        return P1.m_name < P2.m_name;
    }
    return P1.m_surname < P2.m_surname;
}

ostream& operator<< (ostream& out, const Person& person)
{
    out << person.m_surname << "\t" << person.m_name << "\t" << person.m_patronymic;
    return out;
}

class PhoneNumber
{
public:
    int m_country, m_city, m_number;
    string m_additional_number;
    PhoneNumber(int country = 0, int city = 0, int number = 0, string add_number = "")
        : m_country(country), m_city(city), m_number(number), m_additional_number(add_number)
    {
        IsAdditionaNumber();
    }
    ~PhoneNumber() {}
    optional<string> IsAdditionaNumber()
    {
        if (m_additional_number == "-")
            m_additional_number = "";
        return m_additional_number;
    }
    friend ostream& operator<< (ostream& out, const PhoneNumber& phonenumber);
    friend bool operator>(const PhoneNumber& N1, const PhoneNumber& N2);
    friend bool operator<(const PhoneNumber& N1, const PhoneNumber& N2);
    PhoneNumber& operator=(const PhoneNumber& newnumber)
    {
        this->m_country = newnumber.m_country;
        this->m_city = newnumber.m_city;
        this->m_number = newnumber.m_number;
        this->m_additional_number = newnumber.m_additional_number;
        return *this;
    }
};

bool operator>(const PhoneNumber& N1, const PhoneNumber& N2)
{
    if (N1.m_country == N2.m_country)
    {
        if (N1.m_city == N2.m_city)
        {
            if (N1.m_number == N2.m_number)
            {
                return N1.m_additional_number < N2.m_additional_number;
            }
            return N1.m_number < N2.m_number;
        }
        return N1.m_city < N2.m_city;
    }
    return N1.m_country < N2.m_country;
}

bool operator<(const PhoneNumber& N1, const PhoneNumber& N2)
{
    if (N1.m_country == N2.m_country)
    {
        if (N1.m_city == N2.m_city)
        {
            if (N1.m_number == N2.m_number)
            {
                return N1.m_additional_number < N2.m_additional_number;
            }
            return N1.m_number < N2.m_number;
        }
        return N1.m_city < N2.m_city;
    }
    return N1.m_country < N2.m_country;
}

ostream& operator<< (ostream& out, const PhoneNumber& phonenumber)
{
    out << "+" << phonenumber.m_country << "(" << phonenumber.m_city << ")" << phonenumber.m_number << " " << phonenumber.m_additional_number;
    return out;
}

class PhoneBook
{
public:
    vector <pair<Person, PhoneNumber>> m_book;
    PhoneBook()
    {
        ifstream Book;
        Book.open("PhoneBook.txt");
        if (!Book.is_open() and !Book.good())
        {
            cout << "File is not open!" << endl;
        }
        else
        {
            while (!Book.eof())
            {
                int country, city, number;
                string surname, name, patronymic, add_number;
                Book >> surname >> name >> patronymic >> country
                    >> city >> number >> add_number;
                PhoneNumber m_telephone_number(country, city, number, add_number);
                Person m_human(surname, name, patronymic);
                pair m_pair(m_human, m_telephone_number);
                m_book.push_back(m_pair);
            }
        }
        Book.close();
    }
    virtual ~PhoneBook() {}

    void SortByName()
    {
        sort(m_book.begin(), m_book.end(), [](pair<Person, PhoneNumber> first_human, pair<Person, PhoneNumber> second_human)
            {
                return first_human.first < second_human.first;
            });
    }

    void SortByPhone()
    {
        sort(m_book.begin(), m_book.end(), [](pair<Person, PhoneNumber> first_human, pair<Person, PhoneNumber> second_human)
            {
                return first_human.second < second_human.second;
            });
    }

    void ChangePhoneNumber(Person change_person, PhoneNumber change_number)
    {
        for_each(m_book.begin(), m_book.end(), [change_person, change_number](pair<Person, PhoneNumber>& person)
            {
                if (person.first == change_person)
                {
                    person.second = change_number;
                }
                return person;
            });
    }

    tuple<string, PhoneNumber> GetPhoneNumber(const string& surname)
    {
        int count = 0;
        PhoneNumber number_answer;
        for_each(m_book.begin(), m_book.end(), [surname, &count, &number_answer](pair<Person, PhoneNumber>& person)
            {
                if (person.first.m_surname == surname)
                {
                    count++;
                    number_answer = person.second;
                }
            });
        if (count == 1)
        {
            tuple<string, PhoneNumber> tuple_answer("", number_answer);
            return tuple_answer;
        }
        if (count == 2)
        {
            tuple<string, PhoneNumber> tuple_answer("Find more than 1!", number_answer);
            return tuple_answer;
        }
        if (count == 0)
        {
            tuple<string, PhoneNumber> tuple_answer("Not found!", number_answer);
            return tuple_answer;
        }
    }

    friend ostream& operator<< (ostream& out, const PhoneBook& phonebook);
};

ostream& operator<< (ostream& out, const PhoneBook& phonebook)
{
    for (const auto& [human, number] : phonebook.m_book)
    {
        out << human << "\t" << number << endl;
    }
    return out;
}

void Test_Change_Phone_Number(PhoneBook book)
{
    string test_surname = "Orekhov";
    PhoneNumber test_number(7, 123, 1234567, "100");
    PhoneNumber result = get<1>(book.GetPhoneNumber(test_surname));
    assert(result.m_country == 7);
    assert(result.m_city == 123);
    assert(result.m_number == 1234567);
    assert(result.m_additional_number == "100");
    Person test_person("Orekhov", "Matvei", "Petrovich");
    PhoneNumber new_test_number(8, 8281, 7420182, "2");
    book.ChangePhoneNumber(test_person, new_test_number);
    result = get<1>(book.GetPhoneNumber(test_surname));
    assert(result.m_country == 8);
    assert(result.m_city == 8281);
    assert(result.m_number == 7420182);
    assert(result.m_additional_number == "2");

    cout << "My_Test_Change_Phone_Number is OK" << endl;
}

TEST_F(PhoneBook book, Change_Phone_Number)
{
    string test_surname = "Orekhov";
    PhoneNumber test_number(7, 123, 1234567, "100");
    PhoneNumber result = get<1>(book.GetPhoneNumber(test_surname));
    EXPECT_EQ(result.m_country == 7);
    EXPECT_EQ(result.m_city == 123);
    EXPECT_EQ(result.m_number == 1234567);
    EXPECT_EQ(result.m_additional_number == "100");
    Person test_person("Orekhov", "Matvei", "Petrovich");
    PhoneNumber new_test_number(8, 8281, 7420182, "2");
    book.ChangePhoneNumber(test_person, new_test_number);
    result = get<1>(book.GetPhoneNumber(test_surname));
    EXPECT_EQ(result.m_country == 8);
    EXPECT_EQ(result.m_city == 8281);
    EXPECT_EQ(result.m_number == 7420182);
    EXPECT_EQ(result.m_additional_number == "2");
}

void Test_GetPhoneNumber_MoreThenOne(PhoneBook& book)
{
    string test_surname = "Solovev";
    assert(get<0>(book.GetPhoneNumber(test_surname)) == "Find more than 1!");
    cout << "My_Test_GetPhoneNumber_MoreThenOne is OK" << endl;
}

TEST_F(PhoneBook& book, GetPhoneNumber_MoreThenOne)
{
    string test_surname = "Solovev";
    EXPECT_EQ(get<0>(book.GetPhoneNumber(test_surname)) == "Find more than 1!");
}

void Test_GetPhoneNumber_NotFound(PhoneBook& book)
{
    string test_surname = "Pupkin";
    assert(get<0>(book.GetPhoneNumber(test_surname)) == "Not found!");
    cout << "My_Test_GetPhoneNumber_NotFound is OK" << endl;
}

TEST_F(PhoneBook& book, GetPhoneNumber_NotFound)
{
    string test_surname = "Pupkin";
    EXPECT_EQ(get<0>(book.GetPhoneNumber(test_surname)) == "Not found!");
    cout << "My_Test_GetPhoneNumber_NotFound is OK" << endl;
}


int main()
{
    PhoneBook myBook;
    cout << myBook;

    cout << "---Sort By Phone---" << endl;
    myBook.SortByPhone();
    cout << myBook;

    cout << "---Sort By Name---" << endl;
    myBook.SortByName();
    cout << myBook;

    cout << "---Change PhoneNumber---" << endl;
    Person person_for_change_number("Orekhov", "Matvei", "Petrovich");
    PhoneNumber number_for_change(7, 123, 1234567, "100");
    myBook.ChangePhoneNumber(person_for_change_number, number_for_change);
    cout << myBook;

    cout << "---GetPhoneNumber---" << endl;

    auto print_phone_number = [&myBook](const string& surname)
    {
        cout << surname << "\t";
        auto answer = myBook.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            cout << get<1>(answer);
        else
            cout << get<0>(answer);
        cout << endl;
    };

    print_phone_number("Aleksandrov");
    print_phone_number("Solovev");
    print_phone_number("Petrov");

    Test_Change_Phone_Number(myBook);
    Test_GetPhoneNumber_NotFound(myBook);
    Test_GetPhoneNumber_MoreThenOne(myBook);

    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}