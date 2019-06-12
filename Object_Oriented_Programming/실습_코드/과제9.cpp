#include<iostream>
#include<string>
using namespace std;

class Converter {
protected:
	virtual double convert(double src) = 0;
	virtual string getSourceString() = 0;
	virtual string getDestString() = 0;
public:
	void run() {
		double src;
		cout << getSourceString() << ": ";
		cin >> src;
		cout << getDestString() << ": " << convert(src);
	}
};

class MKConverter : public Converter {
protected:
	double convert(double src) {
		return src * 1.609;
	}
	string getSourceString() {
		return "mile";
	}
	string getDestString() {
		return "km";
	}
};

int main() {
	MKConverter mk;
	mk.run();
}