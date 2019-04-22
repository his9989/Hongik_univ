#include<iostream>
using namespace std;

class Shape {
private:
public:
	Shape() {
		cout << "This is Shape class" << endl;
	};
	virtual ~Shape() {
		cout << "Delete Shape class" << endl;
	}
	virtual void draw() {
		cout << "I have no value" << endl;
	}
};

class Rectangle :public Shape {
public:
	Rectangle() {
		cout << "This is Rectangle" << endl;
	}
	~Rectangle() {
		cout << "Delete Rectangle" << endl;
	}
	void draw() {
		cout << "Rectangle area is 50" << endl;
	}
};

class Circle : public Shape {
public:
	Circle() {
		cout << "This is Circle" << endl;
	}
	~Circle() {
		cout << "Delete Circle" << endl;
	}
	void draw() {
		cout << "Rectangle area is 500" << endl;
	}
};


int main() {
	Shape a;
	cout << endl;
	a.draw();
	cout << endl;
	Rectangle r;
	cout << endl;
	r.draw();
	cout << endl;
	Circle c;
	cout << endl;
	c.draw();
	cout << "-----------"<<endl;
/*
	a.~Shape();
	cout << endl;
	r.~Rectangle();
	cout << endl;
	c.~Circle();
	cout << endl;
	*/
}