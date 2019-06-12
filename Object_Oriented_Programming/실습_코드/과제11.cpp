#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
	vector<int> v;
	int num = 0;
	float sum = 0.0;
	while (1) {
		cout << "Enter the integer (0 for exit) : ";
		cin >> num;
		if (num == 0) break;
		v.push_back(num);
		sum += num;
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl << "Average : " << sum / v.size() << endl;
	}
}