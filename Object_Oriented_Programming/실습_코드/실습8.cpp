#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

class Circle {
	int radius;
public:
	Circle(int radius = 0) {
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
	NamedCircle(int radius, string name) {
		this->setRadius(radius);
		this->name = name;
	}
	string getName() {
		return name;
	}
	void show() {
		cout << "Name : " << this->getName() << ", Radius : " << this->getRadius() << ", Area : " << this->getArea() << endl;
	}
};

int main() {
	NamedCircle waffle(3, "waffle");
	waffle.show();
}