#include<iostream>
#include<string>
using namespace std;

class Shape {
protected:
	string name;
	int width, height;
public:
	Shape(string n = "", int w = 0, int h = 0) { name = n; width = w; height = h; }
	virtual double getArea() = 0;
	string getName() { return name; }
};

class Oval : public Shape {
public:
	Oval(string n, int w, int h) : Shape(n, w, h) {}
	double getArea() {
		return 3.14 * 0.25 * this->width * this->height;
	}
};

class Rectangle : public Shape {
public:
	Rectangle(string n, int w, int h) : Shape(n, w, h) {}
	double getArea() {
		return this->width * this->height;
	}
};

class Triangle : public Shape {
public:
	Triangle(string n, int w, int h) : Shape(n, w, h) {}
	double getArea() {
		return 0.5 * this->width * this->height;
	}
};

int main() {
	Shape *p[3];
	p[0] = new Oval("oval", 20, 40);
	p[1] = new Rectangle("rectangle", 30, 40);
	p[2] = new Triangle("triangle", 30, 40);
	for (int i = 0; i < 3; i++) {
		cout << "Area of " << p[i]->getName() << ": " << p[i]->getArea() << endl;
	}
	for (int i = 0; i < 3; i++) delete p[i];
}