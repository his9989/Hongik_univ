#include<iostream>
using namespace std;

class Tower {
private:
	int height;
public:
	Tower() {
		height = 1;
	}
	Tower(int height) {
		this->height = height;
	}
	int getHeight() {
		return height;
	}
	//Tower operator+ (Tower &);

	friend Tower operator+ (Tower &tow1, Tower &tow2);
};

/*
Tower Tower::operator+(Tower & tow2) {
	Tower temp;
	temp.height = this->getHeight() + tow2.getHeight();
	return temp;
}
*/

Tower operator+ (Tower &tow1, Tower &tow2) {
	Tower temp;
	temp.height = tow1.getHeight() + tow2.getHeight();
	return temp;
}

int main() {
	Tower ta(10), tb(20), tc;

	cout << "Before the operation, the height of the tower was " << tc.getHeight() << endl;
	tc = ta + tb;
	cout << "After the operation, the height of the tower is " << tc.getHeight() << endl;
}