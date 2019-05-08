#include<iostream>
#include<string>
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
	NamedCircle(int radius, string name);

	void show() {
		cout << "Name : " << this->name << ", Radius : " << this->getRadius() << endl;
	}
};

NamedCircle ::NamedCircle(int radius, string name) : Circle(radius) {
	this->setRadius(radius);
	this->name = name;
}


int main() {
	NamedCircle waffle(3, "waffle");
	waffle.show();
}

/*
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
	void show() {
		cout << "Name : " << this->name << ", Radius : " << this->getRadius() << endl;
	}
};

int main() {
	NamedCircle waffle(3, "waffle");
	waffle.show();
}
*/