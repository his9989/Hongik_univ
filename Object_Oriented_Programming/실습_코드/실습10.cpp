#include <iostream>
#include <string>
using namespace std;

class LoopAdder {
	string name;
	int x, y, sum;
	void read();
	void write();
protected:
	LoopAdder(string name = "") {
		this->name = name;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	virtual int calculate() = 0;
public:
	void run();
};

void LoopAdder::read() {
	cout << name << ":" << endl;
	cout << "Enter two numbers: ";
	cin >> x >> y;
}

void LoopAdder::write() {
	cout << "Sum of " << x << " to " << y << " : " << sum << endl;
}

void LoopAdder::run() {
	read();
	sum = calculate();
	write();
}

class ForLoopAdder : public LoopAdder {
protected:
	virtual int calculate();
public:
	ForLoopAdder (string name) : LoopAdder(name) {}
};

int ForLoopAdder::calculate() {
	int sum = 0;
	for (int i = getX(); i <= this->getY(); i++) {
		sum += i;
	}
	return sum;
}

int main() {
	ForLoopAdder forLoop("For Loop");
	forLoop.run();
}