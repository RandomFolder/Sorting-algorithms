#include <iostream>
#include <vector>

int bin_search(std::vector<int> & A, int el)
{
	int low = 0, high = A.size() - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (A[mid] == el) return mid;
		else if (el > A[mid]) low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}

void selection_sort(std::vector<int> & A)
{
	for (int i = 0; i < A.size(); i++)
	{
		int min = i;
		for (int j = i + 1; j < A.size(); j++)
			if (A[j] < A[min]) min = j;
		std::swap(A[i], A[min]);
	}
}

void insertion_sort(std::vector<int>& A)
{
	for (int i = 1; i < A.size(); i++)
	{
		int value = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > value)
		{
			A[j + 1] = A[j];
			A[j] = value;
			j--;
		}
	}
}

void bubble_sort(std::vector<int>& A)
{
	for (int i = 0; i < A.size(); i++)
	{
		bool swapped = false;
		for (int j = A.size() - 1; j >= i + 1; j--)
			if (A[j - 1] > A[j])
			{
				std::swap(A[j - 1], A[j]);
				swapped = true;
			}
		if (!swapped) break;
	}
}

void Merge(std::vector<int>& A, int low, int mid, int high)
{
	int first_half = mid - low + 1, second_half = high - mid;
	std::vector<int> right, left;
	for (int i = 0; i < first_half; i++) left.push_back(A[low + i]);
	for (int i = 0; i < second_half; i++) right.push_back(A[mid + i + 1]);

	int i = 0, j = 0, k = low;

	while (i < first_half && j < second_half)
	{
		if (left[i] <= right[j])
		{
			A[k] = left[i];
			i++;
		}
		else
		{
			A[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < first_half)
	{
		A[k] = left[i];
		i++; k++;
	}

	while (j < second_half)
	{
		A[k] = right[j];
		j++; k++;
	}
}

void Merge_sort(std::vector<int>& A, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		Merge_sort(A, low, mid);
		Merge_sort(A, mid + 1, high);
		Merge(A, low, mid, high);
	}
}

int Partition(std::vector<int>& A, int low, int high)
{
	int pivot = A[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
		if (A[j] <= pivot)
		{
			i++;
			std::swap(A[i], A[j]);
		}
	i++;
	std::swap(A[high], A[i]);
	return i;
}

void Quicksort(std::vector<int>& A, int low, int high)
{
	if (low < high)
	{
		int q = Partition(A, low, high);
		Quicksort(A, low, q - 1);
		Quicksort(A, q + 1, high);
	}
}

void Heapify(std::vector<int> & A, int size, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && A[left] > A[largest]) largest = left;
	if (right < size && A[right] > A[largest]) largest = right;
	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		Heapify(A, size, largest);
	}
}

void Heapsort(std::vector<int> & A, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--) Heapify(A, size, i);

	for (int i = A.size() - 1; i >= 0; i--)
	{
		std::swap(A[0], A[i]);
		Heapify(A, i, 0);
	}
}

void Countingsort(std::vector<int>& A)
{
	int max_value = A[0];

	for (int i = 0; i < A.size(); i++)
		if (A[i] > max_value) max_value = A[i];

	std::vector<int> count(max_value + 1, 0);

	for (int i = 0; i < A.size(); i++) count[A[i]]++;
	for (int i = 1; i < count.size(); i++) count[i] += count[i - 1];

	std::vector<int> sorted_arr(A.size(), 0);
	for (int i = 0; i < sorted_arr.size(); i++)
	{
		sorted_arr[count[A[i]] - 1] = A[i];
		count[A[i]]--;
	}
	for (int i = 0; i < A.size(); i++) A[i] = sorted_arr[i];
}

void BucketSort(std::vector<int>& A)
{
	std::vector<std::vector<int>> buckets(A.size() + 1);

	int max_value = A[0];
	for (int i = 0; i < A.size(); i++)
		if (A[i] > max_value) max_value = A[i];

	for (int i = 0; i < A.size(); i++) buckets[A.size() * A[i] / max_value].push_back(A[i]);
	for (int i = 0; i < buckets.size(); i++)
		if (!buckets[i].empty()) insertion_sort(buckets[i]);

	int index = 0;

	for (int i = 0; i < buckets.size(); i++)
		if (!buckets[i].empty())
			for (int j = 0; j < buckets[i].size(); j++)
			{
				A[index] = buckets[i][j];
				index++;
			}
}

int num_of_dig(int number)
{
	int res = 0;
	while (number != 0)
	{
		number /= 10;
		res++;
	}
	return res;
}

void Radixsort(std::vector<int> & A)
{
	int max_value = A[0];

	for (int i = 0; i < A.size(); i++)
		if (A[i] > max_value) max_value = A[i];

	int num_of_digits = num_of_dig(max_value);

	for (int i = 0, digit = 1; i < num_of_digits; i++, digit *= 10)
	{
		std::vector<std::vector<int>> buckets(10);
		for (int j = 0; j < A.size(); j++)
			buckets[(A[j] / digit) % 10].push_back(A[j]);
		
		int index = 0;
		for (int j = 0; j < buckets.size(); j++)
			for (int k = 0; k < buckets[j].size(); k++)
			{
				A[index] = buckets[j][k];
				index++;
			}
	}

}

int main()
{
	std::vector<int> arr;
	for (int i = 0; i < 20; i++) arr.push_back(rand() % 30);
	//for (int i = 0; i < arr.size(); i++) std::cout << arr[i] << ' ';
	//std::cout << '\n';

	//selection_sort(arr);
	//insertion_sort(arr);
	//bubble_sort(arr);
	//Merge_sort(arr, 0, arr.size() - 1);
	//Quicksort(arr, 0, arr.size() - 1);
	//Countingsort(arr);
	//BucketSort(arr);
	//Heapsort(arr, arr.size());
	//Radixsort(arr);
	//for (int i = 0; i < arr.size(); i++) std::cout << arr[i] << ' ';
	//std::cout << '\n';
	//std::cout << bin_search(arr, 18);

	return 0;
}