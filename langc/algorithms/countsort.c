#include <stdio.h>
#include <string.h>

/*
 arr -- the input array of integers to be sorted
 n -- the length of the input array
 k -- a number such that all integers are in the range 0..k-1
*/
void count_sort(int arr[], int n, int k)
{
	// create an integer array of size n to store sorted array
	int output[n];

	// create an integer array of size k, initialized by all zero
	int freq[k];
	memset(freq, 0, sizeof(freq));

	// using value of integer in the input array as index,
	// store count of each integer in freq[] array
	for (int i = 0; i < n; i++)
		freq[arr[i]]++;

	// calculate the starting index for each integer
	int total = 0;
	for (int i = 0; i < k; i++)
	{
		int old_count = freq[i];
		freq[i] = total;
		total += old_count;
	}

	// copy to output array, preserving order of inputs with equal keys
	for (int i = 0; i < n; i++)
	{
		output[freq[arr[i]]] = arr[i];
		freq[arr[i]]++;
	}

	// copy the output array back to the input array
	for (int i = 0; i < n; i++)
		arr[i] = output[i];
}

// C program for stable version of counting sort
int main()
{
	int arr[] = { 4, 2, 10, 10, 1, 4, 2, 1, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);
	count_sort(arr, n, 11);

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	return 0;
}
