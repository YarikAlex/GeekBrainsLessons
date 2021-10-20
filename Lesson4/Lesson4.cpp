#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

template <class ContainerT>
void PrintVector(ContainerT& v1)
{
    for_each(v1.begin(), v1.end(), [](float iter)
        {
            cout << iter << " ";
        });
    cout << endl;
}

template <class ContainerT, typename T>
void Insert_sorted(ContainerT& container, T& number)
{
    auto it = find_if(container.begin(), container.end(), [&number](T i)
        {
            return i > number;
        });
    container.insert(it, number);
}

int main()
{
    //Task 1
    vector<int> sortedVector = { 1,2,3,4,5,7,8,9,10,11 };
    int newNumber = 6;
    Insert_sorted(sortedVector, newNumber);
    PrintVector(sortedVector);

    list<float> sortedList = { 1,2,3,4,5,7,8,9,10,11 };
    float NUmberForList = 6.5;
    Insert_sorted(sortedList, NUmberForList);
    PrintVector(sortedList);


    //Task 2
    vector<float> vectorFloat(10);
    generate(vectorFloat.begin(), vectorFloat.end(), []() {return 1.11 * (rand() % 101); });
    PrintVector(vectorFloat);
    vector<int> vectorInt;
    for_each(vectorFloat.begin(), vectorFloat.end(), [&](int iter)
        {
            vectorInt.push_back(static_cast<int>(iter));
        });

    transform(vectorFloat.begin(), vectorFloat.end(), vectorFloat.begin(), [](float i)
        {
            return pow(i - static_cast<int>(i), 2);
        });
    cout << "Deviation is " << accumulate(vectorFloat.begin(), vectorFloat.end(), 0.0) << endl;

    return 0;
}