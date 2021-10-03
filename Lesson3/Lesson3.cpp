#include <iostream>
#include <list>
#include <vector>
#include "Timer.h"
using namespace std;

//Задаие №1
void CalculateArifmeticMean(list<double>& theList)
{
    double sum = 0, count = 0;
    for (auto it : theList)
    {
        sum += it;
        count++;
    }
    theList.push_back(sum / count);
}

//Задание №2
class Matrix
{
public:
    int m_size;
    int m_Determinant = 0;
    vector<int> m_matrix;
    Matrix(int size):m_size(size)
    {
        vector<int> matrix(size*size);
        generate(matrix.begin(), matrix.end(), []() {return rand() % 100; });
        m_matrix = move(matrix);
    }
    ~Matrix() {}
    vector<int> FindFirstElementsOfRow(vector<int>& matrix, int& size)
    {
        vector<int> firstElementOfRow;
        int count = 1;
        for (auto it : matrix)
        {
            if ((count - (size + 1)) % size == 0)
            {
                firstElementOfRow.push_back(it);
            }
            count++;
        }
        return firstElementOfRow;
    }

    int FindMinor(vector<int>& vector)
    {
        int count = 1;
        int first = 1, second = 1;
        for (auto it : vector)
        {
            if (count > 1 && count < 4)
                second *= it;
            else first *= it;
            count++;
        }
        return first - second;
    }
    void FindDet(vector<int> matrix, vector<int>& arrayOfMinor, int size, int i)
    {
        if (i == 0)
        {
            matrix.erase(matrix.begin() + (size * i), matrix.begin() + (size * (i + 1)));
            vector<int> new_matrix;
            int count = 1;
            for (auto it : matrix)
            {
                if (count++ % size != 0)
                    new_matrix.push_back(it);
            }
            arrayOfMinor[i] *= FindMinor(new_matrix);
            new_matrix.clear();
        }
        if (i == 1)
        {
            matrix.erase(matrix.begin() + (size * i), matrix.begin() + (size * (i + 1)));
            vector<int> new_matrix;
            int count = 1;
            for (auto it : matrix)
            {
                if (count++ % size != 0)
                    new_matrix.push_back(it);
            }
            arrayOfMinor[i] *= FindMinor(new_matrix);
            new_matrix.clear();
        }
        if (i == 2)
        {
            matrix.erase(matrix.begin() + (size * i), matrix.begin() + (size * (i + 1)));
            vector<int> new_matrix;
            int count = 1;
            for (auto it : matrix)
            {
                if (count++ % size != 0)
                    new_matrix.push_back(it);
            }
            arrayOfMinor[i] *= FindMinor(new_matrix);
            new_matrix.clear();
        }
        matrix.clear();
    }

    int CutTheMatrix(vector<int> matrix, int size, int row)
    {
        int Determinant = 0;
        while (size > 3)
        {
            matrix.erase(matrix.begin() + (size * row), matrix.begin() + (size * (row + 1)));
            vector<int> new_matrix;
            int count = 1;
            for (auto it : matrix)
            {
                if (count++ % size != 0)
                    new_matrix.push_back(it);
            }
            matrix.clear();
            matrix = new_matrix;
            new_matrix.clear();
            size--;
        }
        if (size == 3)
        {
            vector<int> firstElementOfRow;
            int count = 1;
            for (auto it : matrix)
            {
                if ((count - (size + 1)) % size == 0)
                {
                    firstElementOfRow.push_back(it);
                }
                count++;
            }
            for (int i = 0; i < 3; ++i)
            {
                FindDet(matrix, firstElementOfRow, size, i);
            }
            for (int i = 0; i < firstElementOfRow.size(); ++i)
            {
                Determinant += pow(-1, i + 2) * firstElementOfRow[i];
            }
        }
        return Determinant;
    }
    void FindDeterminantOfMatrix()
    {
        vector<int> firstElementOfRow = FindFirstElementsOfRow(m_matrix, m_size);
        for (int row = 0; row < m_size; ++row)
        {
            m_Determinant += pow(-1, row + 2) * firstElementOfRow[row] * CutTheMatrix(m_matrix, m_size, row);
        }
        cout << "Determinant of Matrix = " << m_Determinant << endl;
    }
};

int main()
{
    //Задание №1.
    list<double> list_of_nambers{ 1, 2, 13, 4, 5, 26, 7, 8, 59, 10 };
    CalculateArifmeticMean(list_of_nambers);
    for (auto it : list_of_nambers)
    {
        cout << it << " ";
    }
    cout << endl;

    //Задание №1.
    Matrix matrix(4);
    Timer timer("FindDeterminantOfMatrix");
    matrix.FindDeterminantOfMatrix();
    timer.print();


    return 0;
}
