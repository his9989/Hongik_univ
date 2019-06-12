#include <iostream>
#include <string>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0){
		this->radius = radius;
	}
	int getRadius() {
		return radius;
	}
	void setRadius(int radius) {
		this->radius = radius;
	}
	double getArea() {
		return 3.14 * radius * radius;
	}
};

class NamedCircle : public Circle {
	string name;
public:
	void setName(string name) {
		this->name = name;
	}
	string getName() {
		return name;
	}
};

int main() {
	NamedCircle pizza[5];
	string tempName = "";
	int tempRadius = 0;
	cout << "Enter the name and the radius of the pizza" << endl;
	int max = 0, index = 0;
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ": ";
		cin >> tempName;
		pizza[i].setName(tempName);
		cin >> tempRadius;
		pizza[i].setRadius(tempRadius);
		if (pizza[i].getRadius() > max) {
			max = pizza[i].getRadius();
			index = i;
		}
	}
	cout << "The largest pizza is " << pizza[index].getName() << endl;
	cout << "And its size is " << pizza[index].getArea();
}