#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm> //for random_shuffle
#include <chrono> //for chronotime
#include <math.h> // for pow and log
using namespace std;

long long int stepCount = 0;
long double cApprox = 0;

void quickSort(vector<int>& arr, int low, int high, bool isRandom)
{
	while (low < high) {
		stepCount++;
		int j = partition(arr, low, high, isRandom);
		stepCount++;
		if (j - low < high - j) {
			stepCount += 3;
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
		stepCount++;
	}
	stepCount++;
}

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
		stepCount += 2;
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
			stepCount += 3;
		}
		stepCount++;
	}
	swap(arr[i + 1], arr[high]);
	stepCount += 3;
	return (i + 1);
}

