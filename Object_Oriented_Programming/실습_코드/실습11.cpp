#include<iostream>
#include<string>
using namespace std;

template <class T>
T biggest(T *arr, int n) {
	T max = arr[0];
	for (int i = 0; i < n; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

int main() {
	int n;
	cout << "Enter the number of integers: ";
	cin >> n;
	int *p = new int[n];
	cout << "Enter the integers : ";
	for (int i = 0; i < n; i++)
		cin >> p[i];
	cout << "The biggest number is " << biggest(p, n) << endl << endl;

	cout << "Enter the number of floating point: ";
	cin >> n;
	double *q = new double[n];
	cout << "Enter the floating numbers : ";
	for (int i = 0; i < n; i++)
		cin >> q[i];
	cout << "The biggest number is " << biggest(q, n) << endl;
}