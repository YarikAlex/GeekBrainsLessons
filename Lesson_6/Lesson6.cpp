#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
using namespace std;

mutex Mutex;

//Task #1
void pcout(int& data)
{
	lock_guard lg(Mutex);
	cout << "Start thread # " << this_thread::get_id() << endl;
	this_thread::sleep_for(1000ms);
	cout << "You entered: " << data << endl;
	this_thread::sleep_for(1000ms);
	cout << "Stop thread # " << this_thread::get_id() << endl;
}

//Task #2.
bool isNotPrime(long number)
{
	bool flag = true;
	for (long i = 2; i < number; ++i)
	{
		if (number % i == 0)
		{
			flag = false;
			break;
		}
	}
	cout << "\t\t\t\t\t\tIs " << number << " prime?";
	if (flag) { cout << " Yes!" << endl; return false; }
	else { cout << " No!" << endl; return true; }
}

void FindPrime(int number, int& result)
{
	cout << "Start thread # " << this_thread::get_id() << endl;
	int start = 1;
	vector<long> numbers(pow(number, 2));
	generate(numbers.begin(), numbers.end(), [&]() {return ++start; });
	auto new_end = remove_if(numbers.begin(), numbers.end(), [&](long it) {return isNotPrime(it); });
	numbers.erase(new_end, numbers.end());
	result = numbers[number - 1];
	cout << "Stop thread # " << this_thread::get_id() << endl;
}

//Task #3.
mutex Mute;

void AddThings(vector<int>& things)
{
	for (int i = 0; i < 10; ++i)
	{
		Mute.lock();
		cout << "--------Owner in a house--------" << endl;
		int newThing = rand() % 100;
		things.push_back(newThing);
		cout << "Added new thing in house. They cost is " << newThing << endl;
		for (int it : things)
		{
			cout << it << " ";
		}
		cout << endl;
		cout << "--------Owner go out--------" << endl;
		Mute.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void StealThing(vector<int>& things)
{
	for (int i = 0; i < 5; ++i)
	{
		Mute.lock();
		cout << "--------Thief in a house--------" << endl;
		things.erase(max_element(things.begin(), things.end()));
		for (int it : things)
		{
			cout << it << " ";
		}
		cout << endl;
		cout << "--------Thief go out--------" << endl;
		Mute.unlock();
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}

int main()
{
	//Task #1.
	int first_number = 5;
	int second_number = 150;
	thread th1(pcout, ref(first_number));
	thread th2(pcout, ref(second_number));
	th1.join();
	th2.join();

	//Task #2.
	int limit = 50;
	int result = 0;
	thread primeThread(FindPrime, limit, ref(result));
	for (int i = 0; i < limit; ++i)
	{
		cout << "Main thread " << this_thread::get_id() << " is working " << i << endl;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	primeThread.join();
	cout << "The " << limit << "th prime is " << result << endl;

	//Task #3.
	vector<int> house;
	thread owner_of_the_house(AddThings, ref(house));
	thread thief(StealThing, ref(house));

	owner_of_the_house.join();
	thief.join();

	return 0;
}
