#ifndef SORTER_CLASS
#define SORTER_CLASS

#include <vector>
#include <iostream>

using namespace std;
class Sorter
{
public:
	Sorter(size_t s)
	{
		size = s;
	}



	vector<int> Arr() {
		return arr;
	}


	void BubbleSort() {
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 1; j < arr.size(); j++) {
				if (arr[short(j-1)] > arr[j]) {
					iter_swap(&arr[short(j-1)], &arr[j]);
				}
			}
		}
	}


	void Fillarray()
	{
		int i = 0;
		while (i != size) {
			int randNum = rand() % (arr.size()+1);
			arr.push_back(randNum);
			i++;
		}
	}
	
	void PrintArray() {
		cout << "[ ";
		for (auto& v : arr) {
			cout << v << " ";
		}
		cout << " ]";
		cout << "\n";
	}

	~Sorter()
	{
		arr.clear();

	}

private:
	int size;
	vector<int> arr;
};
#endif // !SORTER_CLASS