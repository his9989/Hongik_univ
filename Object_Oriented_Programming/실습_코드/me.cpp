#include<iostream>
using namespace std;

class Tower {
private:
	int height;
public:
	Tower(int height);
	int getHeight() { return this->height; }
};

void swapHeight(Tower &tow1, Tower &tow2) {
	Tower temp = tow1;
	tow1 = tow2;
	tow2 = temp;
}

Tower::Tower(int height) {
	this->height = height;
}

int main() {
	Tower tower1(20), tower2(40);
	cout << "Before" << endl;
	cout << "	Tower 1 : " << tower1.getHeight() << endl;
	cout << "	Tower 2 : " << tower2.getHeight() << endl;
	swapHeight(tower1, tower2);
	cout << "After" << endl;
	cout << "	Tower 1 : " << tower1.getHeight() << endl;
	cout << "	Tower 2 : " << tower2.getHeight() << endl;
}