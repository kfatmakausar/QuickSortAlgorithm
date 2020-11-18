#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm> //for random_shuffle
#include <chrono> //for chronotime
#include <math.h> // for pow
using namespace std;

long long int stepCount = 0;
long double cApprox = 0;

//function for generating pivot
int partition(vector<int>& arr, int low, int high, bool isRandom)
{
	if (isRandom) {
		int random = low + rand() % (high - low);
		swap(arr[random], arr[high]);
	}
	int pivot = arr[high];
	int i = (low - 1);
	stepCount += 2;
	for (int j = low; j <= high - 1; j++)
	{
		stepCount += 3;
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
			stepCount += 3;
		}
	}
	swap(arr[i + 1], arr[high]);
	stepCount += 1;
	return (i + 1);
}

//The main function that implements QuickSort(Array to be sorted, Starting index, Ending index) 
void quickSort(vector<int>& arr, int low, int high, bool isRandom)
{
	while (low < high) {
		stepCount++;
		int j = partition(arr, low, high, isRandom);
		stepCount++;
		if (j - low < high - j) {
			stepCount += 1;
			quickSort(arr, low, j - 1, isRandom);
			stepCount++;
			low = j + 1;
			stepCount++;
		}
		else {
			quickSort(arr, j + 1, high, isRandom);
			stepCount++;
			high = j - 1;
			stepCount++;
		}
	}
}

//Printing the vector arrays function
void printArray(vector<int> &arr)
{
	for (int x : arr)
	{
		cout << x << " ";
	}
}

//Generating sorted arrays for n input
void generateSort(vector<int> &arr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		arr.push_back(i);
	}
}

//Generate reverse arrays for n input
void generateReverse(vector<int> &arr, int n)
{
	for (int i = n; i >= 1; i--)
	{
		arr.push_back(i);
	}
}

//Generate random permutation arrays for n input
void generateRandom(vector<int> &arr, int n)
{
	for (int i = 1; i <= n; i++)
	{
		arr.push_back(i);
	}
	random_shuffle(arr.begin(), arr.end());
}

int main()
{
	// Array of inputs n
	int inputs[8] = { 100, 200, 300, 400, 500, 1000, 4000, 10000 };

	//QuickSort for Sorted Arrays, Reverse Arrays, Random Permutation Arrays
	//C approximation will be steps/n^2
	
	cout << "---------------------------------QUICK SORT----------------------------------------" << endl;
	cout << "SORTED ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateSort(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), false);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}
	cout << "REVERSED ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateReverse(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), false);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}
	cout << "RANDOM PERMUTATION ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateRandom(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), false);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}

	//50 instances of random inputs quickSort
	cout << "50 INSTANCES QUICK SORT" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		double totalT = 0;
		for (int x = 0; x < 50; x++)
		{
			vector<int> arr;
			for (int j = 1; j <= inputs[i]; j++)
			{
				arr.push_back(rand() % inputs[i] + 1);
			}
			auto t1 = chrono::high_resolution_clock::now();
			quickSort(arr, 0, (arr.size() - 1), false);
			auto t2 = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> timer = t2 - t1;
			totalT += timer.count();
			arr.clear();
		}
		cApprox = (stepCount / 50) / (pow(inputs[i], 2));
		cout << "50 INSTANCES OF " << inputs[i] << " ELEMENTS: Steps Average = " << stepCount / 50 << " | Runtime = " << totalT / 50 << " miliseconds | Average time: " << totalT / 50 << " miliseconds. | C Approximation: " << cApprox << endl;
	}
	
	cout << "---------------------------------RANDOMIZED QUICK SORT----------------------------------------" << endl;
	cout << "SORTED ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateSort(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), true);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}
	
	cout << "REVERSED ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateReverse(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), true);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}
	cout << "RANDOM PERMUTATION ARRAYS" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		vector<int> arr;
		generateRandom(arr, inputs[i]);
		auto t1 = chrono::high_resolution_clock::now();
		quickSort(arr, 0, (arr.size() - 1), true);
		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> timer = t2 - t1;
		cApprox = (stepCount) / (pow(inputs[i], 2));
		cout << arr.size() << " ELEMENTS: Steps = " << stepCount << " | Runtime = " << timer.count() << " miliseconds. | C Approximation: " << cApprox << endl;
		arr.clear();
	}

	//50 instances of random inputs quickSort
	cout << "50 INSTANCES RANDOMIZED QUICK SORT" << endl;
	for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
	{
		stepCount = 0;
		cApprox = 0;
		double totalT = 0;
		for (int x = 0; x < 50; x++)
		{
			vector<int> arr;
			for (int j = 1; j <= inputs[i]; j++)
			{
				arr.push_back(rand() % inputs[i] + 1);
			}
			auto t1 = chrono::high_resolution_clock::now();
			quickSort(arr, 0, (arr.size() - 1), true);
			auto t2 = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> timer = t2 - t1;
			totalT += timer.count();
			arr.clear();
		}
		cApprox = (stepCount / 50) / (pow(inputs[i], 2));
		cout << "50 INSTANCES OF " << inputs[i] << " ELEMENTS: Steps Average = " << stepCount / 50 << " | Runtime = " << totalT / 50 << " miliseconds | Average time: " << totalT / 50 << " miliseconds. | C Approximation: " << cApprox << endl;
	}
	
	system("PAUSE");
	return 0;
}


