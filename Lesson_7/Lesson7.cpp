#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <string>
using namespace std;

class FullName
{
public:
	string m_name;
	string m_surname;
	string m_patronymic;
	FullName(string name, string surname, string patronymic)
	:m_name(name), m_surname(surname), m_patronymic(patronymic){}
	FullName() {}
	~FullName() {}
	friend ostream& operator<< (ostream& out, const FullName& student);
};

ostream& operator<< (ostream& out, const FullName& student)
{
	out << student.m_surname << "\t" << student.m_name << "\t" << student.m_patronymic;
	return out;
}

class Student
{
public:
	FullName s_name;
	vector<int> s_grades;
	double s_average_score;
	Student(FullName student, double avg_sc = 0.0):s_name(student), s_average_score(avg_sc){}
	~Student() {}
	void AddGrades(int grade)
	{
		s_grades.push_back(grade);
		s_average_score = static_cast<double> (accumulate(s_grades.begin(), s_grades.end(), 0))/s_grades.size();	
	}
	void PrintAvg()
	{
		cout<<s_name << " has averege score " << s_average_score << endl;
	}
};


class IRepository {
	virtual void Open() = 0; // бинарная десериализация в файл
	virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
	virtual double GetAverageScore(const FullName& name) = 0;
	virtual string GetAllInfo(const FullName& name) = 0;
	virtual string GetAllInfo() = 0;
};

class StudentGroup//: public IRepository, public IMethods
{
public:
	vector<Student> m_students;
	StudentGroup() {}
	~StudentGroup() {}
	void AddStudent(Student newstudent)
	{
		m_students.push_back(newstudent);
	}
	double GetAverageScore(const FullName& name)
	{
		auto it = find_if(m_students.begin(), m_students.end(), [&](const Student& student) 
			{
				return tie(student.s_name.m_name, student.s_name.m_surname, student.s_name.m_patronymic) == tie(name.m_name, name.m_surname, name.m_patronymic);
			});
		return it->s_average_score;
	}
	string GetAllInfo(const FullName& name)
	{
		auto it = find_if(m_students.begin(), m_students.end(), [&](const Student& student)
			{
				return tie(student.s_name.m_name, student.s_name.m_surname, student.s_name.m_patronymic) == tie(name.m_name, name.m_surname, name.m_patronymic);
			});
		string student = it->s_name.m_surname + ' ' + it->s_name.m_name + " has grades: ";
		for (int i = 0; i < it->s_grades.size(); ++i)
		{
			student += to_string(it->s_grades[i]) + " ";
		}
		student += "Averege score: " + to_string(it->s_average_score);
		return student;
	}
	string GetAllInfo()
	{
		string student;
		for_each(m_students.begin(), m_students.end(), [&](const Student& it)
			{
				student = it.s_name.m_name + ' ' + it.s_name.m_surname + ' ' + it.s_name.m_patronymic + ": ";
				student += to_string(it.s_average_score);
			});
		return student;
	}

	void Open()
	{
		ifstream fromFile("Students.txt", ios::binary);
		while (!fromFile.eof())
		{
			FullName newname;
			fromFile.read(reinterpret_cast<char *>(&newname), sizeof(newname));
			Student newstudent(newname);
			m_students.push_back(newstudent);
		}
	}

	void Save()
	{
		ofstream inFile("Students.txt", ios::binary);
		for_each(m_students.begin(), m_students.end(), [&](Student& it)
			{
				inFile.write(reinterpret_cast<char*>(&it), sizeof(it));
			});
		inFile.close();
	}
};

int main()
{
	FullName me("Alexandr", "Yaroslavtcev", "Vyacheslavovich");
	Student first(me);
	first.AddGrades(5);
	first.AddGrades(4);
	first.AddGrades(3);
	first.AddGrades(5);
	first.PrintAvg();
	StudentGroup newgroup;
	newgroup.AddStudent(first);
	cout << newgroup.GetAverageScore(me) << endl;
	cout << newgroup.GetAllInfo(me)<<endl;
	cout << newgroup.GetAllInfo() << endl;
	newgroup.Save();
	newgroup.Open();

	return 0;
}