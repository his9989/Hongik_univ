//generalization : superclass
//specialization : subclass
//inheritence : superclass���� subclass�� ����� ��
//overriding(polymorphism) : subclass���� superclass�� ����Լ��� �����ϴ� ��
//overloading : ������ �����ε��� �ϳ� ����

#include<iostream>
using namespace std;

// superclass, generalization
class Polygon {
protected:
	int width, height;
public:
	Polygon() {
		cout << "Polygon Constructor" << endl;
	}
	Polygon(int a, int b) {
		cout << "Polygon Constructor width = "<<a<<", height =  "<<b<< endl;
	}
	void set_values(int a, int b) {
		width = a, height = b;
	}
	void check() {
		cout << "Polygon" << endl;
	}
};

// inheritence
// subclass, specialization
class Rectangle : public Polygon {
public:
	Rectangle() {
		cout << "Rectangle Constructor" << endl;
	}
	Rectangle(int a, int b) {
		cout << "Rectangle Constructor width = " << a << ", height =  " << b << endl;
	}
	int area() {
		return width * height;
	}
	// overriding
	void check() {
		cout << "Rectangel" << endl;
	}
};

class Triangle : public Polygon {
public:
	Triangle() {
		cout << "Triangle Constructor" << endl;
	}
	Triangle(int a, int b) {
		cout << "Triangle Constructor width = " << a << ", height =  " << b << endl;
	}
	int area() {
		return width * height * 0.5;
	}
	// overriding
	void check() {
		cout << "Triangle" << endl;
	}
};

int main() {
	Polygon p;
	Rectangle r;
	Triangle t;
	cout << "---" << endl;
	p.check();
	r.check();
	t.check();
	cout << "---" << endl;
	r.set_values(3, 4);
	t.set_values(3, 4);
	cout << "---" << endl;
	Polygon p2(3, 4);
	// subclass���� overloading�� constructor�� ȣ���ϴ� ���
	// superclass�� default constructor�� ȣ��ȴ�.
	Rectangle r2(3, 4);
	Triangle t2(3, 4);
	cout << "---" << endl;
	r2.set_values(3, 4);
	t2.set_values(3, 4);
	cout << "---" << endl;
	cout << r.area() << endl;
	cout << r2.area() << endl;
	cout << t.area() << endl;
	cout << t2.area() << endl;
}